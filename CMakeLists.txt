cmake_minimum_required(VERSION 3.16)

# CXX is required by PsyCross, whose renderer and GTE are C++.
project(brave_fencer_musashi_decomp LANGUAGES C CXX)

option(MUSASHI_BUILD_PC_PORT "Build the platform-neutral PC port smoke target" ON)
option(MUSASHI_WITH_PSYCROSS "Link the PC port against the PsyCross Psy-Q reimplementation" ON)
option(MUSASHI_USE_VENDOR_BFM
    "Prefer cleaned house-style matched leaves reconciled with vendor/bfm-decomp (Druthulu)"
    OFF)

# PsyCross (MIT) reimplements libgpu, libgte, libspu, libcd, libetc, libapi and
# libpad for PC. It is vendored at a pinned commit by tools/fetch_toolchains.sh
# and its checkout is ignored.
#
# Its own CMakeLists.txt is deliberately not used. It calls find_package(OPENAL)
# in upper case, which only resolves on case-insensitive filesystems, and links
# a bare `OpenAL` target that modern config packages do not export. Owning the
# integration here avoids carrying a patch against an ignored checkout: the
# upstream build file is only a source glob and two find_package calls.
if(MUSASHI_BUILD_PC_PORT AND MUSASHI_WITH_PSYCROSS)
    set(MUSASHI_PSYCROSS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tools/third_party/psycross")
    if(NOT EXISTS "${MUSASHI_PSYCROSS_DIR}/include/PsyX/PsyX_public.h")
        message(FATAL_ERROR
            "PsyCross not found under tools/third_party/psycross; run "
            "./tools/fetch_toolchains.sh, or configure with -DMUSASHI_WITH_PSYCROSS=OFF")
    endif()

    find_package(SDL2 REQUIRED)
    find_package(OpenAL REQUIRED)
    # GLAD loads GL entry points at runtime, but the library must still link.
    find_package(OpenGL REQUIRED)

    # src/psx holds the Psy-Q implementations (LIBGPU, LIBGTE, LIBCD, ...) in
    # files named with an uppercase .C. Globbing only "*.c" is case-sensitive on
    # Linux and silently drops all eleven, producing a library that links but
    # exports none of the Psy-Q API. Upstream's own CMakeLists.txt has this bug;
    # REDRIVER2 builds with premake instead, which is why it goes unnoticed.
    #
    # GCC treats .C as C++, so the language is forced back to C to keep these
    # symbols unmangled and callable from the decomp's C.
    file(GLOB_RECURSE MUSASHI_PSYCROSS_SOURCES_C
        "${MUSASHI_PSYCROSS_DIR}/src/*.c"
        "${MUSASHI_PSYCROSS_DIR}/src/*.C"
    )
    file(GLOB_RECURSE MUSASHI_PSYCROSS_SOURCES_CXX
        "${MUSASHI_PSYCROSS_DIR}/src/*.cpp"
    )
    if(NOT MUSASHI_PSYCROSS_SOURCES_C MATCHES "LIBGPU")
        message(FATAL_ERROR
            "PsyCross source glob did not pick up src/psx/LIBGPU.C; the Psy-Q "
            "layer would be missing from the build")
    endif()
    # Keep the ignored upstream checkout intact. Both native and source-step
    # probes use this exact, count-checked signed-translation adaptation.
    find_package(Python3 REQUIRED COMPONENTS Interpreter)
    set(MUSASHI_GTE_UPSTREAM "${MUSASHI_PSYCROSS_DIR}/src/gte/PsyX_GTE.cpp")
    set(MUSASHI_GTE_PREPARED "${CMAKE_CURRENT_BINARY_DIR}/generated/PsyX_GTE.cpp")
    add_custom_command(OUTPUT "${MUSASHI_GTE_PREPARED}"
        COMMAND ${Python3_EXECUTABLE}
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/prepare_psycross_gte.py"
            "${MUSASHI_GTE_UPSTREAM}" "${MUSASHI_GTE_PREPARED}"
        DEPENDS "${MUSASHI_GTE_UPSTREAM}"
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/prepare_psycross_gte.py"
        VERBATIM)
    list(REMOVE_ITEM MUSASHI_PSYCROSS_SOURCES_CXX "${MUSASHI_GTE_UPSTREAM}")
    list(APPEND MUSASHI_PSYCROSS_SOURCES_CXX "${MUSASHI_GTE_PREPARED}")
    set_source_files_properties(${MUSASHI_PSYCROSS_SOURCES_C} PROPERTIES LANGUAGE C)
    add_library(psycross_static STATIC
        ${MUSASHI_PSYCROSS_SOURCES_C}
        ${MUSASHI_PSYCROSS_SOURCES_CXX}
    )
    set_target_properties(psycross_static PROPERTIES OUTPUT_NAME "psycross")
    target_include_directories(psycross_static
        PRIVATE "${MUSASHI_PSYCROSS_DIR}/src/gte"
        PUBLIC
            "${MUSASHI_PSYCROSS_DIR}/include"
            "${MUSASHI_PSYCROSS_DIR}/include/psx"
    )
    target_compile_features(psycross_static PUBLIC cxx_std_11)
    # The primitive-tag pointer macros (setaddr, getaddr, nextPrim, isendprim)
    # are gated on USE_EXTENDED_PRIM_POINTERS, not on the 64-bit check that
    # sizes the tag struct. Without it, on x86-64, a 12-byte tag holding a
    # uintptr_t is filled by macros that truncate every pointer to 32 bits and
    # test for a 24-bit terminator, so an ordering-table walk yields nothing.
    # Upstream sets this in premake. PUBLIC because the macros expand in our
    # code as well as in the library.
    # USE_PGXP defaults to USE_EXTENDED_PRIM_POINTERS, so the line above would
    # also switch PGXP on. It is held off explicitly: the port has no GTE
    # transforms yet, and with PGXP on a primitive without a cache entry has
    # its positions zeroed rather than left alone. Revisit when 3D lands.
    target_compile_definitions(psycross_static PUBLIC USE_EXTENDED_PRIM_POINTERS=1 USE_PGXP=0)
    # Two Linux/GCC build breaks in upstream, corrected here rather than by
    # patching the ignored checkout. Upstream is built with MSVC, where neither
    # surfaces.
    #  - Brace-initialised narrowing: PsyX_GPU.cpp initialises a uintptr_t from
    #    -1, and gte/rcossin_tbl.h fills short tables with values above
    #    SHRT_MAX, relying on implementation-defined wraparound. GCC 16 rejects
    #    both, in C as well as C++ now that C23 is the default, so the
    #    diagnostic is downgraded for this target in both languages.
    #  - include/psx ships a Psy-Q compatibility strings.h stub. Being on the
    #    -I path it shadows glibc's, so strcasecmp is never declared even though
    #    PsyX_main.cpp includes the header. pc_port/compat/psycross_compat.h
    #    declares the prototype directly; see that file for the full account.
    #  - LIBETC.C returns a callback pointer as an int (`(int)vsync_callback`),
    #    which truncates on x86-64. GCC 14+ makes that an error in C. It is
    #    downgraded to build, but the truncation is real: the handle returned by
    #    ResetCallback/VSyncCallback must not be cast back to a pointer on a
    #    64-bit host. See docs/PC-PORT.md.
    target_compile_options(psycross_static PRIVATE
        -Wno-narrowing
        -fpermissive
        -include "${CMAKE_CURRENT_SOURCE_DIR}/pc_port/compat/psycross_compat.h"
    )
    target_link_libraries(psycross_static
        PUBLIC
            SDL2::SDL2
            OpenAL::OpenAL
            OpenGL::GL
    )
endif()

if(MUSASHI_BUILD_PC_PORT)
    # Native entry-data loading verifies the complete retail EXE before writes.
    # Crypto only: no TLS/network dependency is used by the port.
    find_package(OpenSSL REQUIRED COMPONENTS Crypto)
    find_package(Python3 REQUIRED COMPONENTS Interpreter)

    # The explicit native MIPS seam consumes the exact words from the matched
    # overlay rather than a separately maintained host formatting algorithm.
    set(MUSASHI_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
    file(MAKE_DIRECTORY "${MUSASHI_GENERATED_DIR}")
    foreach(MUSASHI_ENTRY_RANGE IN ITEMS "800553f4:595" "800553d8:7" "80053290:30" "8001c9d0:19" "8001c320:74" "800285ac:8" "8005c4cc:4" "80011e24:24" "800295d4:36" "80029664:11" "80011380:192" "80010000:40" "800100a0:28" "80010178:37"
                                        "80010214:457" "80014238:36" "8001c044:33" "80015310:15" "80028a48:130" "80028c50:66" "80014928:14" "8005ce18:3"
                                        "800143ac:38" "80014390:7" "800191a8:5" "80010a98:18" "800595fc:23" "80042610:13" "800189a8:30" "80018a20:145" "8005d184:48" "8005f704:9" "8005d244:157" "80028d58:8" "80029178:10" "8005d538:90" "8005e188:7" "8005d4b8:32" "8005e79c:83" "80018c64:33" "80018f88:16" "80018ce8:100" "80018f20:26" "80018e9c:33" "800291b4:5" "80028d78:9" "80015208:59" "80059bfc:62" "8005ae80:58" "8005c054:91" "80010b40:29" "80010bb4:50" "80029690:26" "80029274:42" "80029344:54" "80014b10:59" "8002d8d4:12" "800476c0:111" "8004768c:13" "80046610:8" "800469cc:36" "80046994:5" "800469a8:9" "80046cfc:8" "80046bfc:15" "800468fc:33" "80046abc:34" "8004689c:24" "80043088:12" "80046d1c:604" "80046c38:49" "80046b44:46" "8004657c:37" "8001bfb0:8" "8001bfa0:4" "8003d650:37" "8002d858:20" "80018730:122" "80018714:7" "8002f5c8:22" "8002f658:9" "80029504:4" "8002f620:10" "8002f648:4" "8001af04:12" "800191bc:6" "800191d4:26" "80011d54:19" "80011cfc:22" "8001b85c:4" "8001c0c8:33" "8001b384:4" "80011dcc:10" "80029254:4" "8002aef8:4" "8002941c:10" "80010ae0:12" "80011b7c:37" "80011778:40" "80015498:92" "80058b40:15" "8001c00c:14" "8001f9f8:101" "8001d1c4:113" "800184f0:137" "800596f4:27" "8005bed8:82" "8002cdd8:131" "8003d25c:52" "8002cfe4:20" "8002d904:217" "80037fc4:118" "8002ec10:96" "8003836c:14" "8003c4f0:42" "80030f80:343" "8002d320:102" "8002ee64:11" "8002eff8:27" "800314dc:135" "800316f8:164" "80031988:68" "8003819c:18" "80038210:62" "80038308:17" "8003834c:8" "80038638:12" "8003b250:12" "8003c23c:127" "8003d3b4:17" "80031be0:58" "8002f064:27" "80030ca4:55" "80030d80:128" "800336a8:121" "8003388c:663" "80034650:32" "8003f144:143" "8003f380:45" "800414e4:49" "8005ba90:187" "8001099c:27" "80058ce4:15" "80059cf4:29" "8003500c:119" "8002d034:111" "8002d240:23" "8002d29c:33" "8002dc68:198" "8002df80:110" "8002e138:289" "8002e5bc:15" "8002e5f8:16" "8002e638:50" "8002e700:39" "8002e79c:31" "8002e818:49" "8002e8dc:28" "8002e94c:49" "8002ea10:40" "8002eab0:24" "8002eb10:39" "8002ebac:25" "8002ede4:32" "8002ee90:10" "8002eeb8:8" "8002eed8:62" "8002efd0:10" "8002f0d0:9" "8002f248:167" "8002f4e4:57" "8002f714:62" "80031b7c:25" "80031cc8:42" "80031dec:42" "80031e94:32" "80031f14:45" "80031fc8:32" "80032048:152" "800322a8:127" "800324a4:180" "80032774:192" "80032a74:422" "8003310c:50" "800331d4:30" "8003324c:54" "80033398:93" "8003350c:43" "800335b8:60" "80034314:207" "800346d0:62" "80034844:25" "800348a8:29" "8003491c:78" "80034a54:18" "80034a9c:17" "80034ae0:11" "80034b0c:12" "80034cf0:67" "80034dfc:132" "80036d58:87" "80036eb4:13" "80036ee8:12" "80036f18:32" "800381e4:11" "800383a4:65" "800384a8:70" "800385c0:30" "80038668:12" "80038698:74" "800387c0:30" "80038838:44" "80038908:20" "8003916c:26" "8003ab84:164" "8003af4c:41" "8003b08c:11" "8003b0b8:11" "8003c0a0:103" "8003c92c:399" "8003cff8:79" "8003ede8:63" "80043974:8" "80044a8c:34" "8005ce98:3" "8001a0fc:6" "8001a114:137" "8001af34:104" "8001b0d4:86" "8001b394:12" "8001b3c4:211" "8001b710:30" "8001b788:15" "8001b7c4:38" "8002d4c8:53" "8002d7fc:4" "8002ed90:21" "8002fd14:45" "8002fde8:73" "8002ff0c:166" "80030730:185" "80030a14:164" "80031a98:57" "800363cc:459" "80036af8:139" "80037144:124" "80037334:9" "80037358:4" "80037368:26" "800373d0:63" "800374cc:16" "8003750c:148" "8003775c:31" "800377d8:316" "80037cd8:39" "80037d74:9" "800401cc:6" "800415a8:33" "8004162c:31" "800416a8:194" "800419b0:28" "80041a80:12" "80041ab0:247" "80041e8c:94" "80042374:10" "800439d4:9" "80046630:71" "8004674c:84" "8001aaa0:12" "80014cac:19" "8001aa98:2" "8001534c:22" "800153a4:10" "80010da0:16" "800110cc:30" "80011220:15" "8001125c:19" "800111bc:25" "80011144:30" "8001a9f8:32" "80010f80:83" "80029514:4" "80010ed4:43" "80014338:22" "80010d60:16" "8002fdc8:8" "8002fc64:44" "8003c438:24" "8003c498:22" "8003ae14:34" "800301a4:9" "8002fb08:87" "8001abbc:77" "8001acf0:104" "8001ae90:29" "800149e0:76" "80014c28:11" "80014d30:14" "80014cf8:14" "800167f0:49" "800118ac:31" "80010a84:5" "800146b0:49" "800527c4:30" "80053eec:32" "8001bff8:5" "80011928:28" "8001bfe8:4" "800116e0:38" "80029000:8" "80028d9c:8" "80028fbc:8" "800183e0:28" "800167b8:14" "80016224:139" "80010a08:31" "80016638:44" "80010cec:29" "80011818:37" "80011a3c:40" "80011c10:31" "8005b1c4:143" "80010c7c:28" "8001513c:2" "80015608:86" "80015760:106" "80059a80:49" "80019018:4" "80018e78:9" "8002ab64:39" "8002ac00:38" "80015978:9" "80012c6c:19" "80012abc:18" "80012cb8:21" "80012b04:21" "80012b58:69" "80012d0c:44" "80049cac:163" "8004914c:12" "800491ac:8" "8004945c:12" "80011e84:12" "8001c214:44" "8001c97c:21" "8001c924:22" "8001c8c4:24" "8001c810:45" "8001ca1c:27" "8001ca88:30" "8001cb00:27" "8001cb6c:28" "8001cbdc:24" "8001cc3c:25" "8001cca0:25" "8001cd04:19" "800233cc:70" "800234e4:35" "80023570:119" "8001cd50:19" "8001cd9c:19" "8001cde8:16" "8001ce28:16" "8001ce68:22" "8001cec0:16" "8001cf00:12" "8001cf30:6" "8001cf48:28" "8001cfb8:9" "8001d074:29" "8001d150:7" "8001d130:8" "8001d0f4:15" "8001d0e8:3" "8001d050:9" "8001c2c4:23" "8001cfdc:29" "800599b8:50" "80024054:91" "8005a600:22" "80053d44:57" "80058890:111" "8001fb8c:31" "8001d388:29" "80015908:19" "80015a74:23" "8005b75c:21" "80058b7c:60" "8005e8e8:83" "8004974c:16" "80052fcc:33" "80054514:177" "80048eac:67" "80053050:74" "800145ec:49" "800525dc:30" "80052654:92"
                                        "80059d68:65" "8005a870:164" "8005ab00:22" "8005ab58:51" "8005ac24:51" "8005acf0:17" "8005ad34:33" "8005b7b0:184" "8005b710:19" "8005c020:13" "800426fc:7" "8005283c:153" "80052d00:36" "80052bec:69" "80053178:40" "80053218:30" "80052d90:42" "80014774:17" "800147b8:92" "80059888:37" "80059760:74" "8005af68:151" "80058a4c:46" "80058b04:15" "80014960:14" "80014998:18" "80014444:36" "8004923c:3" "800144d4:32" "80014554:38" "8002850c:19" "80053af8:10" "8002823c:50" "80028620:29" "80053308:8" "80053328:311" "8005386c:20" "80053804:26" "800538bc:12" "800538ec:35" "80053f6c:245" "80053e28:49" "80048d9c:68" "800484ec:88" "80053b20:46" "8004787c:15" "800478b8:36" "80047948:40" "80054340:60" "80054430:50" "800544f8:7" "80047d3c:33" "80053cf8:19" "80047cb4:32" "8004d16c:40" "80053ad8:8" "800491fc:8" "8004921c:6" "8005ce28:3" "80043078:4" "80059fc0:298" "8005b684:10"
                                        "8001971c:133" "80019990:32" "80045374:179"
                                        "80019a24:53" "80034b98:35" "80019af8:385"
                                        "8001a338:424" "8004355c:8" "8004239c:26"
                                        "80042404:56" "800424e4:39" "80044dbc:26"
                                        "80045640:8" "80045660:184" "80045c94:27" "80043a18:65"
                                        "80045940:42" "800459e8:171" "8005c4dc:25"
                                        "80043398:10"
                                        "800433c0:10"
                                        "800433e8:10"
                                        "80043410:4"
                                        "800435cc:78"
                                        "80043704:75"
                                        "80043994:8"
                                        "80043b1c:32"
                                        "80045090:64"
                                        "80045d00:180"
                                        "800460cc:133"
                                        "8004637c:65"
                                        "80046480:51"
                                        "8005ce68:3"
                                        "8005cea8:3"
                                        "80043420:4"
                                        "80043440:4"
                                        "8004357c:8"
                                        "800443a4:179"
                                        "8005c584:32"
                                        "8005c324:13" "8005c358:12"
                                        "8005cf08:4" "8005cf18:4"
                                        "8006189c:121" "80061b58:66"
                                        "800617cc:5" "800617e0:5" "800617f4:5" "80061808:5"
                                        "8006181c:5" "80061830:5" "80061844:5" "80061858:5"
                                        "80045290:57"
                                        "800426d4:4"
                                        "8003c598:229"
                                        "80037d98:66"
                                        "8003d424:4"
                                        "8002cc4c:26"
                                        "8002fae0:10"
                                        "8002c8bc:14"
                                        "80037cc8:4"
                                        "8003be74:9"
                                        "8003be98:130"
                                        "8003b1ec:25"
                                        "80034c24:51"
                                        "800430b8:9"
                                        "800430dc:137"
                                        "80043830:81"
                                        "80037004:9"
                                        "8003be24:20"
                                        "8003b3d0:35"
                                        "8002d1f0:20"
                                        "8003b45c:318"
                                        "8003b954:308"
                                        "8003b280:52"
                                        "8002c8f4:214"
                                        "8003a424:8"
                                        "8003a444:62"
                                        "8003a53c:31"
                                        "8003a5b8:165"
                                        "8003a84c:115"
                                        "8003af04:18"
                                        "8003b0e4:26"
                                        "8003b14c:9"
                                        "8003d518:12"
                                        "8003d548:58"
                                        "8003fe3c:196"
                                        "8004014c:21"
                                        "800401a0:11"
                                        "80040868:52"
                                        "8003fa64:237"
                                        "800425e0:12"
                                        "80042f8c:42"
                                        "8005d6cc:26" "8005d734:91" "8005d8a0:5" "8005d980:17"
                                        "8005d9c4:133" "8005dbd8:50"
                                        "8005eae8:16" "8005f75c:53" "8005dca0:118"
                                        "8005e0ac:36"
                                        "8005fba8:8" "8005fbc8:40"
                                        "8005f830:153" "8005fb70:11"
                                        "8005e228:83" "8005e374:14" "8005e3ac:252" "8005ea88:8" "8005eac8:8" "8005f384:4"
                                        "8005de78:141" "8005e13c:10" "8005e1a4:33" "8005ea34:8" "8005ea54:5" "8005ea68:8" "8005eaa8:8" "8005eb28:54" "8005ec00:48" "8005ecc0:35" "8005ed4c:223" "8005f290:61" "8005f394:47" "8005f450:159" "8005f6cc:14" "8005fa94:55")
        string(REPLACE ":" ";" MUSASHI_ENTRY_PARTS "${MUSASHI_ENTRY_RANGE}")
        list(GET MUSASHI_ENTRY_PARTS 0 MUSASHI_ENTRY_NAME)
        list(GET MUSASHI_ENTRY_PARTS 1 MUSASHI_ENTRY_COUNT)
        set(MUSASHI_ENTRY_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/main/${MUSASHI_ENTRY_NAME}.c")
        set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${MUSASHI_ENTRY_SOURCE}")
        execute_process(
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                    ${MUSASHI_ENTRY_SOURCE} ${MUSASHI_GENERATED_DIR}/${MUSASHI_ENTRY_NAME}_words.inc
                    --expected-words ${MUSASHI_ENTRY_COUNT}
            RESULT_VARIABLE MUSASHI_ENTRY_WORDS_RESULT)
        if(NOT MUSASHI_ENTRY_WORDS_RESULT EQUAL 0)
            message(FATAL_ERROR "Cannot extract ${MUSASHI_ENTRY_NAME} entry words")
        endif()
    endforeach()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0007/800cf02c.c
                ${MUSASHI_GENERATED_DIR}/800cf02c_overlay_words.inc --expected-words 2259
        RESULT_VARIABLE MUSASHI_OV7_REMAINDER_WORDS_RESULT)
    if(NOT MUSASHI_OV7_REMAINDER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0007 800CF02C remainder words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cedfc.c
                ${MUSASHI_GENERATED_DIR}/800cedfc_overlay0010_words.inc --expected-words 194
        RESULT_VARIABLE MUSASHI_OV10_DISPATCH_WORDS_RESULT)
    if(NOT MUSASHI_OV10_DISPATCH_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800CEDFC words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cefd0.c
                ${MUSASHI_GENERATED_DIR}/800cefd0_overlay0010_words.inc --expected-words 77
        RESULT_VARIABLE MUSASHI_OV10_CEFD0_WORDS_RESULT)
    if(NOT MUSASHI_OV10_CEFD0_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800CEFD0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cf94c.c
                ${MUSASHI_GENERATED_DIR}/800cf94c_overlay0010_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_OV10_CF94C_WORDS_RESULT)
    if(NOT MUSASHI_OV10_CF94C_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800CF94C words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cfe60.c
                ${MUSASHI_GENERATED_DIR}/800cfe60_overlay0010_words.inc --expected-words 237
        RESULT_VARIABLE MUSASHI_OV10_CFE60_WORDS_RESULT)
    if(NOT MUSASHI_OV10_CFE60_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800CFE60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cfbf8.c
                ${MUSASHI_GENERATED_DIR}/800cfbf8_overlay0010_words.inc --expected-words 124
        RESULT_VARIABLE MUSASHI_OV10_CFBF8_WORDS_RESULT)
    if(NOT MUSASHI_OV10_CFBF8_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800CFBF8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cf4d4.c
                ${MUSASHI_GENERATED_DIR}/800cf4d4_overlay0010_words.inc --expected-words 204
        RESULT_VARIABLE MUSASHI_OV10_CF4D4_WORDS_RESULT)
    if(NOT MUSASHI_OV10_CF4D4_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800CF4D4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cf47c.c
                ${MUSASHI_GENERATED_DIR}/800cf47c_overlay0010_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_OV10_CF47C_WORDS_RESULT)
    if(NOT MUSASHI_OV10_CF47C_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800CF47C words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cf3b8.c
                ${MUSASHI_GENERATED_DIR}/800cf3b8_overlay0010_words.inc --expected-words 49
        RESULT_VARIABLE MUSASHI_OV10_CF3B8_WORDS_RESULT)
    if(NOT MUSASHI_OV10_CF3B8_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800CF3B8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cf398.c
                ${MUSASHI_GENERATED_DIR}/800cf398_overlay0010_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_OV10_CF398_WORDS_RESULT)
    if(NOT MUSASHI_OV10_CF398_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800CF398 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cf370.c
                ${MUSASHI_GENERATED_DIR}/800cf370_overlay0010_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_OV10_CF370_WORDS_RESULT)
    if(NOT MUSASHI_OV10_CF370_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800CF370 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800d0488.c
                ${MUSASHI_GENERATED_DIR}/800d0488_overlay0010_words.inc --expected-words 64
        RESULT_VARIABLE MUSASHI_OV10_D0488_WORDS_RESULT)
    if(NOT MUSASHI_OV10_D0488_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800D0488 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800d0630.c
                ${MUSASHI_GENERATED_DIR}/800d0630_overlay0010_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_OV10_800D0630_RESULT)
    if(NOT MUSASHI_OV10_800D0630_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN10 800d0630 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800d02c0.c
                ${MUSASHI_GENERATED_DIR}/800d02c0_overlay0010_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_OV10_800D02C0_RESULT)
    if(NOT MUSASHI_OV10_800D02C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN10 800d02c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800d1e20.c
                ${MUSASHI_GENERATED_DIR}/800d1e20_overlay0010_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_OV10_800D1E20_RESULT)
    if(NOT MUSASHI_OV10_800D1E20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN10 800d1e20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800d18dc.c
                ${MUSASHI_GENERATED_DIR}/800d18dc_overlay0010_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_OV10_800D18DC_RESULT)
    if(NOT MUSASHI_OV10_800D18DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN10 800d18dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800d1938.c
                ${MUSASHI_GENERATED_DIR}/800d1938_overlay0010_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_OV10_800D1938_RESULT)
    if(NOT MUSASHI_OV10_800D1938_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN10 800d1938 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800d1984.c
                ${MUSASHI_GENERATED_DIR}/800d1984_overlay0010_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_OV10_800D1984_RESULT)
    if(NOT MUSASHI_OV10_800D1984_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN10 800d1984 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800d1f58.c
                ${MUSASHI_GENERATED_DIR}/800d1f58_overlay0010_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_OV10_800D1F58_RESULT)
    if(NOT MUSASHI_OV10_800D1F58_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN10 800d1f58 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800d05e8.c
                ${MUSASHI_GENERATED_DIR}/800d05e8_overlay0010_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_OV10_800D05E8_RESULT)
    if(NOT MUSASHI_OV10_800D05E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN10 800d05e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800d0588.c
                ${MUSASHI_GENERATED_DIR}/800d0588_overlay0010_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_OV10_800D0588_RESULT)
    if(NOT MUSASHI_OV10_800D0588_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN10 800d0588 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cf854.c
                ${MUSASHI_GENERATED_DIR}/800cf854_overlay0010_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_OV10_800CF854_RESULT)
    if(NOT MUSASHI_OV10_800CF854_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN10 800cf854 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800d065c.c
                ${MUSASHI_GENERATED_DIR}/800d065c_overlay0010_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_OV10_800D065C_RESULT)
    if(NOT MUSASHI_OV10_800D065C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN10 800d065c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0010/800cfbbc.c
                ${MUSASHI_GENERATED_DIR}/800cfbbc_overlay0010_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_OV10_CFBBC_WORDS_RESULT)
    if(NOT MUSASHI_OV10_CFBBC_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0010 800CFBBC words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc01_0000/80128158.c
                ${MUSASHI_GENERATED_DIR}/80128158_sc01_0000_words.inc --expected-words 178
        RESULT_VARIABLE MUSASHI_SC01_80128158_RESULT)
    if(NOT MUSASHI_SC01_80128158_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC01 title 80128158 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128420.c
                ${MUSASHI_GENERATED_DIR}/80128420_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_80128420_RESULT)
    if(NOT MUSASHI_SC02_80128420_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128420 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80129220.c
                ${MUSASHI_GENERATED_DIR}/80129220_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80129220_RESULT)
    if(NOT MUSASHI_SC02_80129220_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80129220 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80129248.c
                ${MUSASHI_GENERATED_DIR}/80129248_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80129248_RESULT)
    if(NOT MUSASHI_SC02_80129248_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80129248 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80129258.c
                ${MUSASHI_GENERATED_DIR}/80129258_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80129258_RESULT)
    if(NOT MUSASHI_SC02_80129258_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80129258 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801378f0.c
                ${MUSASHI_GENERATED_DIR}/801378f0_sc02_0031_words.inc --expected-words 58
        RESULT_VARIABLE MUSASHI_SC02_801378F0_RESULT)
    if(NOT MUSASHI_SC02_801378F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801378f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013a860.c
                ${MUSASHI_GENERATED_DIR}/8013a860_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8013A860_RESULT)
    if(NOT MUSASHI_SC02_8013A860_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013a860 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128c14.c
                ${MUSASHI_GENERATED_DIR}/80128c14_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_80128C14_RESULT)
    if(NOT MUSASHI_SC02_80128C14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128c14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013c98c.c
                ${MUSASHI_GENERATED_DIR}/8013c98c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8013C98C_RESULT)
    if(NOT MUSASHI_SC02_8013C98C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013c98c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80129c40.c
                ${MUSASHI_GENERATED_DIR}/80129c40_sc02_0031_words.inc --expected-words 46
        RESULT_VARIABLE MUSASHI_SC02_80129C40_RESULT)
    if(NOT MUSASHI_SC02_80129C40_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80129c40 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80145cec.c
                ${MUSASHI_GENERATED_DIR}/80145cec_sc02_0031_words.inc --expected-words 127
        RESULT_VARIABLE MUSASHI_SC02_80145CEC_RESULT)
    if(NOT MUSASHI_SC02_80145CEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80145cec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801552f4.c
                ${MUSASHI_GENERATED_DIR}/801552f4_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_801552F4_RESULT)
    if(NOT MUSASHI_SC02_801552F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801552f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147084.c
                ${MUSASHI_GENERATED_DIR}/80147084_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80147084_RESULT)
    if(NOT MUSASHI_SC02_80147084_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147084 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147098.c
                ${MUSASHI_GENERATED_DIR}/80147098_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80147098_RESULT)
    if(NOT MUSASHI_SC02_80147098_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147098 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801470ac.c
                ${MUSASHI_GENERATED_DIR}/801470ac_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_801470AC_RESULT)
    if(NOT MUSASHI_SC02_801470AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801470ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149210.c
                ${MUSASHI_GENERATED_DIR}/80149210_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80149210_RESULT)
    if(NOT MUSASHI_SC02_80149210_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149210 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149228.c
                ${MUSASHI_GENERATED_DIR}/80149228_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80149228_RESULT)
    if(NOT MUSASHI_SC02_80149228_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149228 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149284.c
                ${MUSASHI_GENERATED_DIR}/80149284_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80149284_RESULT)
    if(NOT MUSASHI_SC02_80149284_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149284 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149290.c
                ${MUSASHI_GENERATED_DIR}/80149290_sc02_0031_words.inc --expected-words 48
        RESULT_VARIABLE MUSASHI_SC02_80149290_RESULT)
    if(NOT MUSASHI_SC02_80149290_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149290 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149350.c
                ${MUSASHI_GENERATED_DIR}/80149350_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80149350_RESULT)
    if(NOT MUSASHI_SC02_80149350_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149350 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149374.c
                ${MUSASHI_GENERATED_DIR}/80149374_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80149374_RESULT)
    if(NOT MUSASHI_SC02_80149374_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149374 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801493d0.c
                ${MUSASHI_GENERATED_DIR}/801493d0_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_801493D0_RESULT)
    if(NOT MUSASHI_SC02_801493D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801493d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014942c.c
                ${MUSASHI_GENERATED_DIR}/8014942c_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8014942C_RESULT)
    if(NOT MUSASHI_SC02_8014942C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014942c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149450.c
                ${MUSASHI_GENERATED_DIR}/80149450_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_80149450_RESULT)
    if(NOT MUSASHI_SC02_80149450_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149450 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801494cc.c
                ${MUSASHI_GENERATED_DIR}/801494cc_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_801494CC_RESULT)
    if(NOT MUSASHI_SC02_801494CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801494cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149544.c
                ${MUSASHI_GENERATED_DIR}/80149544_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80149544_RESULT)
    if(NOT MUSASHI_SC02_80149544_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149544 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149584.c
                ${MUSASHI_GENERATED_DIR}/80149584_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80149584_RESULT)
    if(NOT MUSASHI_SC02_80149584_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149584 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801495c4.c
                ${MUSASHI_GENERATED_DIR}/801495c4_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_801495C4_RESULT)
    if(NOT MUSASHI_SC02_801495C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801495c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014964c.c
                ${MUSASHI_GENERATED_DIR}/8014964c_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_8014964C_RESULT)
    if(NOT MUSASHI_SC02_8014964C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014964c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801496d4.c
                ${MUSASHI_GENERATED_DIR}/801496d4_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801496D4_RESULT)
    if(NOT MUSASHI_SC02_801496D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801496d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149704.c
                ${MUSASHI_GENERATED_DIR}/80149704_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80149704_RESULT)
    if(NOT MUSASHI_SC02_80149704_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149704 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149724.c
                ${MUSASHI_GENERATED_DIR}/80149724_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80149724_RESULT)
    if(NOT MUSASHI_SC02_80149724_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149724 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149744.c
                ${MUSASHI_GENERATED_DIR}/80149744_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80149744_RESULT)
    if(NOT MUSASHI_SC02_80149744_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149744 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149788.c
                ${MUSASHI_GENERATED_DIR}/80149788_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80149788_RESULT)
    if(NOT MUSASHI_SC02_80149788_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149788 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801497a8.c
                ${MUSASHI_GENERATED_DIR}/801497a8_sc02_0031_words.inc --expected-words 47
        RESULT_VARIABLE MUSASHI_SC02_801497A8_RESULT)
    if(NOT MUSASHI_SC02_801497A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801497a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149864.c
                ${MUSASHI_GENERATED_DIR}/80149864_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80149864_RESULT)
    if(NOT MUSASHI_SC02_80149864_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149864 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149884.c
                ${MUSASHI_GENERATED_DIR}/80149884_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80149884_RESULT)
    if(NOT MUSASHI_SC02_80149884_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149884 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801498c0.c
                ${MUSASHI_GENERATED_DIR}/801498c0_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801498C0_RESULT)
    if(NOT MUSASHI_SC02_801498C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801498c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801498e0.c
                ${MUSASHI_GENERATED_DIR}/801498e0_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_801498E0_RESULT)
    if(NOT MUSASHI_SC02_801498E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801498e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149954.c
                ${MUSASHI_GENERATED_DIR}/80149954_sc02_0031_words.inc --expected-words 68
        RESULT_VARIABLE MUSASHI_SC02_80149954_RESULT)
    if(NOT MUSASHI_SC02_80149954_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149954 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149a64.c
                ${MUSASHI_GENERATED_DIR}/80149a64_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80149A64_RESULT)
    if(NOT MUSASHI_SC02_80149A64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149a64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149aa8.c
                ${MUSASHI_GENERATED_DIR}/80149aa8_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80149AA8_RESULT)
    if(NOT MUSASHI_SC02_80149AA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149aa8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149ad4.c
                ${MUSASHI_GENERATED_DIR}/80149ad4_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80149AD4_RESULT)
    if(NOT MUSASHI_SC02_80149AD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149ad4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149b14.c
                ${MUSASHI_GENERATED_DIR}/80149b14_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80149B14_RESULT)
    if(NOT MUSASHI_SC02_80149B14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149b14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149b54.c
                ${MUSASHI_GENERATED_DIR}/80149b54_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80149B54_RESULT)
    if(NOT MUSASHI_SC02_80149B54_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149b54 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149bac.c
                ${MUSASHI_GENERATED_DIR}/80149bac_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80149BAC_RESULT)
    if(NOT MUSASHI_SC02_80149BAC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149bac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149bec.c
                ${MUSASHI_GENERATED_DIR}/80149bec_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_80149BEC_RESULT)
    if(NOT MUSASHI_SC02_80149BEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149bec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149c08.c
                ${MUSASHI_GENERATED_DIR}/80149c08_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_80149C08_RESULT)
    if(NOT MUSASHI_SC02_80149C08_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149c08 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149c94.c
                ${MUSASHI_GENERATED_DIR}/80149c94_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80149C94_RESULT)
    if(NOT MUSASHI_SC02_80149C94_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149c94 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149cb4.c
                ${MUSASHI_GENERATED_DIR}/80149cb4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80149CB4_RESULT)
    if(NOT MUSASHI_SC02_80149CB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149cb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149cd4.c
                ${MUSASHI_GENERATED_DIR}/80149cd4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80149CD4_RESULT)
    if(NOT MUSASHI_SC02_80149CD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149cd4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149d10.c
                ${MUSASHI_GENERATED_DIR}/80149d10_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_80149D10_RESULT)
    if(NOT MUSASHI_SC02_80149D10_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149d10 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149d9c.c
                ${MUSASHI_GENERATED_DIR}/80149d9c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80149D9C_RESULT)
    if(NOT MUSASHI_SC02_80149D9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149d9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149dd8.c
                ${MUSASHI_GENERATED_DIR}/80149dd8_sc02_0031_words.inc --expected-words 47
        RESULT_VARIABLE MUSASHI_SC02_80149DD8_RESULT)
    if(NOT MUSASHI_SC02_80149DD8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149dd8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149e94.c
                ${MUSASHI_GENERATED_DIR}/80149e94_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_80149E94_RESULT)
    if(NOT MUSASHI_SC02_80149E94_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149e94 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149f2c.c
                ${MUSASHI_GENERATED_DIR}/80149f2c_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_80149F2C_RESULT)
    if(NOT MUSASHI_SC02_80149F2C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149f2c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149fa8.c
                ${MUSASHI_GENERATED_DIR}/80149fa8_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80149FA8_RESULT)
    if(NOT MUSASHI_SC02_80149FA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149fa8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149fb0.c
                ${MUSASHI_GENERATED_DIR}/80149fb0_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_80149FB0_RESULT)
    if(NOT MUSASHI_SC02_80149FB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149fb0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a048.c
                ${MUSASHI_GENERATED_DIR}/8014a048_sc02_0031_words.inc --expected-words 90
        RESULT_VARIABLE MUSASHI_SC02_8014A048_RESULT)
    if(NOT MUSASHI_SC02_8014A048_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a048 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a1b0.c
                ${MUSASHI_GENERATED_DIR}/8014a1b0_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_8014A1B0_RESULT)
    if(NOT MUSASHI_SC02_8014A1B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a1b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a218.c
                ${MUSASHI_GENERATED_DIR}/8014a218_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8014A218_RESULT)
    if(NOT MUSASHI_SC02_8014A218_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a218 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a238.c
                ${MUSASHI_GENERATED_DIR}/8014a238_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_8014A238_RESULT)
    if(NOT MUSASHI_SC02_8014A238_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a238 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a2e4.c
                ${MUSASHI_GENERATED_DIR}/8014a2e4_sc02_0031_words.inc --expected-words 39
        RESULT_VARIABLE MUSASHI_SC02_8014A2E4_RESULT)
    if(NOT MUSASHI_SC02_8014A2E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a2e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a380.c
                ${MUSASHI_GENERATED_DIR}/8014a380_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8014A380_RESULT)
    if(NOT MUSASHI_SC02_8014A380_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a380 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a3e0.c
                ${MUSASHI_GENERATED_DIR}/8014a3e0_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_8014A3E0_RESULT)
    if(NOT MUSASHI_SC02_8014A3E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a3e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a454.c
                ${MUSASHI_GENERATED_DIR}/8014a454_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8014A454_RESULT)
    if(NOT MUSASHI_SC02_8014A454_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a454 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a4b4.c
                ${MUSASHI_GENERATED_DIR}/8014a4b4_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8014A4B4_RESULT)
    if(NOT MUSASHI_SC02_8014A4B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a4b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a4fc.c
                ${MUSASHI_GENERATED_DIR}/8014a4fc_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8014A4FC_RESULT)
    if(NOT MUSASHI_SC02_8014A4FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a4fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a51c.c
                ${MUSASHI_GENERATED_DIR}/8014a51c_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_8014A51C_RESULT)
    if(NOT MUSASHI_SC02_8014A51C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a51c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a59c.c
                ${MUSASHI_GENERATED_DIR}/8014a59c_sc02_0031_words.inc --expected-words 39
        RESULT_VARIABLE MUSASHI_SC02_8014A59C_RESULT)
    if(NOT MUSASHI_SC02_8014A59C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a59c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a638.c
                ${MUSASHI_GENERATED_DIR}/8014a638_sc02_0031_words.inc --expected-words 64
        RESULT_VARIABLE MUSASHI_SC02_8014A638_RESULT)
    if(NOT MUSASHI_SC02_8014A638_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a638 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a738.c
                ${MUSASHI_GENERATED_DIR}/8014a738_sc02_0031_words.inc --expected-words 70
        RESULT_VARIABLE MUSASHI_SC02_8014A738_RESULT)
    if(NOT MUSASHI_SC02_8014A738_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a738 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a850.c
                ${MUSASHI_GENERATED_DIR}/8014a850_sc02_0031_words.inc --expected-words 109
        RESULT_VARIABLE MUSASHI_SC02_8014A850_RESULT)
    if(NOT MUSASHI_SC02_8014A850_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a850 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014aa04.c
                ${MUSASHI_GENERATED_DIR}/8014aa04_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8014AA04_RESULT)
    if(NOT MUSASHI_SC02_8014AA04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014aa04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014aa28.c
                ${MUSASHI_GENERATED_DIR}/8014aa28_sc02_0031_words.inc --expected-words 77
        RESULT_VARIABLE MUSASHI_SC02_8014AA28_RESULT)
    if(NOT MUSASHI_SC02_8014AA28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014aa28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ab5c.c
                ${MUSASHI_GENERATED_DIR}/8014ab5c_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8014AB5C_RESULT)
    if(NOT MUSASHI_SC02_8014AB5C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ab5c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ab7c.c
                ${MUSASHI_GENERATED_DIR}/8014ab7c_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_8014AB7C_RESULT)
    if(NOT MUSASHI_SC02_8014AB7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ab7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014abf0.c
                ${MUSASHI_GENERATED_DIR}/8014abf0_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8014ABF0_RESULT)
    if(NOT MUSASHI_SC02_8014ABF0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014abf0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ac10.c
                ${MUSASHI_GENERATED_DIR}/8014ac10_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_8014AC10_RESULT)
    if(NOT MUSASHI_SC02_8014AC10_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ac10 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014acc0.c
                ${MUSASHI_GENERATED_DIR}/8014acc0_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8014ACC0_RESULT)
    if(NOT MUSASHI_SC02_8014ACC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014acc0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ace8.c
                ${MUSASHI_GENERATED_DIR}/8014ace8_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8014ACE8_RESULT)
    if(NOT MUSASHI_SC02_8014ACE8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ace8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ad30.c
                ${MUSASHI_GENERATED_DIR}/8014ad30_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8014AD30_RESULT)
    if(NOT MUSASHI_SC02_8014AD30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ad30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ad7c.c
                ${MUSASHI_GENERATED_DIR}/8014ad7c_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8014AD7C_RESULT)
    if(NOT MUSASHI_SC02_8014AD7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ad7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ada8.c
                ${MUSASHI_GENERATED_DIR}/8014ada8_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8014ADA8_RESULT)
    if(NOT MUSASHI_SC02_8014ADA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ada8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ade0.c
                ${MUSASHI_GENERATED_DIR}/8014ade0_sc02_0031_words.inc --expected-words 139
        RESULT_VARIABLE MUSASHI_SC02_8014ADE0_RESULT)
    if(NOT MUSASHI_SC02_8014ADE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ade0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b00c.c
                ${MUSASHI_GENERATED_DIR}/8014b00c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8014B00C_RESULT)
    if(NOT MUSASHI_SC02_8014B00C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b00c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b034.c
                ${MUSASHI_GENERATED_DIR}/8014b034_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8014B034_RESULT)
    if(NOT MUSASHI_SC02_8014B034_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b034 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b084.c
                ${MUSASHI_GENERATED_DIR}/8014b084_sc02_0031_words.inc --expected-words 42
        RESULT_VARIABLE MUSASHI_SC02_8014B084_RESULT)
    if(NOT MUSASHI_SC02_8014B084_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b084 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b12c.c
                ${MUSASHI_GENERATED_DIR}/8014b12c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8014B12C_RESULT)
    if(NOT MUSASHI_SC02_8014B12C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b12c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b154.c
                ${MUSASHI_GENERATED_DIR}/8014b154_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_8014B154_RESULT)
    if(NOT MUSASHI_SC02_8014B154_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b154 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b160.c
                ${MUSASHI_GENERATED_DIR}/8014b160_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8014B160_RESULT)
    if(NOT MUSASHI_SC02_8014B160_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b160 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b190.c
                ${MUSASHI_GENERATED_DIR}/8014b190_sc02_0031_words.inc --expected-words 70
        RESULT_VARIABLE MUSASHI_SC02_8014B190_RESULT)
    if(NOT MUSASHI_SC02_8014B190_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b190 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b2a8.c
                ${MUSASHI_GENERATED_DIR}/8014b2a8_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8014B2A8_RESULT)
    if(NOT MUSASHI_SC02_8014B2A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b2a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b2d0.c
                ${MUSASHI_GENERATED_DIR}/8014b2d0_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8014B2D0_RESULT)
    if(NOT MUSASHI_SC02_8014B2D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b2d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b2f8.c
                ${MUSASHI_GENERATED_DIR}/8014b2f8_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_8014B2F8_RESULT)
    if(NOT MUSASHI_SC02_8014B2F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b2f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b310.c
                ${MUSASHI_GENERATED_DIR}/8014b310_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8014B310_RESULT)
    if(NOT MUSASHI_SC02_8014B310_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b310 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b33c.c
                ${MUSASHI_GENERATED_DIR}/8014b33c_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8014B33C_RESULT)
    if(NOT MUSASHI_SC02_8014B33C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b33c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b350.c
                ${MUSASHI_GENERATED_DIR}/8014b350_sc02_0031_words.inc --expected-words 93
        RESULT_VARIABLE MUSASHI_SC02_8014B350_RESULT)
    if(NOT MUSASHI_SC02_8014B350_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b350 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b4c4.c
                ${MUSASHI_GENERATED_DIR}/8014b4c4_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014B4C4_RESULT)
    if(NOT MUSASHI_SC02_8014B4C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b4c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b4d4.c
                ${MUSASHI_GENERATED_DIR}/8014b4d4_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8014B4D4_RESULT)
    if(NOT MUSASHI_SC02_8014B4D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b4d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b504.c
                ${MUSASHI_GENERATED_DIR}/8014b504_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_8014B504_RESULT)
    if(NOT MUSASHI_SC02_8014B504_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b504 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b598.c
                ${MUSASHI_GENERATED_DIR}/8014b598_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_8014B598_RESULT)
    if(NOT MUSASHI_SC02_8014B598_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b598 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b5b0.c
                ${MUSASHI_GENERATED_DIR}/8014b5b0_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_8014B5B0_RESULT)
    if(NOT MUSASHI_SC02_8014B5B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b5b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b5b8.c
                ${MUSASHI_GENERATED_DIR}/8014b5b8_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_8014B5B8_RESULT)
    if(NOT MUSASHI_SC02_8014B5B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b5b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b5c4.c
                ${MUSASHI_GENERATED_DIR}/8014b5c4_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_8014B5C4_RESULT)
    if(NOT MUSASHI_SC02_8014B5C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b5c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b5d0.c
                ${MUSASHI_GENERATED_DIR}/8014b5d0_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_8014B5D0_RESULT)
    if(NOT MUSASHI_SC02_8014B5D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b5d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b5d8.c
                ${MUSASHI_GENERATED_DIR}/8014b5d8_sc02_0031_words.inc --expected-words 70
        RESULT_VARIABLE MUSASHI_SC02_8014B5D8_RESULT)
    if(NOT MUSASHI_SC02_8014B5D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b5d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b6f0.c
                ${MUSASHI_GENERATED_DIR}/8014b6f0_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_8014B6F0_RESULT)
    if(NOT MUSASHI_SC02_8014B6F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b6f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b768.c
                ${MUSASHI_GENERATED_DIR}/8014b768_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8014B768_RESULT)
    if(NOT MUSASHI_SC02_8014B768_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b768 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b7a4.c
                ${MUSASHI_GENERATED_DIR}/8014b7a4_sc02_0031_words.inc --expected-words 104
        RESULT_VARIABLE MUSASHI_SC02_8014B7A4_RESULT)
    if(NOT MUSASHI_SC02_8014B7A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b7a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014b944.c
                ${MUSASHI_GENERATED_DIR}/8014b944_sc02_0031_words.inc --expected-words 114
        RESULT_VARIABLE MUSASHI_SC02_8014B944_RESULT)
    if(NOT MUSASHI_SC02_8014B944_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014b944 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bb0c.c
                ${MUSASHI_GENERATED_DIR}/8014bb0c_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_8014BB0C_RESULT)
    if(NOT MUSASHI_SC02_8014BB0C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bb0c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bb24.c
                ${MUSASHI_GENERATED_DIR}/8014bb24_sc02_0031_words.inc --expected-words 58
        RESULT_VARIABLE MUSASHI_SC02_8014BB24_RESULT)
    if(NOT MUSASHI_SC02_8014BB24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bb24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bc0c.c
                ${MUSASHI_GENERATED_DIR}/8014bc0c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8014BC0C_RESULT)
    if(NOT MUSASHI_SC02_8014BC0C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bc0c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bc44.c
                ${MUSASHI_GENERATED_DIR}/8014bc44_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8014BC44_RESULT)
    if(NOT MUSASHI_SC02_8014BC44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bc44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bc80.c
                ${MUSASHI_GENERATED_DIR}/8014bc80_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8014BC80_RESULT)
    if(NOT MUSASHI_SC02_8014BC80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bc80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bcc0.c
                ${MUSASHI_GENERATED_DIR}/8014bcc0_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8014BCC0_RESULT)
    if(NOT MUSASHI_SC02_8014BCC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bcc0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bcec.c
                ${MUSASHI_GENERATED_DIR}/8014bcec_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8014BCEC_RESULT)
    if(NOT MUSASHI_SC02_8014BCEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bcec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bd24.c
                ${MUSASHI_GENERATED_DIR}/8014bd24_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8014BD24_RESULT)
    if(NOT MUSASHI_SC02_8014BD24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bd24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bd60.c
                ${MUSASHI_GENERATED_DIR}/8014bd60_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8014BD60_RESULT)
    if(NOT MUSASHI_SC02_8014BD60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bd60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bd98.c
                ${MUSASHI_GENERATED_DIR}/8014bd98_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8014BD98_RESULT)
    if(NOT MUSASHI_SC02_8014BD98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bd98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bdc8.c
                ${MUSASHI_GENERATED_DIR}/8014bdc8_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_8014BDC8_RESULT)
    if(NOT MUSASHI_SC02_8014BDC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bdc8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bde0.c
                ${MUSASHI_GENERATED_DIR}/8014bde0_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_8014BDE0_RESULT)
    if(NOT MUSASHI_SC02_8014BDE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bde0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bde8.c
                ${MUSASHI_GENERATED_DIR}/8014bde8_sc02_0031_words.inc --expected-words 36
        RESULT_VARIABLE MUSASHI_SC02_8014BDE8_RESULT)
    if(NOT MUSASHI_SC02_8014BDE8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bde8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014be78.c
                ${MUSASHI_GENERATED_DIR}/8014be78_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8014BE78_RESULT)
    if(NOT MUSASHI_SC02_8014BE78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014be78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014be9c.c
                ${MUSASHI_GENERATED_DIR}/8014be9c_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8014BE9C_RESULT)
    if(NOT MUSASHI_SC02_8014BE9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014be9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bec0.c
                ${MUSASHI_GENERATED_DIR}/8014bec0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8014BEC0_RESULT)
    if(NOT MUSASHI_SC02_8014BEC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bec0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bef8.c
                ${MUSASHI_GENERATED_DIR}/8014bef8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8014BEF8_RESULT)
    if(NOT MUSASHI_SC02_8014BEF8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bef8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bf18.c
                ${MUSASHI_GENERATED_DIR}/8014bf18_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8014BF18_RESULT)
    if(NOT MUSASHI_SC02_8014BF18_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bf18 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bf48.c
                ${MUSASHI_GENERATED_DIR}/8014bf48_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8014BF48_RESULT)
    if(NOT MUSASHI_SC02_8014BF48_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bf48 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bf6c.c
                ${MUSASHI_GENERATED_DIR}/8014bf6c_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8014BF6C_RESULT)
    if(NOT MUSASHI_SC02_8014BF6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bf6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bf8c.c
                ${MUSASHI_GENERATED_DIR}/8014bf8c_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8014BF8C_RESULT)
    if(NOT MUSASHI_SC02_8014BF8C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bf8c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bfb0.c
                ${MUSASHI_GENERATED_DIR}/8014bfb0_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8014BFB0_RESULT)
    if(NOT MUSASHI_SC02_8014BFB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bfb0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bfd4.c
                ${MUSASHI_GENERATED_DIR}/8014bfd4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8014BFD4_RESULT)
    if(NOT MUSASHI_SC02_8014BFD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bfd4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014bff4.c
                ${MUSASHI_GENERATED_DIR}/8014bff4_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_8014BFF4_RESULT)
    if(NOT MUSASHI_SC02_8014BFF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014bff4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c010.c
                ${MUSASHI_GENERATED_DIR}/8014c010_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8014C010_RESULT)
    if(NOT MUSASHI_SC02_8014C010_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c010 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c050.c
                ${MUSASHI_GENERATED_DIR}/8014c050_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8014C050_RESULT)
    if(NOT MUSASHI_SC02_8014C050_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c050 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c088.c
                ${MUSASHI_GENERATED_DIR}/8014c088_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8014C088_RESULT)
    if(NOT MUSASHI_SC02_8014C088_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c088 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c0c8.c
                ${MUSASHI_GENERATED_DIR}/8014c0c8_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8014C0C8_RESULT)
    if(NOT MUSASHI_SC02_8014C0C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c0c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c118.c
                ${MUSASHI_GENERATED_DIR}/8014c118_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8014C118_RESULT)
    if(NOT MUSASHI_SC02_8014C118_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c118 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c168.c
                ${MUSASHI_GENERATED_DIR}/8014c168_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8014C168_RESULT)
    if(NOT MUSASHI_SC02_8014C168_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c168 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c1a0.c
                ${MUSASHI_GENERATED_DIR}/8014c1a0_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8014C1A0_RESULT)
    if(NOT MUSASHI_SC02_8014C1A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c1a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c1c8.c
                ${MUSASHI_GENERATED_DIR}/8014c1c8_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_8014C1C8_RESULT)
    if(NOT MUSASHI_SC02_8014C1C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c1c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c278.c
                ${MUSASHI_GENERATED_DIR}/8014c278_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8014C278_RESULT)
    if(NOT MUSASHI_SC02_8014C278_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c278 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c2b0.c
                ${MUSASHI_GENERATED_DIR}/8014c2b0_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014C2B0_RESULT)
    if(NOT MUSASHI_SC02_8014C2B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c2b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c308.c
                ${MUSASHI_GENERATED_DIR}/8014c308_sc02_0031_words.inc --expected-words 39
        RESULT_VARIABLE MUSASHI_SC02_8014C308_RESULT)
    if(NOT MUSASHI_SC02_8014C308_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c308 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c3a4.c
                ${MUSASHI_GENERATED_DIR}/8014c3a4_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8014C3A4_RESULT)
    if(NOT MUSASHI_SC02_8014C3A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c3a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c3d0.c
                ${MUSASHI_GENERATED_DIR}/8014c3d0_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8014C3D0_RESULT)
    if(NOT MUSASHI_SC02_8014C3D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c3d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c43c.c
                ${MUSASHI_GENERATED_DIR}/8014c43c_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_8014C43C_RESULT)
    if(NOT MUSASHI_SC02_8014C43C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c43c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c4ac.c
                ${MUSASHI_GENERATED_DIR}/8014c4ac_sc02_0031_words.inc --expected-words 47
        RESULT_VARIABLE MUSASHI_SC02_8014C4AC_RESULT)
    if(NOT MUSASHI_SC02_8014C4AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c4ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c568.c
                ${MUSASHI_GENERATED_DIR}/8014c568_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8014C568_RESULT)
    if(NOT MUSASHI_SC02_8014C568_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c568 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c59c.c
                ${MUSASHI_GENERATED_DIR}/8014c59c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8014C59C_RESULT)
    if(NOT MUSASHI_SC02_8014C59C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c59c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c5d0.c
                ${MUSASHI_GENERATED_DIR}/8014c5d0_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8014C5D0_RESULT)
    if(NOT MUSASHI_SC02_8014C5D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c5d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c5fc.c
                ${MUSASHI_GENERATED_DIR}/8014c5fc_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_8014C5FC_RESULT)
    if(NOT MUSASHI_SC02_8014C5FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c5fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c6ac.c
                ${MUSASHI_GENERATED_DIR}/8014c6ac_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8014C6AC_RESULT)
    if(NOT MUSASHI_SC02_8014C6AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c6ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c6c0.c
                ${MUSASHI_GENERATED_DIR}/8014c6c0_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014C6C0_RESULT)
    if(NOT MUSASHI_SC02_8014C6C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c6c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c6e0.c
                ${MUSASHI_GENERATED_DIR}/8014c6e0_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8014C6E0_RESULT)
    if(NOT MUSASHI_SC02_8014C6E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c6e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c6f4.c
                ${MUSASHI_GENERATED_DIR}/8014c6f4_sc02_0031_words.inc --expected-words 91
        RESULT_VARIABLE MUSASHI_SC02_8014C6F4_RESULT)
    if(NOT MUSASHI_SC02_8014C6F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c6f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c860.c
                ${MUSASHI_GENERATED_DIR}/8014c860_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8014C860_RESULT)
    if(NOT MUSASHI_SC02_8014C860_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c860 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c88c.c
                ${MUSASHI_GENERATED_DIR}/8014c88c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8014C88C_RESULT)
    if(NOT MUSASHI_SC02_8014C88C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c88c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c8c8.c
                ${MUSASHI_GENERATED_DIR}/8014c8c8_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8014C8C8_RESULT)
    if(NOT MUSASHI_SC02_8014C8C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c8c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c8f0.c
                ${MUSASHI_GENERATED_DIR}/8014c8f0_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8014C8F0_RESULT)
    if(NOT MUSASHI_SC02_8014C8F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c8f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c918.c
                ${MUSASHI_GENERATED_DIR}/8014c918_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8014C918_RESULT)
    if(NOT MUSASHI_SC02_8014C918_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c918 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016533c.c
                ${MUSASHI_GENERATED_DIR}/8016533c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8016533C_RESULT)
    if(NOT MUSASHI_SC02_8016533C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016533c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801659dc.c
                ${MUSASHI_GENERATED_DIR}/801659dc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801659DC_RESULT)
    if(NOT MUSASHI_SC02_801659DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801659dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165a18.c
                ${MUSASHI_GENERATED_DIR}/80165a18_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80165A18_RESULT)
    if(NOT MUSASHI_SC02_80165A18_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165a18 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801627c0.c
                ${MUSASHI_GENERATED_DIR}/801627c0_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_801627C0_RESULT)
    if(NOT MUSASHI_SC02_801627C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801627c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162af4.c
                ${MUSASHI_GENERATED_DIR}/80162af4_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80162AF4_RESULT)
    if(NOT MUSASHI_SC02_80162AF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162af4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165c78.c
                ${MUSASHI_GENERATED_DIR}/80165c78_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80165C78_RESULT)
    if(NOT MUSASHI_SC02_80165C78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165c78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801468c8.c
                ${MUSASHI_GENERATED_DIR}/801468c8_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_801468C8_RESULT)
    if(NOT MUSASHI_SC02_801468C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801468c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80145ee8.c
                ${MUSASHI_GENERATED_DIR}/80145ee8_sc02_0031_words.inc --expected-words 75
        RESULT_VARIABLE MUSASHI_SC02_80145EE8_RESULT)
    if(NOT MUSASHI_SC02_80145EE8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80145ee8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146014.c
                ${MUSASHI_GENERATED_DIR}/80146014_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80146014_RESULT)
    if(NOT MUSASHI_SC02_80146014_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146014 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c968.c
                ${MUSASHI_GENERATED_DIR}/8014c968_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014C968_RESULT)
    if(NOT MUSASHI_SC02_8014C968_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c968 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c978.c
                ${MUSASHI_GENERATED_DIR}/8014c978_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8014C978_RESULT)
    if(NOT MUSASHI_SC02_8014C978_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c978 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c98c.c
                ${MUSASHI_GENERATED_DIR}/8014c98c_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014C98C_RESULT)
    if(NOT MUSASHI_SC02_8014C98C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c98c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c99c.c
                ${MUSASHI_GENERATED_DIR}/8014c99c_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_8014C99C_RESULT)
    if(NOT MUSASHI_SC02_8014C99C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c99c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ca00.c
                ${MUSASHI_GENERATED_DIR}/8014ca00_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8014CA00_RESULT)
    if(NOT MUSASHI_SC02_8014CA00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ca00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ca14.c
                ${MUSASHI_GENERATED_DIR}/8014ca14_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_8014CA14_RESULT)
    if(NOT MUSASHI_SC02_8014CA14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ca14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ca70.c
                ${MUSASHI_GENERATED_DIR}/8014ca70_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_8014CA70_RESULT)
    if(NOT MUSASHI_SC02_8014CA70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ca70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ca88.c
                ${MUSASHI_GENERATED_DIR}/8014ca88_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_8014CA88_RESULT)
    if(NOT MUSASHI_SC02_8014CA88_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ca88 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cae4.c
                ${MUSASHI_GENERATED_DIR}/8014cae4_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_8014CAE4_RESULT)
    if(NOT MUSASHI_SC02_8014CAE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cae4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cafc.c
                ${MUSASHI_GENERATED_DIR}/8014cafc_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014CAFC_RESULT)
    if(NOT MUSASHI_SC02_8014CAFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cafc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cb0c.c
                ${MUSASHI_GENERATED_DIR}/8014cb0c_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014CB0C_RESULT)
    if(NOT MUSASHI_SC02_8014CB0C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cb0c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cb1c.c
                ${MUSASHI_GENERATED_DIR}/8014cb1c_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014CB1C_RESULT)
    if(NOT MUSASHI_SC02_8014CB1C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cb1c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cb2c.c
                ${MUSASHI_GENERATED_DIR}/8014cb2c_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8014CB2C_RESULT)
    if(NOT MUSASHI_SC02_8014CB2C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cb2c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cb58.c
                ${MUSASHI_GENERATED_DIR}/8014cb58_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014CB58_RESULT)
    if(NOT MUSASHI_SC02_8014CB58_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cb58 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cb68.c
                ${MUSASHI_GENERATED_DIR}/8014cb68_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8014CB68_RESULT)
    if(NOT MUSASHI_SC02_8014CB68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cb68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cb7c.c
                ${MUSASHI_GENERATED_DIR}/8014cb7c_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014CB7C_RESULT)
    if(NOT MUSASHI_SC02_8014CB7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cb7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cb8c.c
                ${MUSASHI_GENERATED_DIR}/8014cb8c_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014CB8C_RESULT)
    if(NOT MUSASHI_SC02_8014CB8C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cb8c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cb9c.c
                ${MUSASHI_GENERATED_DIR}/8014cb9c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8014CB9C_RESULT)
    if(NOT MUSASHI_SC02_8014CB9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cb9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cbd8.c
                ${MUSASHI_GENERATED_DIR}/8014cbd8_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014CBD8_RESULT)
    if(NOT MUSASHI_SC02_8014CBD8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cbd8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cbe8.c
                ${MUSASHI_GENERATED_DIR}/8014cbe8_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014CBE8_RESULT)
    if(NOT MUSASHI_SC02_8014CBE8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cbe8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cbf8.c
                ${MUSASHI_GENERATED_DIR}/8014cbf8_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8014CBF8_RESULT)
    if(NOT MUSASHI_SC02_8014CBF8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cbf8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cc28.c
                ${MUSASHI_GENERATED_DIR}/8014cc28_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_8014CC28_RESULT)
    if(NOT MUSASHI_SC02_8014CC28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cc28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ccb4.c
                ${MUSASHI_GENERATED_DIR}/8014ccb4_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014CCB4_RESULT)
    if(NOT MUSASHI_SC02_8014CCB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ccb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cd0c.c
                ${MUSASHI_GENERATED_DIR}/8014cd0c_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_8014CD0C_RESULT)
    if(NOT MUSASHI_SC02_8014CD0C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cd0c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cd80.c
                ${MUSASHI_GENERATED_DIR}/8014cd80_sc02_0031_words.inc --expected-words 97
        RESULT_VARIABLE MUSASHI_SC02_8014CD80_RESULT)
    if(NOT MUSASHI_SC02_8014CD80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cd80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014cf04.c
                ${MUSASHI_GENERATED_DIR}/8014cf04_sc02_0031_words.inc --expected-words 82
        RESULT_VARIABLE MUSASHI_SC02_8014CF04_RESULT)
    if(NOT MUSASHI_SC02_8014CF04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014cf04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014d04c.c
                ${MUSASHI_GENERATED_DIR}/8014d04c_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014D04C_RESULT)
    if(NOT MUSASHI_SC02_8014D04C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014d04c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014d0a4.c
                ${MUSASHI_GENERATED_DIR}/8014d0a4_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_8014D0A4_RESULT)
    if(NOT MUSASHI_SC02_8014D0A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014d0a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014d12c.c
                ${MUSASHI_GENERATED_DIR}/8014d12c_sc02_0031_words.inc --expected-words 93
        RESULT_VARIABLE MUSASHI_SC02_8014D12C_RESULT)
    if(NOT MUSASHI_SC02_8014D12C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014d12c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014d2a0.c
                ${MUSASHI_GENERATED_DIR}/8014d2a0_sc02_0031_words.inc --expected-words 80
        RESULT_VARIABLE MUSASHI_SC02_8014D2A0_RESULT)
    if(NOT MUSASHI_SC02_8014D2A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014d2a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014d3e0.c
                ${MUSASHI_GENERATED_DIR}/8014d3e0_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014D3E0_RESULT)
    if(NOT MUSASHI_SC02_8014D3E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014d3e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014d438.c
                ${MUSASHI_GENERATED_DIR}/8014d438_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_8014D438_RESULT)
    if(NOT MUSASHI_SC02_8014D438_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014d438 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014d4c0.c
                ${MUSASHI_GENERATED_DIR}/8014d4c0_sc02_0031_words.inc --expected-words 84
        RESULT_VARIABLE MUSASHI_SC02_8014D4C0_RESULT)
    if(NOT MUSASHI_SC02_8014D4C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014d4c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014d610.c
                ${MUSASHI_GENERATED_DIR}/8014d610_sc02_0031_words.inc --expected-words 74
        RESULT_VARIABLE MUSASHI_SC02_8014D610_RESULT)
    if(NOT MUSASHI_SC02_8014D610_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014d610 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014d738.c
                ${MUSASHI_GENERATED_DIR}/8014d738_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014D738_RESULT)
    if(NOT MUSASHI_SC02_8014D738_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014d738 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014d790.c
                ${MUSASHI_GENERATED_DIR}/8014d790_sc02_0031_words.inc --expected-words 36
        RESULT_VARIABLE MUSASHI_SC02_8014D790_RESULT)
    if(NOT MUSASHI_SC02_8014D790_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014d790 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014d820.c
                ${MUSASHI_GENERATED_DIR}/8014d820_sc02_0031_words.inc --expected-words 304
        RESULT_VARIABLE MUSASHI_SC02_8014D820_RESULT)
    if(NOT MUSASHI_SC02_8014D820_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014d820 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014dce0.c
                ${MUSASHI_GENERATED_DIR}/8014dce0_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_8014DCE0_RESULT)
    if(NOT MUSASHI_SC02_8014DCE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014dce0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014dd8c.c
                ${MUSASHI_GENERATED_DIR}/8014dd8c_sc02_0031_words.inc --expected-words 108
        RESULT_VARIABLE MUSASHI_SC02_8014DD8C_RESULT)
    if(NOT MUSASHI_SC02_8014DD8C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014dd8c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014df3c.c
                ${MUSASHI_GENERATED_DIR}/8014df3c_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014DF3C_RESULT)
    if(NOT MUSASHI_SC02_8014DF3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014df3c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014df94.c
                ${MUSASHI_GENERATED_DIR}/8014df94_sc02_0031_words.inc --expected-words 45
        RESULT_VARIABLE MUSASHI_SC02_8014DF94_RESULT)
    if(NOT MUSASHI_SC02_8014DF94_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014df94 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e048.c
                ${MUSASHI_GENERATED_DIR}/8014e048_sc02_0031_words.inc --expected-words 143
        RESULT_VARIABLE MUSASHI_SC02_8014E048_RESULT)
    if(NOT MUSASHI_SC02_8014E048_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e048 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e284.c
                ${MUSASHI_GENERATED_DIR}/8014e284_sc02_0031_words.inc --expected-words 108
        RESULT_VARIABLE MUSASHI_SC02_8014E284_RESULT)
    if(NOT MUSASHI_SC02_8014E284_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e284 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e434.c
                ${MUSASHI_GENERATED_DIR}/8014e434_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014E434_RESULT)
    if(NOT MUSASHI_SC02_8014E434_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e434 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e48c.c
                ${MUSASHI_GENERATED_DIR}/8014e48c_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_8014E48C_RESULT)
    if(NOT MUSASHI_SC02_8014E48C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e48c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e514.c
                ${MUSASHI_GENERATED_DIR}/8014e514_sc02_0031_words.inc --expected-words 40
        RESULT_VARIABLE MUSASHI_SC02_8014E514_RESULT)
    if(NOT MUSASHI_SC02_8014E514_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e514 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e5b4.c
                ${MUSASHI_GENERATED_DIR}/8014e5b4_sc02_0031_words.inc --expected-words 59
        RESULT_VARIABLE MUSASHI_SC02_8014E5B4_RESULT)
    if(NOT MUSASHI_SC02_8014E5B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e5b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e6a0.c
                ${MUSASHI_GENERATED_DIR}/8014e6a0_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014E6A0_RESULT)
    if(NOT MUSASHI_SC02_8014E6A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e6a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e6f8.c
                ${MUSASHI_GENERATED_DIR}/8014e6f8_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_8014E6F8_RESULT)
    if(NOT MUSASHI_SC02_8014E6F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e6f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e790.c
                ${MUSASHI_GENERATED_DIR}/8014e790_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_8014E790_RESULT)
    if(NOT MUSASHI_SC02_8014E790_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e790 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e83c.c
                ${MUSASHI_GENERATED_DIR}/8014e83c_sc02_0031_words.inc --expected-words 62
        RESULT_VARIABLE MUSASHI_SC02_8014E83C_RESULT)
    if(NOT MUSASHI_SC02_8014E83C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e83c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014c6d0.c
                ${MUSASHI_GENERATED_DIR}/8014c6d0_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8014C6D0_RESULT)
    if(NOT MUSASHI_SC02_8014C6D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014c6d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165938.c
                ${MUSASHI_GENERATED_DIR}/80165938_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80165938_RESULT)
    if(NOT MUSASHI_SC02_80165938_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165938 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153c8c.c
                ${MUSASHI_GENERATED_DIR}/80153c8c_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80153C8C_RESULT)
    if(NOT MUSASHI_SC02_80153C8C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153c8c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144b9c.c
                ${MUSASHI_GENERATED_DIR}/80144b9c_sc02_0031_words.inc --expected-words 770
        RESULT_VARIABLE MUSASHI_SC02_80144B9C_RESULT)
    if(NOT MUSASHI_SC02_80144B9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144b9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801457a4.c
                ${MUSASHI_GENERATED_DIR}/801457a4_sc02_0031_words.inc --expected-words 79
        RESULT_VARIABLE MUSASHI_SC02_801457A4_RESULT)
    if(NOT MUSASHI_SC02_801457A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801457a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8018129c.c
                ${MUSASHI_GENERATED_DIR}/8018129c_sc02_0031_words.inc --expected-words 40
        RESULT_VARIABLE MUSASHI_SC02_8018129C_RESULT)
    if(NOT MUSASHI_SC02_8018129C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8018129c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a018.c
                ${MUSASHI_GENERATED_DIR}/8012a018_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8012A018_RESULT)
    if(NOT MUSASHI_SC02_8012A018_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a018 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a048.c
                ${MUSASHI_GENERATED_DIR}/8012a048_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8012A048_RESULT)
    if(NOT MUSASHI_SC02_8012A048_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a048 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a094.c
                ${MUSASHI_GENERATED_DIR}/8012a094_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8012A094_RESULT)
    if(NOT MUSASHI_SC02_8012A094_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a094 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8018133c.c
                ${MUSASHI_GENERATED_DIR}/8018133c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8018133C_RESULT)
    if(NOT MUSASHI_SC02_8018133C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8018133c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80181378.c
                ${MUSASHI_GENERATED_DIR}/80181378_sc02_0031_words.inc --expected-words 91
        RESULT_VARIABLE MUSASHI_SC02_80181378_RESULT)
    if(NOT MUSASHI_SC02_80181378_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80181378 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801814e4.c
                ${MUSASHI_GENERATED_DIR}/801814e4_sc02_0031_words.inc --expected-words 119
        RESULT_VARIABLE MUSASHI_SC02_801814E4_RESULT)
    if(NOT MUSASHI_SC02_801814E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801814e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148800.c
                ${MUSASHI_GENERATED_DIR}/80148800_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148800_RESULT)
    if(NOT MUSASHI_SC02_80148800_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148800 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014880c.c
                ${MUSASHI_GENERATED_DIR}/8014880c_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_8014880C_RESULT)
    if(NOT MUSASHI_SC02_8014880C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014880c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148818.c
                ${MUSASHI_GENERATED_DIR}/80148818_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148818_RESULT)
    if(NOT MUSASHI_SC02_80148818_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148818 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148824.c
                ${MUSASHI_GENERATED_DIR}/80148824_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_80148824_RESULT)
    if(NOT MUSASHI_SC02_80148824_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148824 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801488a8.c
                ${MUSASHI_GENERATED_DIR}/801488a8_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_801488A8_RESULT)
    if(NOT MUSASHI_SC02_801488A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801488a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014891c.c
                ${MUSASHI_GENERATED_DIR}/8014891c_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_8014891C_RESULT)
    if(NOT MUSASHI_SC02_8014891C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014891c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148980.c
                ${MUSASHI_GENERATED_DIR}/80148980_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_80148980_RESULT)
    if(NOT MUSASHI_SC02_80148980_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148980 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801489e8.c
                ${MUSASHI_GENERATED_DIR}/801489e8_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_801489E8_RESULT)
    if(NOT MUSASHI_SC02_801489E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801489e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148a48.c
                ${MUSASHI_GENERATED_DIR}/80148a48_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80148A48_RESULT)
    if(NOT MUSASHI_SC02_80148A48_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148a48 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148aac.c
                ${MUSASHI_GENERATED_DIR}/80148aac_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80148AAC_RESULT)
    if(NOT MUSASHI_SC02_80148AAC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148aac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148afc.c
                ${MUSASHI_GENERATED_DIR}/80148afc_sc02_0031_words.inc --expected-words 71
        RESULT_VARIABLE MUSASHI_SC02_80148AFC_RESULT)
    if(NOT MUSASHI_SC02_80148AFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148afc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148c18.c
                ${MUSASHI_GENERATED_DIR}/80148c18_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80148C18_RESULT)
    if(NOT MUSASHI_SC02_80148C18_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148c18 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148c20.c
                ${MUSASHI_GENERATED_DIR}/80148c20_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80148C20_RESULT)
    if(NOT MUSASHI_SC02_80148C20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148c20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148c34.c
                ${MUSASHI_GENERATED_DIR}/80148c34_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80148C34_RESULT)
    if(NOT MUSASHI_SC02_80148C34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148c34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148c4c.c
                ${MUSASHI_GENERATED_DIR}/80148c4c_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80148C4C_RESULT)
    if(NOT MUSASHI_SC02_80148C4C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148c4c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148c64.c
                ${MUSASHI_GENERATED_DIR}/80148c64_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80148C64_RESULT)
    if(NOT MUSASHI_SC02_80148C64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148c64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148c7c.c
                ${MUSASHI_GENERATED_DIR}/80148c7c_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80148C7C_RESULT)
    if(NOT MUSASHI_SC02_80148C7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148c7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148c84.c
                ${MUSASHI_GENERATED_DIR}/80148c84_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80148C84_RESULT)
    if(NOT MUSASHI_SC02_80148C84_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148c84 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148c9c.c
                ${MUSASHI_GENERATED_DIR}/80148c9c_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80148C9C_RESULT)
    if(NOT MUSASHI_SC02_80148C9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148c9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148cb4.c
                ${MUSASHI_GENERATED_DIR}/80148cb4_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80148CB4_RESULT)
    if(NOT MUSASHI_SC02_80148CB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148cb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148ccc.c
                ${MUSASHI_GENERATED_DIR}/80148ccc_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80148CCC_RESULT)
    if(NOT MUSASHI_SC02_80148CCC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148ccc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148ce4.c
                ${MUSASHI_GENERATED_DIR}/80148ce4_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80148CE4_RESULT)
    if(NOT MUSASHI_SC02_80148CE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148ce4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148cec.c
                ${MUSASHI_GENERATED_DIR}/80148cec_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80148CEC_RESULT)
    if(NOT MUSASHI_SC02_80148CEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148cec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148cf4.c
                ${MUSASHI_GENERATED_DIR}/80148cf4_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80148CF4_RESULT)
    if(NOT MUSASHI_SC02_80148CF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148cf4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148d0c.c
                ${MUSASHI_GENERATED_DIR}/80148d0c_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80148D0C_RESULT)
    if(NOT MUSASHI_SC02_80148D0C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148d0c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148d24.c
                ${MUSASHI_GENERATED_DIR}/80148d24_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80148D24_RESULT)
    if(NOT MUSASHI_SC02_80148D24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148d24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148d3c.c
                ${MUSASHI_GENERATED_DIR}/80148d3c_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80148D3C_RESULT)
    if(NOT MUSASHI_SC02_80148D3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148d3c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148d44.c
                ${MUSASHI_GENERATED_DIR}/80148d44_sc02_0031_words.inc --expected-words 68
        RESULT_VARIABLE MUSASHI_SC02_80148D44_RESULT)
    if(NOT MUSASHI_SC02_80148D44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148d44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148e54.c
                ${MUSASHI_GENERATED_DIR}/80148e54_sc02_0031_words.inc --expected-words 67
        RESULT_VARIABLE MUSASHI_SC02_80148E54_RESULT)
    if(NOT MUSASHI_SC02_80148E54_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148e54 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148f60.c
                ${MUSASHI_GENERATED_DIR}/80148f60_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80148F60_RESULT)
    if(NOT MUSASHI_SC02_80148F60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148f60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148f68.c
                ${MUSASHI_GENERATED_DIR}/80148f68_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148F68_RESULT)
    if(NOT MUSASHI_SC02_80148F68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148f68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148f74.c
                ${MUSASHI_GENERATED_DIR}/80148f74_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148F74_RESULT)
    if(NOT MUSASHI_SC02_80148F74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148f74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148f80.c
                ${MUSASHI_GENERATED_DIR}/80148f80_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148F80_RESULT)
    if(NOT MUSASHI_SC02_80148F80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148f80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148f8c.c
                ${MUSASHI_GENERATED_DIR}/80148f8c_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148F8C_RESULT)
    if(NOT MUSASHI_SC02_80148F8C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148f8c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148f98.c
                ${MUSASHI_GENERATED_DIR}/80148f98_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80148F98_RESULT)
    if(NOT MUSASHI_SC02_80148F98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148f98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148fa0.c
                ${MUSASHI_GENERATED_DIR}/80148fa0_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148FA0_RESULT)
    if(NOT MUSASHI_SC02_80148FA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148fa0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148fac.c
                ${MUSASHI_GENERATED_DIR}/80148fac_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148FAC_RESULT)
    if(NOT MUSASHI_SC02_80148FAC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148fac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148fb8.c
                ${MUSASHI_GENERATED_DIR}/80148fb8_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148FB8_RESULT)
    if(NOT MUSASHI_SC02_80148FB8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148fb8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148fc4.c
                ${MUSASHI_GENERATED_DIR}/80148fc4_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148FC4_RESULT)
    if(NOT MUSASHI_SC02_80148FC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148fc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148fd0.c
                ${MUSASHI_GENERATED_DIR}/80148fd0_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80148FD0_RESULT)
    if(NOT MUSASHI_SC02_80148FD0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148fd0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148fd8.c
                ${MUSASHI_GENERATED_DIR}/80148fd8_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80148FD8_RESULT)
    if(NOT MUSASHI_SC02_80148FD8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148fd8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148fe0.c
                ${MUSASHI_GENERATED_DIR}/80148fe0_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148FE0_RESULT)
    if(NOT MUSASHI_SC02_80148FE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148fe0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148fec.c
                ${MUSASHI_GENERATED_DIR}/80148fec_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148FEC_RESULT)
    if(NOT MUSASHI_SC02_80148FEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148fec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148ff8.c
                ${MUSASHI_GENERATED_DIR}/80148ff8_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80148FF8_RESULT)
    if(NOT MUSASHI_SC02_80148FF8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148ff8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149004.c
                ${MUSASHI_GENERATED_DIR}/80149004_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80149004_RESULT)
    if(NOT MUSASHI_SC02_80149004_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149004 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014900c.c
                ${MUSASHI_GENERATED_DIR}/8014900c_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8014900C_RESULT)
    if(NOT MUSASHI_SC02_8014900C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014900c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149020.c
                ${MUSASHI_GENERATED_DIR}/80149020_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80149020_RESULT)
    if(NOT MUSASHI_SC02_80149020_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149020 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149034.c
                ${MUSASHI_GENERATED_DIR}/80149034_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80149034_RESULT)
    if(NOT MUSASHI_SC02_80149034_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149034 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149048.c
                ${MUSASHI_GENERATED_DIR}/80149048_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80149048_RESULT)
    if(NOT MUSASHI_SC02_80149048_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149048 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014905c.c
                ${MUSASHI_GENERATED_DIR}/8014905c_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_8014905C_RESULT)
    if(NOT MUSASHI_SC02_8014905C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014905c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149078.c
                ${MUSASHI_GENERATED_DIR}/80149078_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_80149078_RESULT)
    if(NOT MUSASHI_SC02_80149078_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149078 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801490e0.c
                ${MUSASHI_GENERATED_DIR}/801490e0_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_801490E0_RESULT)
    if(NOT MUSASHI_SC02_801490E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801490e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801490e8.c
                ${MUSASHI_GENERATED_DIR}/801490e8_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_801490E8_RESULT)
    if(NOT MUSASHI_SC02_801490E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801490e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801490f0.c
                ${MUSASHI_GENERATED_DIR}/801490f0_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_801490F0_RESULT)
    if(NOT MUSASHI_SC02_801490F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801490f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801490f8.c
                ${MUSASHI_GENERATED_DIR}/801490f8_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_801490F8_RESULT)
    if(NOT MUSASHI_SC02_801490F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801490f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149184.c
                ${MUSASHI_GENERATED_DIR}/80149184_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80149184_RESULT)
    if(NOT MUSASHI_SC02_80149184_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149184 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801491c4.c
                ${MUSASHI_GENERATED_DIR}/801491c4_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801491C4_RESULT)
    if(NOT MUSASHI_SC02_801491C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801491c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80149204.c
                ${MUSASHI_GENERATED_DIR}/80149204_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80149204_RESULT)
    if(NOT MUSASHI_SC02_80149204_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80149204 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f14c.c
                ${MUSASHI_GENERATED_DIR}/8012f14c_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8012F14C_RESULT)
    if(NOT MUSASHI_SC02_8012F14C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f14c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80129398.c
                ${MUSASHI_GENERATED_DIR}/80129398_sc02_0031_words.inc --expected-words 36
        RESULT_VARIABLE MUSASHI_SC02_80129398_RESULT)
    if(NOT MUSASHI_SC02_80129398_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80129398 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012944c.c
                ${MUSASHI_GENERATED_DIR}/8012944c_sc02_0031_words.inc --expected-words 72
        RESULT_VARIABLE MUSASHI_SC02_8012944C_RESULT)
    if(NOT MUSASHI_SC02_8012944C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012944c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801336e8.c
                ${MUSASHI_GENERATED_DIR}/801336e8_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_801336E8_RESULT)
    if(NOT MUSASHI_SC02_801336E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801336e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80136bc4.c
                ${MUSASHI_GENERATED_DIR}/80136bc4_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80136BC4_RESULT)
    if(NOT MUSASHI_SC02_80136BC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80136bc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013b568.c
                ${MUSASHI_GENERATED_DIR}/8013b568_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8013B568_RESULT)
    if(NOT MUSASHI_SC02_8013B568_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013b568 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013c08c.c
                ${MUSASHI_GENERATED_DIR}/8013c08c_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8013C08C_RESULT)
    if(NOT MUSASHI_SC02_8013C08C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013c08c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013c0f8.c
                ${MUSASHI_GENERATED_DIR}/8013c0f8_sc02_0031_words.inc --expected-words 154
        RESULT_VARIABLE MUSASHI_SC02_8013C0F8_RESULT)
    if(NOT MUSASHI_SC02_8013C0F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013c0f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801832f4.c
                ${MUSASHI_GENERATED_DIR}/801832f4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801832F4_RESULT)
    if(NOT MUSASHI_SC02_801832F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801832f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80183314.c
                ${MUSASHI_GENERATED_DIR}/80183314_sc02_0031_words.inc --expected-words 81
        RESULT_VARIABLE MUSASHI_SC02_80183314_RESULT)
    if(NOT MUSASHI_SC02_80183314_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80183314 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80183458.c
                ${MUSASHI_GENERATED_DIR}/80183458_sc02_0031_words.inc --expected-words 236
        RESULT_VARIABLE MUSASHI_SC02_80183458_RESULT)
    if(NOT MUSASHI_SC02_80183458_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80183458 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80183808.c
                ${MUSASHI_GENERATED_DIR}/80183808_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80183808_RESULT)
    if(NOT MUSASHI_SC02_80183808_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80183808 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80183810.c
                ${MUSASHI_GENERATED_DIR}/80183810_sc02_0031_words.inc --expected-words 132
        RESULT_VARIABLE MUSASHI_SC02_80183810_RESULT)
    if(NOT MUSASHI_SC02_80183810_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80183810 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80183a20.c
                ${MUSASHI_GENERATED_DIR}/80183a20_sc02_0031_words.inc --expected-words 100
        RESULT_VARIABLE MUSASHI_SC02_80183A20_RESULT)
    if(NOT MUSASHI_SC02_80183A20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80183a20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80183bb0.c
                ${MUSASHI_GENERATED_DIR}/80183bb0_sc02_0031_words.inc --expected-words 117
        RESULT_VARIABLE MUSASHI_SC02_80183BB0_RESULT)
    if(NOT MUSASHI_SC02_80183BB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80183bb0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80183d84.c
                ${MUSASHI_GENERATED_DIR}/80183d84_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80183D84_RESULT)
    if(NOT MUSASHI_SC02_80183D84_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80183d84 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80183dc0.c
                ${MUSASHI_GENERATED_DIR}/80183dc0_sc02_0031_words.inc --expected-words 139
        RESULT_VARIABLE MUSASHI_SC02_80183DC0_RESULT)
    if(NOT MUSASHI_SC02_80183DC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80183dc0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80183fec.c
                ${MUSASHI_GENERATED_DIR}/80183fec_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80183FEC_RESULT)
    if(NOT MUSASHI_SC02_80183FEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80183fec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80184028.c
                ${MUSASHI_GENERATED_DIR}/80184028_sc02_0031_words.inc --expected-words 89
        RESULT_VARIABLE MUSASHI_SC02_80184028_RESULT)
    if(NOT MUSASHI_SC02_80184028_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80184028 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8018418c.c
                ${MUSASHI_GENERATED_DIR}/8018418c_sc02_0031_words.inc --expected-words 99
        RESULT_VARIABLE MUSASHI_SC02_8018418C_RESULT)
    if(NOT MUSASHI_SC02_8018418C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8018418c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80184318.c
                ${MUSASHI_GENERATED_DIR}/80184318_sc02_0031_words.inc --expected-words 54
        RESULT_VARIABLE MUSASHI_SC02_80184318_RESULT)
    if(NOT MUSASHI_SC02_80184318_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80184318 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80181868.c
                ${MUSASHI_GENERATED_DIR}/80181868_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80181868_RESULT)
    if(NOT MUSASHI_SC02_80181868_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80181868 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80181938.c
                ${MUSASHI_GENERATED_DIR}/80181938_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_80181938_RESULT)
    if(NOT MUSASHI_SC02_80181938_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80181938 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801843b4.c
                ${MUSASHI_GENERATED_DIR}/801843b4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801843B4_RESULT)
    if(NOT MUSASHI_SC02_801843B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801843b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801843f0.c
                ${MUSASHI_GENERATED_DIR}/801843f0_sc02_0031_words.inc --expected-words 53
        RESULT_VARIABLE MUSASHI_SC02_801843F0_RESULT)
    if(NOT MUSASHI_SC02_801843F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801843f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801844c4.c
                ${MUSASHI_GENERATED_DIR}/801844c4_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_801844C4_RESULT)
    if(NOT MUSASHI_SC02_801844C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801844c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801844ec.c
                ${MUSASHI_GENERATED_DIR}/801844ec_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_801844EC_RESULT)
    if(NOT MUSASHI_SC02_801844EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801844ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801844f4.c
                ${MUSASHI_GENERATED_DIR}/801844f4_sc02_0031_words.inc --expected-words 83
        RESULT_VARIABLE MUSASHI_SC02_801844F4_RESULT)
    if(NOT MUSASHI_SC02_801844F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801844f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80184640.c
                ${MUSASHI_GENERATED_DIR}/80184640_sc02_0031_words.inc --expected-words 72
        RESULT_VARIABLE MUSASHI_SC02_80184640_RESULT)
    if(NOT MUSASHI_SC02_80184640_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80184640 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c354.c
                ${MUSASHI_GENERATED_DIR}/8012c354_sc02_0031_words.inc --expected-words 57
        RESULT_VARIABLE MUSASHI_SC02_8012C354_RESULT)
    if(NOT MUSASHI_SC02_8012C354_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c354 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801788b8.c
                ${MUSASHI_GENERATED_DIR}/801788b8_sc02_0031_words.inc --expected-words 46
        RESULT_VARIABLE MUSASHI_SC02_801788B8_RESULT)
    if(NOT MUSASHI_SC02_801788B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801788b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c658.c
                ${MUSASHI_GENERATED_DIR}/8012c658_sc02_0031_words.inc --expected-words 62
        RESULT_VARIABLE MUSASHI_SC02_8012C658_RESULT)
    if(NOT MUSASHI_SC02_8012C658_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c658 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e8e0.c
                ${MUSASHI_GENERATED_DIR}/8012e8e0_sc02_0031_words.inc --expected-words 56
        RESULT_VARIABLE MUSASHI_SC02_8012E8E0_RESULT)
    if(NOT MUSASHI_SC02_8012E8E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e8e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144988.c
                ${MUSASHI_GENERATED_DIR}/80144988_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80144988_RESULT)
    if(NOT MUSASHI_SC02_80144988_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144988 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801449c8.c
                ${MUSASHI_GENERATED_DIR}/801449c8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801449C8_RESULT)
    if(NOT MUSASHI_SC02_801449C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801449c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144a04.c
                ${MUSASHI_GENERATED_DIR}/80144a04_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80144A04_RESULT)
    if(NOT MUSASHI_SC02_80144A04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144a04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144a2c.c
                ${MUSASHI_GENERATED_DIR}/80144a2c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80144A2C_RESULT)
    if(NOT MUSASHI_SC02_80144A2C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144a2c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144a68.c
                ${MUSASHI_GENERATED_DIR}/80144a68_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80144A68_RESULT)
    if(NOT MUSASHI_SC02_80144A68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144a68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144a90.c
                ${MUSASHI_GENERATED_DIR}/80144a90_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80144A90_RESULT)
    if(NOT MUSASHI_SC02_80144A90_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144a90 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144a98.c
                ${MUSASHI_GENERATED_DIR}/80144a98_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80144A98_RESULT)
    if(NOT MUSASHI_SC02_80144A98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144a98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144aec.c
                ${MUSASHI_GENERATED_DIR}/80144aec_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80144AEC_RESULT)
    if(NOT MUSASHI_SC02_80144AEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144aec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144b14.c
                ${MUSASHI_GENERATED_DIR}/80144b14_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_80144B14_RESULT)
    if(NOT MUSASHI_SC02_80144B14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144b14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ad44.c
                ${MUSASHI_GENERATED_DIR}/8012ad44_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_8012AD44_RESULT)
    if(NOT MUSASHI_SC02_8012AD44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ad44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801848a8.c
                ${MUSASHI_GENERATED_DIR}/801848a8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801848A8_RESULT)
    if(NOT MUSASHI_SC02_801848A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801848a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801848e4.c
                ${MUSASHI_GENERATED_DIR}/801848e4_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_801848E4_RESULT)
    if(NOT MUSASHI_SC02_801848E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801848e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8018496c.c
                ${MUSASHI_GENERATED_DIR}/8018496c_sc02_0031_words.inc --expected-words 48
        RESULT_VARIABLE MUSASHI_SC02_8018496C_RESULT)
    if(NOT MUSASHI_SC02_8018496C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8018496c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80184a2c.c
                ${MUSASHI_GENERATED_DIR}/80184a2c_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80184A2C_RESULT)
    if(NOT MUSASHI_SC02_80184A2C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80184a2c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80184a9c.c
                ${MUSASHI_GENERATED_DIR}/80184a9c_sc02_0031_words.inc --expected-words 62
        RESULT_VARIABLE MUSASHI_SC02_80184A9C_RESULT)
    if(NOT MUSASHI_SC02_80184A9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80184a9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80184b94.c
                ${MUSASHI_GENERATED_DIR}/80184b94_sc02_0031_words.inc --expected-words 36
        RESULT_VARIABLE MUSASHI_SC02_80184B94_RESULT)
    if(NOT MUSASHI_SC02_80184B94_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80184b94 words")
    endif()
        execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143970.c
                ${MUSASHI_GENERATED_DIR}/80143970_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_80143970_RESULT)
    if(NOT MUSASHI_SC02_80143970_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143970 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801439fc.c
                ${MUSASHI_GENERATED_DIR}/801439fc_sc02_0031_words.inc --expected-words 92
        RESULT_VARIABLE MUSASHI_SC02_801439FC_RESULT)
    if(NOT MUSASHI_SC02_801439FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801439fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143b6c.c
                ${MUSASHI_GENERATED_DIR}/80143b6c_sc02_0031_words.inc --expected-words 90
        RESULT_VARIABLE MUSASHI_SC02_80143B6C_RESULT)
    if(NOT MUSASHI_SC02_80143B6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143b6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143cd4.c
                ${MUSASHI_GENERATED_DIR}/80143cd4_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80143CD4_RESULT)
    if(NOT MUSASHI_SC02_80143CD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143cd4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143d28.c
                ${MUSASHI_GENERATED_DIR}/80143d28_sc02_0031_words.inc --expected-words 99
        RESULT_VARIABLE MUSASHI_SC02_80143D28_RESULT)
    if(NOT MUSASHI_SC02_80143D28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143d28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143eb4.c
                ${MUSASHI_GENERATED_DIR}/80143eb4_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80143EB4_RESULT)
    if(NOT MUSASHI_SC02_80143EB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143eb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143ebc.c
                ${MUSASHI_GENERATED_DIR}/80143ebc_sc02_0031_words.inc --expected-words 102
        RESULT_VARIABLE MUSASHI_SC02_80143EBC_RESULT)
    if(NOT MUSASHI_SC02_80143EBC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143ebc words")
    endif()
execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144054.c
                ${MUSASHI_GENERATED_DIR}/80144054_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80144054_RESULT)
    if(NOT MUSASHI_SC02_80144054_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144054 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144090.c
                ${MUSASHI_GENERATED_DIR}/80144090_sc02_0031_words.inc --expected-words 154
        RESULT_VARIABLE MUSASHI_SC02_80144090_RESULT)
    if(NOT MUSASHI_SC02_80144090_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144090 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801442f8.c
                ${MUSASHI_GENERATED_DIR}/801442f8_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_801442F8_RESULT)
    if(NOT MUSASHI_SC02_801442F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801442f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144364.c
                ${MUSASHI_GENERATED_DIR}/80144364_sc02_0031_words.inc --expected-words 61
        RESULT_VARIABLE MUSASHI_SC02_80144364_RESULT)
    if(NOT MUSASHI_SC02_80144364_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144364 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144458.c
                ${MUSASHI_GENERATED_DIR}/80144458_sc02_0031_words.inc --expected-words 64
        RESULT_VARIABLE MUSASHI_SC02_80144458_RESULT)
    if(NOT MUSASHI_SC02_80144458_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144458 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144558.c
                ${MUSASHI_GENERATED_DIR}/80144558_sc02_0031_words.inc --expected-words 53
        RESULT_VARIABLE MUSASHI_SC02_80144558_RESULT)
    if(NOT MUSASHI_SC02_80144558_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144558 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014462c.c
                ${MUSASHI_GENERATED_DIR}/8014462c_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_8014462C_RESULT)
    if(NOT MUSASHI_SC02_8014462C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014462c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801446a4.c
                ${MUSASHI_GENERATED_DIR}/801446a4_sc02_0031_words.inc --expected-words 54
        RESULT_VARIABLE MUSASHI_SC02_801446A4_RESULT)
    if(NOT MUSASHI_SC02_801446A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801446a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014477c.c
                ${MUSASHI_GENERATED_DIR}/8014477c_sc02_0031_words.inc --expected-words 65
        RESULT_VARIABLE MUSASHI_SC02_8014477C_RESULT)
    if(NOT MUSASHI_SC02_8014477C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014477c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80144880.c
                ${MUSASHI_GENERATED_DIR}/80144880_sc02_0031_words.inc --expected-words 66
        RESULT_VARIABLE MUSASHI_SC02_80144880_RESULT)
    if(NOT MUSASHI_SC02_80144880_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80144880 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801458e0.c
                ${MUSASHI_GENERATED_DIR}/801458e0_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_801458E0_RESULT)
    if(NOT MUSASHI_SC02_801458E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801458e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801458e8.c
                ${MUSASHI_GENERATED_DIR}/801458e8_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_801458E8_RESULT)
    if(NOT MUSASHI_SC02_801458E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801458e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80145934.c
                ${MUSASHI_GENERATED_DIR}/80145934_sc02_0031_words.inc --expected-words 62
        RESULT_VARIABLE MUSASHI_SC02_80145934_RESULT)
    if(NOT MUSASHI_SC02_80145934_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80145934 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80145a2c.c
                ${MUSASHI_GENERATED_DIR}/80145a2c_sc02_0031_words.inc --expected-words 62
        RESULT_VARIABLE MUSASHI_SC02_80145A2C_RESULT)
    if(NOT MUSASHI_SC02_80145A2C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80145a2c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80145b24.c
                ${MUSASHI_GENERATED_DIR}/80145b24_sc02_0031_words.inc --expected-words 53
        RESULT_VARIABLE MUSASHI_SC02_80145B24_RESULT)
    if(NOT MUSASHI_SC02_80145B24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80145b24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80145bf8.c
                ${MUSASHI_GENERATED_DIR}/80145bf8_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80145BF8_RESULT)
    if(NOT MUSASHI_SC02_80145BF8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80145bf8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80145c54.c
                ${MUSASHI_GENERATED_DIR}/80145c54_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_80145C54_RESULT)
    if(NOT MUSASHI_SC02_80145C54_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80145c54 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014607c.c
                ${MUSASHI_GENERATED_DIR}/8014607c_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_8014607C_RESULT)
    if(NOT MUSASHI_SC02_8014607C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014607c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146128.c
                ${MUSASHI_GENERATED_DIR}/80146128_sc02_0031_words.inc --expected-words 142
        RESULT_VARIABLE MUSASHI_SC02_80146128_RESULT)
    if(NOT MUSASHI_SC02_80146128_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146128 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146360.c
                ${MUSASHI_GENERATED_DIR}/80146360_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80146360_RESULT)
    if(NOT MUSASHI_SC02_80146360_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146360 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801463a0.c
                ${MUSASHI_GENERATED_DIR}/801463a0_sc02_0031_words.inc --expected-words 101
        RESULT_VARIABLE MUSASHI_SC02_801463A0_RESULT)
    if(NOT MUSASHI_SC02_801463A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801463a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146534.c
                ${MUSASHI_GENERATED_DIR}/80146534_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80146534_RESULT)
    if(NOT MUSASHI_SC02_80146534_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146534 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146554.c
                ${MUSASHI_GENERATED_DIR}/80146554_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80146554_RESULT)
    if(NOT MUSASHI_SC02_80146554_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146554 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146578.c
                ${MUSASHI_GENERATED_DIR}/80146578_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80146578_RESULT)
    if(NOT MUSASHI_SC02_80146578_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146578 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014659c.c
                ${MUSASHI_GENERATED_DIR}/8014659c_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8014659C_RESULT)
    if(NOT MUSASHI_SC02_8014659C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014659c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801465c0.c
                ${MUSASHI_GENERATED_DIR}/801465c0_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_801465C0_RESULT)
    if(NOT MUSASHI_SC02_801465C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801465c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801465e4.c
                ${MUSASHI_GENERATED_DIR}/801465e4_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_801465E4_RESULT)
    if(NOT MUSASHI_SC02_801465E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801465e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146608.c
                ${MUSASHI_GENERATED_DIR}/80146608_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_80146608_RESULT)
    if(NOT MUSASHI_SC02_80146608_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146608 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801466b4.c
                ${MUSASHI_GENERATED_DIR}/801466b4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801466B4_RESULT)
    if(NOT MUSASHI_SC02_801466B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801466b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801466f0.c
                ${MUSASHI_GENERATED_DIR}/801466f0_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_801466F0_RESULT)
    if(NOT MUSASHI_SC02_801466F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801466f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146750.c
                ${MUSASHI_GENERATED_DIR}/80146750_sc02_0031_words.inc --expected-words 47
        RESULT_VARIABLE MUSASHI_SC02_80146750_RESULT)
    if(NOT MUSASHI_SC02_80146750_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146750 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014680c.c
                ${MUSASHI_GENERATED_DIR}/8014680c_sc02_0031_words.inc --expected-words 47
        RESULT_VARIABLE MUSASHI_SC02_8014680C_RESULT)
    if(NOT MUSASHI_SC02_8014680C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014680c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146924.c
                ${MUSASHI_GENERATED_DIR}/80146924_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80146924_RESULT)
    if(NOT MUSASHI_SC02_80146924_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146924 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146994.c
                ${MUSASHI_GENERATED_DIR}/80146994_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80146994_RESULT)
    if(NOT MUSASHI_SC02_80146994_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146994 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801469c8.c
                ${MUSASHI_GENERATED_DIR}/801469c8_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_801469C8_RESULT)
    if(NOT MUSASHI_SC02_801469C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801469c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146a6c.c
                ${MUSASHI_GENERATED_DIR}/80146a6c_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80146A6C_RESULT)
    if(NOT MUSASHI_SC02_80146A6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146a6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146ab4.c
                ${MUSASHI_GENERATED_DIR}/80146ab4_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80146AB4_RESULT)
    if(NOT MUSASHI_SC02_80146AB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146ab4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146afc.c
                ${MUSASHI_GENERATED_DIR}/80146afc_sc02_0031_words.inc --expected-words 40
        RESULT_VARIABLE MUSASHI_SC02_80146AFC_RESULT)
    if(NOT MUSASHI_SC02_80146AFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146afc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146b9c.c
                ${MUSASHI_GENERATED_DIR}/80146b9c_sc02_0031_words.inc --expected-words 40
        RESULT_VARIABLE MUSASHI_SC02_80146B9C_RESULT)
    if(NOT MUSASHI_SC02_80146B9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146b9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146c3c.c
                ${MUSASHI_GENERATED_DIR}/80146c3c_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80146C3C_RESULT)
    if(NOT MUSASHI_SC02_80146C3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146c3c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146c98.c
                ${MUSASHI_GENERATED_DIR}/80146c98_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80146C98_RESULT)
    if(NOT MUSASHI_SC02_80146C98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146c98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146ca0.c
                ${MUSASHI_GENERATED_DIR}/80146ca0_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80146CA0_RESULT)
    if(NOT MUSASHI_SC02_80146CA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146ca0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146cb4.c
                ${MUSASHI_GENERATED_DIR}/80146cb4_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80146CB4_RESULT)
    if(NOT MUSASHI_SC02_80146CB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146cb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146cc8.c
                ${MUSASHI_GENERATED_DIR}/80146cc8_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_80146CC8_RESULT)
    if(NOT MUSASHI_SC02_80146CC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146cc8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146d30.c
                ${MUSASHI_GENERATED_DIR}/80146d30_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80146D30_RESULT)
    if(NOT MUSASHI_SC02_80146D30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146d30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146d80.c
                ${MUSASHI_GENERATED_DIR}/80146d80_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80146D80_RESULT)
    if(NOT MUSASHI_SC02_80146D80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146d80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146d90.c
                ${MUSASHI_GENERATED_DIR}/80146d90_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80146D90_RESULT)
    if(NOT MUSASHI_SC02_80146D90_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146d90 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146db8.c
                ${MUSASHI_GENERATED_DIR}/80146db8_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80146DB8_RESULT)
    if(NOT MUSASHI_SC02_80146DB8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146db8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146de8.c
                ${MUSASHI_GENERATED_DIR}/80146de8_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80146DE8_RESULT)
    if(NOT MUSASHI_SC02_80146DE8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146de8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146df8.c
                ${MUSASHI_GENERATED_DIR}/80146df8_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_80146DF8_RESULT)
    if(NOT MUSASHI_SC02_80146DF8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146df8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146e90.c
                ${MUSASHI_GENERATED_DIR}/80146e90_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80146E90_RESULT)
    if(NOT MUSASHI_SC02_80146E90_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146e90 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146e98.c
                ${MUSASHI_GENERATED_DIR}/80146e98_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80146E98_RESULT)
    if(NOT MUSASHI_SC02_80146E98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146e98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146ec0.c
                ${MUSASHI_GENERATED_DIR}/80146ec0_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_80146EC0_RESULT)
    if(NOT MUSASHI_SC02_80146EC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146ec0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146f58.c
                ${MUSASHI_GENERATED_DIR}/80146f58_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80146F58_RESULT)
    if(NOT MUSASHI_SC02_80146F58_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146f58 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146fc4.c
                ${MUSASHI_GENERATED_DIR}/80146fc4_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_80146FC4_RESULT)
    if(NOT MUSASHI_SC02_80146FC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146fc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014704c.c
                ${MUSASHI_GENERATED_DIR}/8014704c_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_8014704C_RESULT)
    if(NOT MUSASHI_SC02_8014704C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014704c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147054.c
                ${MUSASHI_GENERATED_DIR}/80147054_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80147054_RESULT)
    if(NOT MUSASHI_SC02_80147054_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147054 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147060.c
                ${MUSASHI_GENERATED_DIR}/80147060_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80147060_RESULT)
    if(NOT MUSASHI_SC02_80147060_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147060 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014706c.c
                ${MUSASHI_GENERATED_DIR}/8014706c_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_8014706C_RESULT)
    if(NOT MUSASHI_SC02_8014706C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014706c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147078.c
                ${MUSASHI_GENERATED_DIR}/80147078_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80147078_RESULT)
    if(NOT MUSASHI_SC02_80147078_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147078 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014708c.c
                ${MUSASHI_GENERATED_DIR}/8014708c_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_8014708C_RESULT)
    if(NOT MUSASHI_SC02_8014708C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014708c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801470a0.c
                ${MUSASHI_GENERATED_DIR}/801470a0_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_801470A0_RESULT)
    if(NOT MUSASHI_SC02_801470A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801470a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801470b4.c
                ${MUSASHI_GENERATED_DIR}/801470b4_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_801470B4_RESULT)
    if(NOT MUSASHI_SC02_801470B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801470b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801470c0.c
                ${MUSASHI_GENERATED_DIR}/801470c0_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_801470C0_RESULT)
    if(NOT MUSASHI_SC02_801470C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801470c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147118.c
                ${MUSASHI_GENERATED_DIR}/80147118_sc02_0031_words.inc --expected-words 83
        RESULT_VARIABLE MUSASHI_SC02_80147118_RESULT)
    if(NOT MUSASHI_SC02_80147118_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147118 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147264.c
                ${MUSASHI_GENERATED_DIR}/80147264_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80147264_RESULT)
    if(NOT MUSASHI_SC02_80147264_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147264 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147290.c
                ${MUSASHI_GENERATED_DIR}/80147290_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80147290_RESULT)
    if(NOT MUSASHI_SC02_80147290_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147290 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801472b4.c
                ${MUSASHI_GENERATED_DIR}/801472b4_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801472B4_RESULT)
    if(NOT MUSASHI_SC02_801472B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801472b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801472c8.c
                ${MUSASHI_GENERATED_DIR}/801472c8_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801472C8_RESULT)
    if(NOT MUSASHI_SC02_801472C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801472c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801472dc.c
                ${MUSASHI_GENERATED_DIR}/801472dc_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801472DC_RESULT)
    if(NOT MUSASHI_SC02_801472DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801472dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801472f0.c
                ${MUSASHI_GENERATED_DIR}/801472f0_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_801472F0_RESULT)
    if(NOT MUSASHI_SC02_801472F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801472f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147300.c
                ${MUSASHI_GENERATED_DIR}/80147300_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80147300_RESULT)
    if(NOT MUSASHI_SC02_80147300_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147300 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147324.c
                ${MUSASHI_GENERATED_DIR}/80147324_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80147324_RESULT)
    if(NOT MUSASHI_SC02_80147324_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147324 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147364.c
                ${MUSASHI_GENERATED_DIR}/80147364_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_80147364_RESULT)
    if(NOT MUSASHI_SC02_80147364_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147364 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801473dc.c
                ${MUSASHI_GENERATED_DIR}/801473dc_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_801473DC_RESULT)
    if(NOT MUSASHI_SC02_801473DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801473dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801473ec.c
                ${MUSASHI_GENERATED_DIR}/801473ec_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_801473EC_RESULT)
    if(NOT MUSASHI_SC02_801473EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801473ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147460.c
                ${MUSASHI_GENERATED_DIR}/80147460_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80147460_RESULT)
    if(NOT MUSASHI_SC02_80147460_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147460 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147478.c
                ${MUSASHI_GENERATED_DIR}/80147478_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80147478_RESULT)
    if(NOT MUSASHI_SC02_80147478_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147478 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801474d8.c
                ${MUSASHI_GENERATED_DIR}/801474d8_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801474D8_RESULT)
    if(NOT MUSASHI_SC02_801474D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801474d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801474ec.c
                ${MUSASHI_GENERATED_DIR}/801474ec_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_801474EC_RESULT)
    if(NOT MUSASHI_SC02_801474EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801474ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147514.c
                ${MUSASHI_GENERATED_DIR}/80147514_sc02_0031_words.inc --expected-words 69
        RESULT_VARIABLE MUSASHI_SC02_80147514_RESULT)
    if(NOT MUSASHI_SC02_80147514_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147514 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147628.c
                ${MUSASHI_GENERATED_DIR}/80147628_sc02_0031_words.inc --expected-words 60
        RESULT_VARIABLE MUSASHI_SC02_80147628_RESULT)
    if(NOT MUSASHI_SC02_80147628_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147628 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147718.c
                ${MUSASHI_GENERATED_DIR}/80147718_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80147718_RESULT)
    if(NOT MUSASHI_SC02_80147718_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147718 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147788.c
                ${MUSASHI_GENERATED_DIR}/80147788_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80147788_RESULT)
    if(NOT MUSASHI_SC02_80147788_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147788 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801477a8.c
                ${MUSASHI_GENERATED_DIR}/801477a8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801477A8_RESULT)
    if(NOT MUSASHI_SC02_801477A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801477a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801477c8.c
                ${MUSASHI_GENERATED_DIR}/801477c8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801477C8_RESULT)
    if(NOT MUSASHI_SC02_801477C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801477c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801477e8.c
                ${MUSASHI_GENERATED_DIR}/801477e8_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_801477E8_RESULT)
    if(NOT MUSASHI_SC02_801477E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801477e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147814.c
                ${MUSASHI_GENERATED_DIR}/80147814_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80147814_RESULT)
    if(NOT MUSASHI_SC02_80147814_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147814 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147860.c
                ${MUSASHI_GENERATED_DIR}/80147860_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80147860_RESULT)
    if(NOT MUSASHI_SC02_80147860_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147860 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801478b8.c
                ${MUSASHI_GENERATED_DIR}/801478b8_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_801478B8_RESULT)
    if(NOT MUSASHI_SC02_801478B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801478b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147928.c
                ${MUSASHI_GENERATED_DIR}/80147928_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80147928_RESULT)
    if(NOT MUSASHI_SC02_80147928_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147928 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147948.c
                ${MUSASHI_GENERATED_DIR}/80147948_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80147948_RESULT)
    if(NOT MUSASHI_SC02_80147948_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147948 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014799c.c
                ${MUSASHI_GENERATED_DIR}/8014799c_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8014799C_RESULT)
    if(NOT MUSASHI_SC02_8014799C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014799c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801479bc.c
                ${MUSASHI_GENERATED_DIR}/801479bc_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_801479BC_RESULT)
    if(NOT MUSASHI_SC02_801479BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801479bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147a10.c
                ${MUSASHI_GENERATED_DIR}/80147a10_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80147A10_RESULT)
    if(NOT MUSASHI_SC02_80147A10_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147a10 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147a30.c
                ${MUSASHI_GENERATED_DIR}/80147a30_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80147A30_RESULT)
    if(NOT MUSASHI_SC02_80147A30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147a30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147a84.c
                ${MUSASHI_GENERATED_DIR}/80147a84_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80147A84_RESULT)
    if(NOT MUSASHI_SC02_80147A84_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147a84 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147aac.c
                ${MUSASHI_GENERATED_DIR}/80147aac_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80147AAC_RESULT)
    if(NOT MUSASHI_SC02_80147AAC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147aac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147ad4.c
                ${MUSASHI_GENERATED_DIR}/80147ad4_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80147AD4_RESULT)
    if(NOT MUSASHI_SC02_80147AD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147ad4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147b18.c
                ${MUSASHI_GENERATED_DIR}/80147b18_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80147B18_RESULT)
    if(NOT MUSASHI_SC02_80147B18_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147b18 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147b5c.c
                ${MUSASHI_GENERATED_DIR}/80147b5c_sc02_0031_words.inc --expected-words 53
        RESULT_VARIABLE MUSASHI_SC02_80147B5C_RESULT)
    if(NOT MUSASHI_SC02_80147B5C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147b5c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147c30.c
                ${MUSASHI_GENERATED_DIR}/80147c30_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_80147C30_RESULT)
    if(NOT MUSASHI_SC02_80147C30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147c30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147cc8.c
                ${MUSASHI_GENERATED_DIR}/80147cc8_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80147CC8_RESULT)
    if(NOT MUSASHI_SC02_80147CC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147cc8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147d38.c
                ${MUSASHI_GENERATED_DIR}/80147d38_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_80147D38_RESULT)
    if(NOT MUSASHI_SC02_80147D38_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147d38 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147dc0.c
                ${MUSASHI_GENERATED_DIR}/80147dc0_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_80147DC0_RESULT)
    if(NOT MUSASHI_SC02_80147DC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147dc0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147e44.c
                ${MUSASHI_GENERATED_DIR}/80147e44_sc02_0031_words.inc --expected-words 67
        RESULT_VARIABLE MUSASHI_SC02_80147E44_RESULT)
    if(NOT MUSASHI_SC02_80147E44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147e44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147f50.c
                ${MUSASHI_GENERATED_DIR}/80147f50_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80147F50_RESULT)
    if(NOT MUSASHI_SC02_80147F50_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147f50 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80147f78.c
                ${MUSASHI_GENERATED_DIR}/80147f78_sc02_0031_words.inc --expected-words 48
        RESULT_VARIABLE MUSASHI_SC02_80147F78_RESULT)
    if(NOT MUSASHI_SC02_80147F78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80147f78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148038.c
                ${MUSASHI_GENERATED_DIR}/80148038_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80148038_RESULT)
    if(NOT MUSASHI_SC02_80148038_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148038 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148094.c
                ${MUSASHI_GENERATED_DIR}/80148094_sc02_0031_words.inc --expected-words 213
        RESULT_VARIABLE MUSASHI_SC02_80148094_RESULT)
    if(NOT MUSASHI_SC02_80148094_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148094 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801483e8.c
                ${MUSASHI_GENERATED_DIR}/801483e8_sc02_0031_words.inc --expected-words 50
        RESULT_VARIABLE MUSASHI_SC02_801483E8_RESULT)
    if(NOT MUSASHI_SC02_801483E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801483e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801484b0.c
                ${MUSASHI_GENERATED_DIR}/801484b0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801484B0_RESULT)
    if(NOT MUSASHI_SC02_801484B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801484b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801484e8.c
                ${MUSASHI_GENERATED_DIR}/801484e8_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_801484E8_RESULT)
    if(NOT MUSASHI_SC02_801484E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801484e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148534.c
                ${MUSASHI_GENERATED_DIR}/80148534_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80148534_RESULT)
    if(NOT MUSASHI_SC02_80148534_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148534 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014856c.c
                ${MUSASHI_GENERATED_DIR}/8014856c_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8014856C_RESULT)
    if(NOT MUSASHI_SC02_8014856C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014856c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801485b8.c
                ${MUSASHI_GENERATED_DIR}/801485b8_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_801485B8_RESULT)
    if(NOT MUSASHI_SC02_801485B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801485b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148634.c
                ${MUSASHI_GENERATED_DIR}/80148634_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80148634_RESULT)
    if(NOT MUSASHI_SC02_80148634_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148634 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80148648.c
                ${MUSASHI_GENERATED_DIR}/80148648_sc02_0031_words.inc --expected-words 107
        RESULT_VARIABLE MUSASHI_SC02_80148648_RESULT)
    if(NOT MUSASHI_SC02_80148648_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80148648 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801487f4.c
                ${MUSASHI_GENERATED_DIR}/801487f4_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_801487F4_RESULT)
    if(NOT MUSASHI_SC02_801487F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801487f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a828.c
                ${MUSASHI_GENERATED_DIR}/8012a828_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8012A828_RESULT)
    if(NOT MUSASHI_SC02_8012A828_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a828 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c218.c
                ${MUSASHI_GENERATED_DIR}/8012c218_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8012C218_RESULT)
    if(NOT MUSASHI_SC02_8012C218_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c218 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012aaac.c
                ${MUSASHI_GENERATED_DIR}/8012aaac_sc02_0031_words.inc --expected-words 125
        RESULT_VARIABLE MUSASHI_SC02_8012AAAC_RESULT)
    if(NOT MUSASHI_SC02_8012AAAC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012aaac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012aca0.c
                ${MUSASHI_GENERATED_DIR}/8012aca0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8012ACA0_RESULT)
    if(NOT MUSASHI_SC02_8012ACA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012aca0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182070.c
                ${MUSASHI_GENERATED_DIR}/80182070_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80182070_RESULT)
    if(NOT MUSASHI_SC02_80182070_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182070 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182078.c
                ${MUSASHI_GENERATED_DIR}/80182078_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_80182078_RESULT)
    if(NOT MUSASHI_SC02_80182078_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182078 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801820e0.c
                ${MUSASHI_GENERATED_DIR}/801820e0_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_801820E0_RESULT)
    if(NOT MUSASHI_SC02_801820E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801820e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182174.c
                ${MUSASHI_GENERATED_DIR}/80182174_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_80182174_RESULT)
    if(NOT MUSASHI_SC02_80182174_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182174 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801821f4.c
                ${MUSASHI_GENERATED_DIR}/801821f4_sc02_0031_words.inc --expected-words 77
        RESULT_VARIABLE MUSASHI_SC02_801821F4_RESULT)
    if(NOT MUSASHI_SC02_801821F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801821f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182328.c
                ${MUSASHI_GENERATED_DIR}/80182328_sc02_0031_words.inc --expected-words 111
        RESULT_VARIABLE MUSASHI_SC02_80182328_RESULT)
    if(NOT MUSASHI_SC02_80182328_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182328 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801824e4.c
                ${MUSASHI_GENERATED_DIR}/801824e4_sc02_0031_words.inc --expected-words 63
        RESULT_VARIABLE MUSASHI_SC02_801824E4_RESULT)
    if(NOT MUSASHI_SC02_801824E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801824e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801825e0.c
                ${MUSASHI_GENERATED_DIR}/801825e0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801825E0_RESULT)
    if(NOT MUSASHI_SC02_801825E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801825e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182618.c
                ${MUSASHI_GENERATED_DIR}/80182618_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80182618_RESULT)
    if(NOT MUSASHI_SC02_80182618_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182618 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182674.c
                ${MUSASHI_GENERATED_DIR}/80182674_sc02_0031_words.inc --expected-words 117
        RESULT_VARIABLE MUSASHI_SC02_80182674_RESULT)
    if(NOT MUSASHI_SC02_80182674_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182674 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182848.c
                ${MUSASHI_GENERATED_DIR}/80182848_sc02_0031_words.inc --expected-words 83
        RESULT_VARIABLE MUSASHI_SC02_80182848_RESULT)
    if(NOT MUSASHI_SC02_80182848_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182848 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182994.c
                ${MUSASHI_GENERATED_DIR}/80182994_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80182994_RESULT)
    if(NOT MUSASHI_SC02_80182994_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182994 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801829a0.c
                ${MUSASHI_GENERATED_DIR}/801829a0_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_801829A0_RESULT)
    if(NOT MUSASHI_SC02_801829A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801829a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801829a8.c
                ${MUSASHI_GENERATED_DIR}/801829a8_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801829A8_RESULT)
    if(NOT MUSASHI_SC02_801829A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801829a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801829bc.c
                ${MUSASHI_GENERATED_DIR}/801829bc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801829BC_RESULT)
    if(NOT MUSASHI_SC02_801829BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801829bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801829f8.c
                ${MUSASHI_GENERATED_DIR}/801829f8_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_801829F8_RESULT)
    if(NOT MUSASHI_SC02_801829F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801829f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182a7c.c
                ${MUSASHI_GENERATED_DIR}/80182a7c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80182A7C_RESULT)
    if(NOT MUSASHI_SC02_80182A7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182a7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182ab4.c
                ${MUSASHI_GENERATED_DIR}/80182ab4_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_80182AB4_RESULT)
    if(NOT MUSASHI_SC02_80182AB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182ab4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182b64.c
                ${MUSASHI_GENERATED_DIR}/80182b64_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80182B64_RESULT)
    if(NOT MUSASHI_SC02_80182B64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182b64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182ba0.c
                ${MUSASHI_GENERATED_DIR}/80182ba0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80182BA0_RESULT)
    if(NOT MUSASHI_SC02_80182BA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182ba0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182be0.c
                ${MUSASHI_GENERATED_DIR}/80182be0_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80182BE0_RESULT)
    if(NOT MUSASHI_SC02_80182BE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182be0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182c24.c
                ${MUSASHI_GENERATED_DIR}/80182c24_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80182C24_RESULT)
    if(NOT MUSASHI_SC02_80182C24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182c24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182c60.c
                ${MUSASHI_GENERATED_DIR}/80182c60_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_80182C60_RESULT)
    if(NOT MUSASHI_SC02_80182C60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182c60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80182cf4.c
                ${MUSASHI_GENERATED_DIR}/80182cf4_sc02_0031_words.inc --expected-words 375
        RESULT_VARIABLE MUSASHI_SC02_80182CF4_RESULT)
    if(NOT MUSASHI_SC02_80182CF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80182cf4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801832d0.c
                ${MUSASHI_GENERATED_DIR}/801832d0_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_801832D0_RESULT)
    if(NOT MUSASHI_SC02_801832D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801832d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c438.c
                ${MUSASHI_GENERATED_DIR}/8012c438_sc02_0031_words.inc --expected-words 57
        RESULT_VARIABLE MUSASHI_SC02_8012C438_RESULT)
    if(NOT MUSASHI_SC02_8012C438_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c438 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c51c.c
                ${MUSASHI_GENERATED_DIR}/8012c51c_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8012C51C_RESULT)
    if(NOT MUSASHI_SC02_8012C51C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c51c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c588.c
                ${MUSASHI_GENERATED_DIR}/8012c588_sc02_0031_words.inc --expected-words 52
        RESULT_VARIABLE MUSASHI_SC02_8012C588_RESULT)
    if(NOT MUSASHI_SC02_8012C588_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c588 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017cb7c.c
                ${MUSASHI_GENERATED_DIR}/8017cb7c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017CB7C_RESULT)
    if(NOT MUSASHI_SC02_8017CB7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017cb7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017cbb8.c
                ${MUSASHI_GENERATED_DIR}/8017cbb8_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8017CBB8_RESULT)
    if(NOT MUSASHI_SC02_8017CBB8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017cbb8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017cc04.c
                ${MUSASHI_GENERATED_DIR}/8017cc04_sc02_0031_words.inc --expected-words 61
        RESULT_VARIABLE MUSASHI_SC02_8017CC04_RESULT)
    if(NOT MUSASHI_SC02_8017CC04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017cc04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017ccf8.c
                ${MUSASHI_GENERATED_DIR}/8017ccf8_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_8017CCF8_RESULT)
    if(NOT MUSASHI_SC02_8017CCF8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017ccf8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017cd78.c
                ${MUSASHI_GENERATED_DIR}/8017cd78_sc02_0031_words.inc --expected-words 45
        RESULT_VARIABLE MUSASHI_SC02_8017CD78_RESULT)
    if(NOT MUSASHI_SC02_8017CD78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017cd78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017ce2c.c
                ${MUSASHI_GENERATED_DIR}/8017ce2c_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8017CE2C_RESULT)
    if(NOT MUSASHI_SC02_8017CE2C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017ce2c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017ce98.c
                ${MUSASHI_GENERATED_DIR}/8017ce98_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_8017CE98_RESULT)
    if(NOT MUSASHI_SC02_8017CE98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017ce98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017cf24.c
                ${MUSASHI_GENERATED_DIR}/8017cf24_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8017CF24_RESULT)
    if(NOT MUSASHI_SC02_8017CF24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017cf24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017cf44.c
                ${MUSASHI_GENERATED_DIR}/8017cf44_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8017CF44_RESULT)
    if(NOT MUSASHI_SC02_8017CF44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017cf44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017cf98.c
                ${MUSASHI_GENERATED_DIR}/8017cf98_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017CF98_RESULT)
    if(NOT MUSASHI_SC02_8017CF98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017cf98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017cfd4.c
                ${MUSASHI_GENERATED_DIR}/8017cfd4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017CFD4_RESULT)
    if(NOT MUSASHI_SC02_8017CFD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017cfd4 words")
    endif()
        execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017e39c.c
                ${MUSASHI_GENERATED_DIR}/8017e39c_sc02_0031_words.inc --expected-words 103
        RESULT_VARIABLE MUSASHI_SC02_8017E39C_RESULT)
    if(NOT MUSASHI_SC02_8017E39C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017e39c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017e538.c
                ${MUSASHI_GENERATED_DIR}/8017e538_sc02_0031_words.inc --expected-words 129
        RESULT_VARIABLE MUSASHI_SC02_8017E538_RESULT)
    if(NOT MUSASHI_SC02_8017E538_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017e538 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017e73c.c
                ${MUSASHI_GENERATED_DIR}/8017e73c_sc02_0031_words.inc --expected-words 253
        RESULT_VARIABLE MUSASHI_SC02_8017E73C_RESULT)
    if(NOT MUSASHI_SC02_8017E73C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017e73c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017eb30.c
                ${MUSASHI_GENERATED_DIR}/8017eb30_sc02_0031_words.inc --expected-words 96
        RESULT_VARIABLE MUSASHI_SC02_8017EB30_RESULT)
    if(NOT MUSASHI_SC02_8017EB30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017eb30 words")
    endif()
execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017ecb0.c
                ${MUSASHI_GENERATED_DIR}/8017ecb0_sc02_0031_words.inc --expected-words 99
        RESULT_VARIABLE MUSASHI_SC02_8017ECB0_RESULT)
    if(NOT MUSASHI_SC02_8017ECB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017ecb0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017ee3c.c
                ${MUSASHI_GENERATED_DIR}/8017ee3c_sc02_0031_words.inc --expected-words 133
        RESULT_VARIABLE MUSASHI_SC02_8017EE3C_RESULT)
    if(NOT MUSASHI_SC02_8017EE3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017ee3c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017f050.c
                ${MUSASHI_GENERATED_DIR}/8017f050_sc02_0031_words.inc --expected-words 53
        RESULT_VARIABLE MUSASHI_SC02_8017F050_RESULT)
    if(NOT MUSASHI_SC02_8017F050_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017f050 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017f124.c
                ${MUSASHI_GENERATED_DIR}/8017f124_sc02_0031_words.inc --expected-words 74
        RESULT_VARIABLE MUSASHI_SC02_8017F124_RESULT)
    if(NOT MUSASHI_SC02_8017F124_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017f124 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017f24c.c
                ${MUSASHI_GENERATED_DIR}/8017f24c_sc02_0031_words.inc --expected-words 93
        RESULT_VARIABLE MUSASHI_SC02_8017F24C_RESULT)
    if(NOT MUSASHI_SC02_8017F24C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017f24c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017f3c0.c
                ${MUSASHI_GENERATED_DIR}/8017f3c0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8017F3C0_RESULT)
    if(NOT MUSASHI_SC02_8017F3C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017f3c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017c2b0.c
                ${MUSASHI_GENERATED_DIR}/8017c2b0_sc02_0031_words.inc --expected-words 227
        RESULT_VARIABLE MUSASHI_SC02_8017C2B0_RESULT)
    if(NOT MUSASHI_SC02_8017C2B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017c2b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017c63c.c
                ${MUSASHI_GENERATED_DIR}/8017c63c_sc02_0031_words.inc --expected-words 158
        RESULT_VARIABLE MUSASHI_SC02_8017C63C_RESULT)
    if(NOT MUSASHI_SC02_8017C63C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017c63c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017c8b4.c
                ${MUSASHI_GENERATED_DIR}/8017c8b4_sc02_0031_words.inc --expected-words 82
        RESULT_VARIABLE MUSASHI_SC02_8017C8B4_RESULT)
    if(NOT MUSASHI_SC02_8017C8B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017c8b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017c9fc.c
                ${MUSASHI_GENERATED_DIR}/8017c9fc_sc02_0031_words.inc --expected-words 96
        RESULT_VARIABLE MUSASHI_SC02_8017C9FC_RESULT)
    if(NOT MUSASHI_SC02_8017C9FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017c9fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012cae4.c
                ${MUSASHI_GENERATED_DIR}/8012cae4_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_8012CAE4_RESULT)
    if(NOT MUSASHI_SC02_8012CAE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012cae4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b2cc.c
                ${MUSASHI_GENERATED_DIR}/8012b2cc_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_8012B2CC_RESULT)
    if(NOT MUSASHI_SC02_8012B2CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b2cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b14c.c
                ${MUSASHI_GENERATED_DIR}/8012b14c_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8012B14C_RESULT)
    if(NOT MUSASHI_SC02_8012B14C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b14c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80181ef0.c
                ${MUSASHI_GENERATED_DIR}/80181ef0_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80181EF0_RESULT)
    if(NOT MUSASHI_SC02_80181EF0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80181ef0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80181bb4.c
                ${MUSASHI_GENERATED_DIR}/80181bb4_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_80181BB4_RESULT)
    if(NOT MUSASHI_SC02_80181BB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80181bb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80181b78.c
                ${MUSASHI_GENERATED_DIR}/80181b78_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80181B78_RESULT)
    if(NOT MUSASHI_SC02_80181B78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80181b78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ad50.c
                ${MUSASHI_GENERATED_DIR}/8012ad50_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8012AD50_RESULT)
    if(NOT MUSASHI_SC02_8012AD50_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ad50 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80181a24.c
                ${MUSASHI_GENERATED_DIR}/80181a24_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80181A24_RESULT)
    if(NOT MUSASHI_SC02_80181A24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80181a24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801819e8.c
                ${MUSASHI_GENERATED_DIR}/801819e8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801819E8_RESULT)
    if(NOT MUSASHI_SC02_801819E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801819e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80181f5c.c
                ${MUSASHI_GENERATED_DIR}/80181f5c_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80181F5C_RESULT)
    if(NOT MUSASHI_SC02_80181F5C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80181f5c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80181fa4.c
                ${MUSASHI_GENERATED_DIR}/80181fa4_sc02_0031_words.inc --expected-words 51
        RESULT_VARIABLE MUSASHI_SC02_80181FA4_RESULT)
    if(NOT MUSASHI_SC02_80181FA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80181fa4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80181f20.c
                ${MUSASHI_GENERATED_DIR}/80181f20_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80181F20_RESULT)
    if(NOT MUSASHI_SC02_80181F20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80181f20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c1b8.c
                ${MUSASHI_GENERATED_DIR}/8012c1b8_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8012C1B8_RESULT)
    if(NOT MUSASHI_SC02_8012C1B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c1b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c194.c
                ${MUSASHI_GENERATED_DIR}/8012c194_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8012C194_RESULT)
    if(NOT MUSASHI_SC02_8012C194_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c194 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c1dc.c
                ${MUSASHI_GENERATED_DIR}/8012c1dc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8012C1DC_RESULT)
    if(NOT MUSASHI_SC02_8012C1DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c1dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013221c.c
                ${MUSASHI_GENERATED_DIR}/8013221c_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8013221C_RESULT)
    if(NOT MUSASHI_SC02_8013221C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013221c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80131fdc.c
                ${MUSASHI_GENERATED_DIR}/80131fdc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80131FDC_RESULT)
    if(NOT MUSASHI_SC02_80131FDC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80131fdc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c890.c
                ${MUSASHI_GENERATED_DIR}/8012c890_sc02_0031_words.inc --expected-words 149
        RESULT_VARIABLE MUSASHI_SC02_8012C890_RESULT)
    if(NOT MUSASHI_SC02_8012C890_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c890 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c750.c
                ${MUSASHI_GENERATED_DIR}/8012c750_sc02_0031_words.inc --expected-words 52
        RESULT_VARIABLE MUSASHI_SC02_8012C750_RESULT)
    if(NOT MUSASHI_SC02_8012C750_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c750 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e4b4.c
                ${MUSASHI_GENERATED_DIR}/8013e4b4_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_8013E4B4_RESULT)
    if(NOT MUSASHI_SC02_8013E4B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e4b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80178608.c
                ${MUSASHI_GENERATED_DIR}/80178608_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_80178608_RESULT)
    if(NOT MUSASHI_SC02_80178608_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80178608 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128564.c
                ${MUSASHI_GENERATED_DIR}/80128564_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80128564_RESULT)
    if(NOT MUSASHI_SC02_80128564_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128564 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801285d4.c
                ${MUSASHI_GENERATED_DIR}/801285d4_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_801285D4_RESULT)
    if(NOT MUSASHI_SC02_801285D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801285d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801285e4.c
                ${MUSASHI_GENERATED_DIR}/801285e4_sc02_0031_words.inc --expected-words 76
        RESULT_VARIABLE MUSASHI_SC02_801285E4_RESULT)
    if(NOT MUSASHI_SC02_801285E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801285e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128714.c
                ${MUSASHI_GENERATED_DIR}/80128714_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_80128714_RESULT)
    if(NOT MUSASHI_SC02_80128714_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128714 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801287b8.c
                ${MUSASHI_GENERATED_DIR}/801287b8_sc02_0031_words.inc --expected-words 76
        RESULT_VARIABLE MUSASHI_SC02_801287B8_RESULT)
    if(NOT MUSASHI_SC02_801287B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801287b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801288e8.c
                ${MUSASHI_GENERATED_DIR}/801288e8_sc02_0031_words.inc --expected-words 80
        RESULT_VARIABLE MUSASHI_SC02_801288E8_RESULT)
    if(NOT MUSASHI_SC02_801288E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801288e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128a28.c
                ${MUSASHI_GENERATED_DIR}/80128a28_sc02_0031_words.inc --expected-words 51
        RESULT_VARIABLE MUSASHI_SC02_80128A28_RESULT)
    if(NOT MUSASHI_SC02_80128A28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128a28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128af4.c
                ${MUSASHI_GENERATED_DIR}/80128af4_sc02_0031_words.inc --expected-words 72
        RESULT_VARIABLE MUSASHI_SC02_80128AF4_RESULT)
    if(NOT MUSASHI_SC02_80128AF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128af4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80146074.c
                ${MUSASHI_GENERATED_DIR}/80146074_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80146074_RESULT)
    if(NOT MUSASHI_SC02_80146074_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80146074 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012853c.c
                ${MUSASHI_GENERATED_DIR}/8012853c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8012853C_RESULT)
    if(NOT MUSASHI_SC02_8012853C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012853c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175494.c
                ${MUSASHI_GENERATED_DIR}/80175494_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80175494_RESULT)
    if(NOT MUSASHI_SC02_80175494_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175494 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e8f0.c
                ${MUSASHI_GENERATED_DIR}/8016e8f0_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8016E8F0_RESULT)
    if(NOT MUSASHI_SC02_8016E8F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e8f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80178004.c
                ${MUSASHI_GENERATED_DIR}/80178004_sc02_0031_words.inc --expected-words 165
        RESULT_VARIABLE MUSASHI_SC02_80178004_RESULT)
    if(NOT MUSASHI_SC02_80178004_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80178004 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80176144.c
                ${MUSASHI_GENERATED_DIR}/80176144_sc02_0031_words.inc --expected-words 53
        RESULT_VARIABLE MUSASHI_SC02_80176144_RESULT)
    if(NOT MUSASHI_SC02_80176144_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80176144 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80178298.c
                ${MUSASHI_GENERATED_DIR}/80178298_sc02_0031_words.inc --expected-words 78
        RESULT_VARIABLE MUSASHI_SC02_80178298_RESULT)
    if(NOT MUSASHI_SC02_80178298_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80178298 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80177940.c
                ${MUSASHI_GENERATED_DIR}/80177940_sc02_0031_words.inc --expected-words 101
        RESULT_VARIABLE MUSASHI_SC02_80177940_RESULT)
    if(NOT MUSASHI_SC02_80177940_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80177940 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80177b5c.c
                ${MUSASHI_GENERATED_DIR}/80177b5c_sc02_0031_words.inc --expected-words 147
        RESULT_VARIABLE MUSASHI_SC02_80177b5c_RESULT)
    if(NOT MUSASHI_SC02_80177b5c_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80177b5c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80177ea4.c
                ${MUSASHI_GENERATED_DIR}/80177ea4_sc02_0031_words.inc --expected-words 56
        RESULT_VARIABLE MUSASHI_SC02_80177ea4_RESULT)
    if(NOT MUSASHI_SC02_80177ea4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80177ea4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801770e0.c
                ${MUSASHI_GENERATED_DIR}/801770e0_sc02_0031_words.inc --expected-words 152
        RESULT_VARIABLE MUSASHI_SC02_801770e0_RESULT)
    if(NOT MUSASHI_SC02_801770e0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801770e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801777bc.c
                ${MUSASHI_GENERATED_DIR}/801777bc_sc02_0031_words.inc --expected-words 59
        RESULT_VARIABLE MUSASHI_SC02_801777bc_RESULT)
    if(NOT MUSASHI_SC02_801777bc_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801777bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801783d0.c
                ${MUSASHI_GENERATED_DIR}/801783d0_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_801783d0_RESULT)
    if(NOT MUSASHI_SC02_801783d0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801783d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80177784.c
                ${MUSASHI_GENERATED_DIR}/80177784_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80177784_RESULT)
    if(NOT MUSASHI_SC02_80177784_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80177784 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80176d94.c
                ${MUSASHI_GENERATED_DIR}/80176d94_sc02_0031_words.inc --expected-words 152
        RESULT_VARIABLE MUSASHI_SC02_80176d94_RESULT)
    if(NOT MUSASHI_SC02_80176d94_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80176d94 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175ab8.c
                ${MUSASHI_GENERATED_DIR}/80175ab8_sc02_0031_words.inc --expected-words 188
        RESULT_VARIABLE MUSASHI_SC02_80175ab8_RESULT)
    if(NOT MUSASHI_SC02_80175ab8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175ab8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017742c.c
                ${MUSASHI_GENERATED_DIR}/8017742c_sc02_0031_words.inc --expected-words 109
        RESULT_VARIABLE MUSASHI_SC02_8017742c_RESULT)
    if(NOT MUSASHI_SC02_8017742c_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017742c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175da8.c
                ${MUSASHI_GENERATED_DIR}/80175da8_sc02_0031_words.inc --expected-words 231
        RESULT_VARIABLE MUSASHI_SC02_80175da8_RESULT)
    if(NOT MUSASHI_SC02_80175da8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175da8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801757a0.c
                ${MUSASHI_GENERATED_DIR}/801757a0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801757a0_RESULT)
    if(NOT MUSASHI_SC02_801757a0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801757a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175308.c
                ${MUSASHI_GENERATED_DIR}/80175308_sc02_0031_words.inc --expected-words 67
        RESULT_VARIABLE MUSASHI_SC02_80175308_RESULT)
    if(NOT MUSASHI_SC02_80175308_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175308 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801284f0.c
                ${MUSASHI_GENERATED_DIR}/801284f0_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_801284F0_RESULT)
    if(NOT MUSASHI_SC02_801284F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801284f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801284b8.c
                ${MUSASHI_GENERATED_DIR}/801284b8_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801284B8_RESULT)
    if(NOT MUSASHI_SC02_801284B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801284b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013d3d4.c
                ${MUSASHI_GENERATED_DIR}/8013d3d4_sc02_0031_words.inc --expected-words 90
        RESULT_VARIABLE MUSASHI_SC02_8013D3D4_RESULT)
    if(NOT MUSASHI_SC02_8013D3D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013d3d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013cf68.c
                ${MUSASHI_GENERATED_DIR}/8013cf68_sc02_0031_words.inc --expected-words 63
        RESULT_VARIABLE MUSASHI_SC02_8013CF68_RESULT)
    if(NOT MUSASHI_SC02_8013CF68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013cf68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013d8fc.c
                ${MUSASHI_GENERATED_DIR}/8013d8fc_sc02_0031_words.inc --expected-words 45
        RESULT_VARIABLE MUSASHI_SC02_8013D8FC_RESULT)
    if(NOT MUSASHI_SC02_8013D8FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013d8fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013d53c.c
                ${MUSASHI_GENERATED_DIR}/8013d53c_sc02_0031_words.inc --expected-words 240
        RESULT_VARIABLE MUSASHI_SC02_8013D53C_RESULT)
    if(NOT MUSASHI_SC02_8013D53C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013d53c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013b83c.c
                ${MUSASHI_GENERATED_DIR}/8013b83c_sc02_0031_words.inc --expected-words 272
        RESULT_VARIABLE MUSASHI_SC02_8013B83C_RESULT)
    if(NOT MUSASHI_SC02_8013B83C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013b83c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128158.c
                ${MUSASHI_GENERATED_DIR}/80128158_sc02_0031_words.inc --expected-words 178
        RESULT_VARIABLE MUSASHI_SC02_80128158_RESULT)
    if(NOT MUSASHI_SC02_80128158_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 title 80128158 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800ceec8.c
                ${MUSASHI_GENERATED_DIR}/800ceec8_overlay0004_words.inc --expected-words 143
        RESULT_VARIABLE MUSASHI_OV4_800CEEC8_RESULT)
    if(NOT MUSASHI_OV4_800CEEC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800CEEC8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d1e18.c
                ${MUSASHI_GENERATED_DIR}/800d1e18_overlay0004_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_OV4_800D1E18_RESULT)
    if(NOT MUSASHI_OV4_800D1E18_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D1E18 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800cfb3c.c
                ${MUSASHI_GENERATED_DIR}/800cfb3c_overlay0004_words.inc --expected-words 56
        RESULT_VARIABLE MUSASHI_OV4_800CFB3C_RESULT)
    if(NOT MUSASHI_OV4_800CFB3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800CFB3C words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d1e9c.c
                ${MUSASHI_GENERATED_DIR}/800d1e9c_overlay0004_words.inc --expected-words 318
        RESULT_VARIABLE MUSASHI_OV4_800D1E9C_RESULT)
    if(NOT MUSASHI_OV4_800D1E9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D1E9C words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2394.c
                ${MUSASHI_GENERATED_DIR}/800d2394_overlay0004_words.inc --expected-words 48
        RESULT_VARIABLE MUSASHI_OV4_800D2394_RESULT)
    if(NOT MUSASHI_OV4_800D2394_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2394 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2454.c
                ${MUSASHI_GENERATED_DIR}/800d2454_overlay0004_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_OV4_800D2454_RESULT)
    if(NOT MUSASHI_OV4_800D2454_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2454 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2aa0.c
                ${MUSASHI_GENERATED_DIR}/800d2aa0_overlay0004_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_OV4_800D2AA0_RESULT)
    if(NOT MUSASHI_OV4_800D2AA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2AA0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2d44.c
                ${MUSASHI_GENERATED_DIR}/800d2d44_overlay0004_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_OV4_800D2D44_RESULT)
    if(NOT MUSASHI_OV4_800D2D44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2D44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2a24.c
                ${MUSASHI_GENERATED_DIR}/800d2a24_overlay0004_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_OV4_800D2A24_RESULT)
    if(NOT MUSASHI_OV4_800D2A24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2A24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2704.c
                ${MUSASHI_GENERATED_DIR}/800d2704_overlay0004_words.inc --expected-words 39
        RESULT_VARIABLE MUSASHI_OV4_800D2704_RESULT)
    if(NOT MUSASHI_OV4_800D2704_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2704 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d298c.c
                ${MUSASHI_GENERATED_DIR}/800d298c_overlay0004_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_OV4_800D298C_RESULT)
    if(NOT MUSASHI_OV4_800D298C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D298C words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2c0c.c
                ${MUSASHI_GENERATED_DIR}/800d2c0c_overlay0004_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_OV4_800D2C0C_RESULT)
    if(NOT MUSASHI_OV4_800D2C0C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2C0C words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2c88.c
                ${MUSASHI_GENERATED_DIR}/800d2c88_overlay0004_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_OV4_800D2C88_RESULT)
    if(NOT MUSASHI_OV4_800D2C88_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2C88 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d24d0.c
                ${MUSASHI_GENERATED_DIR}/800d24d0_overlay0004_words.inc --expected-words 141
        RESULT_VARIABLE MUSASHI_OV4_800D24D0_RESULT)
    if(NOT MUSASHI_OV4_800D24D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D24D0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2d68.c
                ${MUSASHI_GENERATED_DIR}/800d2d68_overlay0004_words.inc --expected-words 63
        RESULT_VARIABLE MUSASHI_OV4_800D2D68_RESULT)
    if(NOT MUSASHI_OV4_800D2D68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2D68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d27a0.c
                ${MUSASHI_GENERATED_DIR}/800d27a0_overlay0004_words.inc --expected-words 123
        RESULT_VARIABLE MUSASHI_OV4_800D27A0_RESULT)
    if(NOT MUSASHI_OV4_800D27A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D27A0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d3234.c
                ${MUSASHI_GENERATED_DIR}/800d3234_overlay0004_words.inc --expected-words 195
        RESULT_VARIABLE MUSASHI_OV4_800D3234_RESULT)
    if(NOT MUSASHI_OV4_800D3234_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D3234 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2e64.c
                ${MUSASHI_GENERATED_DIR}/800d2e64_overlay0004_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_OV4_800D2E64_RESULT)
    if(NOT MUSASHI_OV4_800D2E64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2E64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2ef8.c
                ${MUSASHI_GENERATED_DIR}/800d2ef8_overlay0004_words.inc --expected-words 36
        RESULT_VARIABLE MUSASHI_OV4_800D2EF8_RESULT)
    if(NOT MUSASHI_OV4_800D2EF8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2EF8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d2f88.c
                ${MUSASHI_GENERATED_DIR}/800d2f88_overlay0004_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_OV4_800D2F88_RESULT)
    if(NOT MUSASHI_OV4_800D2F88_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D2F88 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d3020.c
                ${MUSASHI_GENERATED_DIR}/800d3020_overlay0004_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_OV4_800D3020_RESULT)
    if(NOT MUSASHI_OV4_800D3020_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D3020 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800d30d0.c
                ${MUSASHI_GENERATED_DIR}/800d30d0_overlay0004_words.inc --expected-words 76
        RESULT_VARIABLE MUSASHI_OV4_800D30D0_RESULT)
    if(NOT MUSASHI_OV4_800D30D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800D30D0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800cffec.c
                ${MUSASHI_GENERATED_DIR}/800cffec_overlay0004_words.inc --expected-words 69
        RESULT_VARIABLE MUSASHI_OV4_800CFFEC_RESULT)
    if(NOT MUSASHI_OV4_800CFFEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800CFFEC words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800cf3e8.c
                ${MUSASHI_GENERATED_DIR}/800cf3e8_overlay0004_words.inc --expected-words 469
        RESULT_VARIABLE MUSASHI_OV4_800CF3E8_RESULT)
    if(NOT MUSASHI_OV4_800CF3E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800CF3E8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800cfc1c.c
                ${MUSASHI_GENERATED_DIR}/800cfc1c_overlay0004_words.inc --expected-words 121
        RESULT_VARIABLE MUSASHI_OV4_800CFC1C_RESULT)
    if(NOT MUSASHI_OV4_800CFC1C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800CFC1C words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800cf104.c
                ${MUSASHI_GENERATED_DIR}/800cf104_overlay0004_words.inc --expected-words 127
        RESULT_VARIABLE MUSASHI_OV4_800CF104_RESULT)
    if(NOT MUSASHI_OV4_800CF104_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800CF104 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800cf300.c
                ${MUSASHI_GENERATED_DIR}/800cf300_overlay0004_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_OV4_800CF300_RESULT)
    if(NOT MUSASHI_OV4_800CF300_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800CF300 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800cf370.c
                ${MUSASHI_GENERATED_DIR}/800cf370_overlay0004_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_OV4_800CF370_RESULT)
    if(NOT MUSASHI_OV4_800CF370_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800CF370 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800cf3a4.c
                ${MUSASHI_GENERATED_DIR}/800cf3a4_overlay0004_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_OV4_800CF3A4_RESULT)
    if(NOT MUSASHI_OV4_800CF3A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800CF3A4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0004/800cfe00.c
                ${MUSASHI_GENERATED_DIR}/800cfe00_overlay0004_words.inc --expected-words 45
        RESULT_VARIABLE MUSASHI_OV4_800CFE00_RESULT)
    if(NOT MUSASHI_OV4_800CFE00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract MAIN4 800CFE00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0012/80128228.c
                ${MUSASHI_GENERATED_DIR}/80128228_overlay0012_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_OV12_8228_WORDS_RESULT)
    if(NOT MUSASHI_OV12_8228_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0012 80128228 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0012/80128288.c
                ${MUSASHI_GENERATED_DIR}/80128288_overlay0012_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_OV12_8288_WORDS_RESULT)
    if(NOT MUSASHI_OV12_8288_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0012 80128288 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0012/80128158.c
                ${MUSASHI_GENERATED_DIR}/80128158_overlay0012_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_OV12_8158_WORDS_RESULT)
    if(NOT MUSASHI_OV12_8158_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0012 80128158 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0012/80128a28.c
                ${MUSASHI_GENERATED_DIR}/80128a28_overlay0012_words.inc --expected-words 51
        RESULT_VARIABLE MUSASHI_OV12_8A28_WORDS_RESULT)
    if(NOT MUSASHI_OV12_8A28_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0012 80128A28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0012/8017bebc.c
                ${MUSASHI_GENERATED_DIR}/8017bebc_overlay0012_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_OV12_7BEBC_WORDS_RESULT)
    if(NOT MUSASHI_OV12_7BEBC_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0012 8017BEBC words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0012/8017bee4.c
                ${MUSASHI_GENERATED_DIR}/8017bee4_overlay0012_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_OV12_7BEE4_WORDS_RESULT)
    if(NOT MUSASHI_OV12_7BEE4_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0012 8017BEE4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0012/8017bf38.c
                ${MUSASHI_GENERATED_DIR}/8017bf38_overlay0012_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_OV12_7BF38_WORDS_RESULT)
    if(NOT MUSASHI_OV12_7BF38_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0012 8017BF38 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/main_0012/8017c008.c
                ${MUSASHI_GENERATED_DIR}/8017c008_overlay0012_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_OV12_7C008_WORDS_RESULT)
    if(NOT MUSASHI_OV12_7C008_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract overlay 0012 8017C008 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005c640.c
                ${MUSASHI_GENERATED_DIR}/8005c640_words.inc --expected-words 418
        RESULT_VARIABLE MUSASHI_FORMATTER_WORDS_RESULT
    )
    if(NOT MUSASHI_FORMATTER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005C640 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005c604.c
                ${MUSASHI_GENERATED_DIR}/8005c604_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_FORMATTER_WRAPPER_WORDS_RESULT
    )
    if(NOT MUSASHI_FORMATTER_WRAPPER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005C604 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80059234.c
                ${MUSASHI_GENERATED_DIR}/80059234_words.inc --expected-words 97
        RESULT_VARIABLE MUSASHI_RESETGRAPH_WORDS_RESULT
    )
    if(NOT MUSASHI_RESETGRAPH_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80059234 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80042580.c
                ${MUSASHI_GENERATED_DIR}/80042580_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_CALLBACK_WRAPPER_WORDS_RESULT
    )
    if(NOT MUSASHI_CALLBACK_WRAPPER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80042580 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80042644.c
                ${MUSASHI_GENERATED_DIR}/80042644_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_CALLBACK_DISPATCH_WORDS_RESULT
    )
    if(NOT MUSASHI_CALLBACK_DISPATCH_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80042644 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80042718.c
                ${MUSASHI_GENERATED_DIR}/80042718_words.inc --expected-words 55
        RESULT_VARIABLE MUSASHI_CALLBACK_INITIALIZER_WORDS_RESULT
    )
    if(NOT MUSASHI_CALLBACK_INITIALIZER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80042718 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80042c90.c
                ${MUSASHI_GENERATED_DIR}/80042c90_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_CALLBACK_INSTALLER_WORDS_RESULT
    )
    if(NOT MUSASHI_CALLBACK_INSTALLER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80042C90 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80042d60.c
                ${MUSASHI_GENERATED_DIR}/80042d60_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_CALLBACK_SLOT_WRITE_WORDS_RESULT
    )
    if(NOT MUSASHI_CALLBACK_SLOT_WRITE_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80042D60 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80042db8.c
                ${MUSASHI_GENERATED_DIR}/80042db8_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_CALLBACK_CHANNEL_INSTALLER_WORDS_RESULT
    )
    if(NOT MUSASHI_CALLBACK_CHANNEL_INSTALLER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80042DB8 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/800594cc.c
                ${MUSASHI_GENERATED_DIR}/800594cc_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_STARTUP_MODE_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_MODE_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 800594CC instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80059658.c
                ${MUSASHI_GENERATED_DIR}/80059658_words.inc --expected-words 39
        RESULT_VARIABLE MUSASHI_STARTUP_GRAPHICS_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_GRAPHICS_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80059658 instruction stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py ${CMAKE_CURRENT_SOURCE_DIR}/src/main/800142c8.c ${MUSASHI_GENERATED_DIR}/800142c8_words.inc --expected-words 28 RESULT_VARIABLE MUSASHI_FINAL_INIT_WORDS_RESULT)
    if(NOT MUSASHI_FINAL_INIT_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 800142C8 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80018fc8.c
                ${MUSASHI_GENERATED_DIR}/80018fc8_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_POST_RECORD_CLEAR_WORDS_RESULT
    )
    if(NOT MUSASHI_POST_RECORD_CLEAR_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80018FC8 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80018918.c
                ${MUSASHI_GENERATED_DIR}/80018918_words.inc --expected-words 36
        RESULT_VARIABLE MUSASHI_STARTUP_RECORD_SETUP_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_RECORD_SETUP_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80018918 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8001b324.c
                ${MUSASHI_GENERATED_DIR}/8001b324_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_STARTUP_GLOBAL_RESET_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_GLOBAL_RESET_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8001B324 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8001b34c.c
                ${MUSASHI_GENERATED_DIR}/8001b34c_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_STARTUP_GLOBAL_RESET_LEAF_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_GLOBAL_RESET_LEAF_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8001B34C instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80028fdc.c
                ${MUSASHI_GENERATED_DIR}/80028fdc_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_STARTUP_SELECTOR_2C_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_SELECTOR_2C_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80028FDC instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80029020.c
                ${MUSASHI_GENERATED_DIR}/80029020_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_STARTUP_SELECTOR_2D_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_SELECTOR_2D_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80029020 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/800291a0.c
                ${MUSASHI_GENERATED_DIR}/800291a0_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_STARTUP_SELECTOR_STORE_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_SELECTOR_STORE_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 800291A0 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80028dbc.c
                ${MUSASHI_GENERATED_DIR}/80028dbc_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_STARTUP_BIT_0C_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_BIT_0C_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80028DBC instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80028e00.c
                ${MUSASHI_GENERATED_DIR}/80028e00_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_STARTUP_BIT_0D_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_BIT_0D_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80028E00 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80029124.c
                ${MUSASHI_GENERATED_DIR}/80029124_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_STARTUP_BIT_STORE_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_BIT_STORE_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80029124 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005fc68.c
                ${MUSASHI_GENERATED_DIR}/8005fc68_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_CD_START_WORDS_RESULT
    )
    if(NOT MUSASHI_CD_START_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005FC68 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8006186c.c
                ${MUSASHI_GENERATED_DIR}/8006186c_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_CD_INIT_WORDS_RESULT
    )
    if(NOT MUSASHI_CD_INIT_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8006186C instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/800622d0.c
                ${MUSASHI_GENERATED_DIR}/800622d0_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_CD_INIT_A_WORDS_RESULT
    )
    if(NOT MUSASHI_CD_INIT_A_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 800622D0 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80062328.c
                ${MUSASHI_GENERATED_DIR}/80062328_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_CD_INIT_B_WORDS_RESULT
    )
    if(NOT MUSASHI_CD_INIT_B_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80062328 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80062394.c
                ${MUSASHI_GENERATED_DIR}/80062394_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_CD_CALLBACK_WORDS_RESULT
    )
    if(NOT MUSASHI_CD_CALLBACK_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80062394 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005fcb8.c
                ${MUSASHI_GENERATED_DIR}/8005fcb8_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_EVENT_START_WORDS_RESULT
    )
    if(NOT MUSASHI_EVENT_START_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005FCB8 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80062888.c
                ${MUSASHI_GENERATED_DIR}/80062888_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_EVENT_RESET_WORDS_RESULT
    )
    if(NOT MUSASHI_EVENT_RESET_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80062888 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005f0c8.c
                ${MUSASHI_GENERATED_DIR}/8005f0c8_words.inc --expected-words 88
        RESULT_VARIABLE MUSASHI_STARTUP_ALLOCATOR_PREFIX_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_ALLOCATOR_PREFIX_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005F0C8 prefix")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005f728.c
                ${MUSASHI_GENERATED_DIR}/8005f728_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_STARTUP_CALLBACK_TABLE_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_CALLBACK_TABLE_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005F728 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005c2c8.c
                ${MUSASHI_GENERATED_DIR}/8005c2c8_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_GUARDED_CLEAR_WORDS_RESULT
    )
    if(NOT MUSASHI_GUARDED_CLEAR_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005C2C8 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005d6a0.c
                ${MUSASHI_GENERATED_DIR}/8005d6a0_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_STARTUP_TABLE_INIT_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_TABLE_INIT_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005D6A0 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005d0f8.c
                ${MUSASHI_GENERATED_DIR}/8005d0f8_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_INPUT_STARTUP_WRAPPER_WORDS_RESULT
    )
    if(NOT MUSASHI_INPUT_STARTUP_WRAPPER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005D0F8 instruction stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005d8b4.c ${MUSASHI_GENERATED_DIR}/8005d8b4_words.inc
        --expected-words 51 RESULT_VARIABLE MUSASHI_INPUT_STARTUP_PREFIX_WORDS_RESULT)
    if(NOT MUSASHI_INPUT_STARTUP_PREFIX_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005D8B4 prefix")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005f228.c ${MUSASHI_GENERATED_DIR}/8005f228_words.inc
        --expected-words 26 RESULT_VARIABLE MUSASHI_INPUT_RECORD_CALLBACK_WORDS_RESULT)
    if(NOT MUSASHI_INPUT_RECORD_CALLBACK_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005F228 record callback")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80043450.c ${MUSASHI_GENERATED_DIR}/80043450_words.inc
        --expected-words 27 RESULT_VARIABLE MUSASHI_STARTUP_RETRY_WORDS_RESULT)
    if(NOT MUSASHI_STARTUP_RETRY_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80043450 retry stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80044bf4.c ${MUSASHI_GENERATED_DIR}/80044bf4_words.inc
        --expected-words 61 RESULT_VARIABLE MUSASHI_STARTUP_RETRY_ALTERNATE_WORDS_RESULT)
    if(NOT MUSASHI_STARTUP_RETRY_ALTERNATE_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80044BF4 retry-alternate stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8004359c.c ${MUSASHI_GENERATED_DIR}/8004359c_words.inc
        --expected-words 6 RESULT_VARIABLE MUSASHI_STARTUP_CALLBACK_SETTER_WORDS_RESULT)
    if(NOT MUSASHI_STARTUP_CALLBACK_SETTER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8004359C callback-setter stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/800435b4.c ${MUSASHI_GENERATED_DIR}/800435b4_words.inc
        --expected-words 6 RESULT_VARIABLE MUSASHI_STARTUP_CALLBACK_SETTER_B_WORDS_RESULT)
    if(NOT MUSASHI_STARTUP_CALLBACK_SETTER_B_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 800435B4 callback-setter stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8004654c.c ${MUSASHI_GENERATED_DIR}/8004654c_words.inc
        --expected-words 6 RESULT_VARIABLE MUSASHI_STARTUP_CALLBACK_SETTER_C_WORDS_RESULT)
    if(NOT MUSASHI_STARTUP_CALLBACK_SETTER_C_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8004654C callback-setter stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80046564.c ${MUSASHI_GENERATED_DIR}/80046564_words.inc
        --expected-words 6 RESULT_VARIABLE MUSASHI_STARTUP_CALLBACK_CONTROL_WORDS_RESULT)
    if(NOT MUSASHI_STARTUP_CALLBACK_CONTROL_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80046564 callback-control stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80044d38.c ${MUSASHI_GENERATED_DIR}/80044d38_words.inc
        --expected-words 123 RESULT_VARIABLE MUSASHI_CD_INITIALIZER_WORDS_RESULT)
    if(NOT MUSASHI_CD_INITIALIZER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80044D38 CD-initializer stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80044670_prefix.c ${MUSASHI_GENERATED_DIR}/80044670_words.inc
        --expected-words 25 RESULT_VARIABLE MUSASHI_CD_COMMAND_PREFIX_WORDS_RESULT)
    if(NOT MUSASHI_CD_COMMAND_PREFIX_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80044670 CD-command prefix")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/800446d4_prefix.c ${MUSASHI_GENERATED_DIR}/800446d4_words.inc
        --expected-words 26 RESULT_VARIABLE MUSASHI_CD_COMMAND_CONTINUATION_WORDS_RESULT)
    if(NOT MUSASHI_CD_COMMAND_CONTINUATION_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 800446D4 CD-command continuation")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8004239c_minus_one.c ${MUSASHI_GENERATED_DIR}/8004239c_minus_one_words.inc
        --expected-words 31 RESULT_VARIABLE MUSASHI_TICK_QUERY_WORDS_RESULT)
    if(NOT MUSASHI_TICK_QUERY_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8004239C minus-one tick-query stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80044124_first_poll.c ${MUSASHI_GENERATED_DIR}/80044124_first_poll_words.inc
        --expected-words 29 RESULT_VARIABLE MUSASHI_STATUS_FIRST_POLL_WORDS_RESULT)
    if(NOT MUSASHI_STATUS_FIRST_POLL_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80044124 first-poll stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80044198_timeout_prefix.c ${MUSASHI_GENERATED_DIR}/80044198_timeout_prefix_words.inc
        --expected-words 16 RESULT_VARIABLE MUSASHI_STATUS_TIMEOUT_WORDS_RESULT)
    if(NOT MUSASHI_STATUS_TIMEOUT_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80044198 timeout-comparison stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/800441d8_diagnostic_prefix.c ${MUSASHI_GENERATED_DIR}/800441d8_diagnostic_prefix_words.inc
        --expected-words 29 RESULT_VARIABLE MUSASHI_STATUS_DIAGNOSTIC_WORDS_RESULT)
    if(NOT MUSASHI_STATUS_DIAGNOSTIC_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 800441D8 timeout-diagnostic stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80044250_status_loop.c ${MUSASHI_GENERATED_DIR}/80044250_status_loop_words.inc
        --expected-words 85 RESULT_VARIABLE MUSASHI_STATUS_LOOP_WORDS_RESULT)
    if(NOT MUSASHI_STATUS_LOOP_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80044250 status/callback loop")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/asm/main.s ${MUSASHI_GENERATED_DIR}/80043b9c_words.inc
        --asm-label func_80043B9C --expected-words 354
        RESULT_VARIABLE MUSASHI_STATUS_WORKER_WORDS_RESULT)
    if(NOT MUSASHI_STATUS_WORKER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80043B9C status-worker stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/asm/main.s ${MUSASHI_GENERATED_DIR}/80044670_full_words.inc
        --asm-label func_80044670 --expected-words 263
        RESULT_VARIABLE MUSASHI_CD_COMMAND_FULL_WORDS_RESULT)
    if(NOT MUSASHI_CD_COMMAND_FULL_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the tracked 80044670 command stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80044b14.c ${MUSASHI_GENERATED_DIR}/80044b14_words.inc
        --expected-words 56 RESULT_VARIABLE MUSASHI_CD_STATE_RESET_WORDS_RESULT)
    if(NOT MUSASHI_CD_STATE_RESET_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80044B14 CD-state-reset stream")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/800434bc.c ${MUSASHI_GENERATED_DIR}/800434bc_words.inc
        --expected-words 8 RESULT_VARIABLE MUSASHI_CD_STATE_RESET_WRAPPER_WORDS_RESULT)
    if(NOT MUSASHI_CD_STATE_RESET_WRAPPER_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 800434BC CD-state-reset wrapper")
    endif()
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/80043300.c ${MUSASHI_GENERATED_DIR}/80043300_words.inc
        --expected-words 38 RESULT_VARIABLE MUSASHI_STARTUP_DISPATCH_WORDS_RESULT)
    if(NOT MUSASHI_STARTUP_DISPATCH_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 80043300 startup dispatcher")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/8005cd98.c
                ${MUSASHI_GENERATED_DIR}/8005cd98_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SAVED_CONTEXT_WORDS_RESULT
    )
    if(NOT MUSASHI_SAVED_CONTEXT_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 8005CD98 instruction stream")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main/800141f0.c
                ${MUSASHI_GENERATED_DIR}/800141f0_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_STARTUP_WORDS_RESULT
    )
    if(NOT MUSASHI_STARTUP_WORDS_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not extract the exact 800141F0 instruction stream")
    endif()

    # Smoke-matched leaves: house-style address-named files under src/main/.
    # These correspond to Druthulu vendor/bfm-decomp/src/800.c symbols, but the
    # cleaned local bodies win over giant-TU / MIPS-asm forms. See VENDOR.md
    # and docs/VENDOR-CLEANUP.md. Do not compile vendor src/800.c wholesale.
    set(MUSASHI_SMOKE_MATCHED_SOURCES
        src/main/80012ab0.c
        src/main/80012e6c.c
        src/main/8001311c.c
        src/main/80013154.c
    )
    if(MUSASHI_USE_VENDOR_BFM)
        set(_musashi_vendor_root "${CMAKE_CURRENT_SOURCE_DIR}/vendor/bfm-decomp")
        if(NOT EXISTS "${_musashi_vendor_root}/src/800.c")
            message(FATAL_ERROR
                "MUSASHI_USE_VENDOR_BFM=ON but ${_musashi_vendor_root}/src/800.c is missing. "
                "Restore the vendor sidecar (rsync from _refs/BFM-decomp or branch vendor/bfm-decomp).")
        endif()
        message(STATUS
            "MUSASHI_USE_VENDOR_BFM: smoke uses cleaned src/main leaves "
            "(80012AB0/80012E6C/8001311C/80013154); raw vendor tree at vendor/bfm-decomp/")
    endif()

    add_library(musashi_shared STATIC
        src/shared/runtime_api.c
        # First native consumer of verified decomp-owned code. Independently
        # byte-matched; does not claim the complete PS1 gameplay graph is portable.
        ${MUSASHI_SMOKE_MATCHED_SOURCES}
    )
    target_include_directories(musashi_shared
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/src/shared
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_compile_features(musashi_shared PUBLIC c_std_99)
    if(MUSASHI_USE_VENDOR_BFM)
        target_compile_definitions(musashi_shared PUBLIC MUSASHI_USE_VENDOR_BFM=1)
    endif()

    if(WIN32)
        set(MUSASHI_PLATFORM_SOURCE pc_port/platform/windows.c)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(MUSASHI_PLATFORM_SOURCE pc_port/platform/linux.c)
    else()
        message(FATAL_ERROR
            "Unsupported target platform '${CMAKE_SYSTEM_NAME}'; provide a pc_port/platform adapter")
    endif()

    add_library(musashi_pc_port STATIC
        pc_port/port_runtime.c
        pc_port/boot_memory.c
        pc_port/startup_bindings.c
        pc_port/mips_formatter.c
        pc_port/gpu_bindings.c
        pc_port/device_reset_bindings.c
        pc_port/callback_bindings.c
        pc_port/event_bindings.c
        pc_port/cd_controller.c
        pc_port/cd_dma3.c
        pc_port/gpu_dma2.c
        pc_port/dma_otc.c
        pc_port/disc_media.c
        pc_port/spu_cd_audio.c
        pc_port/irq_controller.c
        pc_port/dma_controller.c
        pc_port/gpu_controller.c
        pc_port/mdec_controller.c
        pc_port/bios_events.c
        pc_port/bios_kernel.c
        pc_port/cpu_status.c
        pc_port/bios_exception.c
        pc_port/bios_heap.c
        pc_port/bios_card.c
        pc_port/bios_backup_unit.c
        pc_port/bios_input.c
        pc_port/source_clock.c
        pc_port/timer2.c
        pc_port/device_epoch.c
        pc_port/sio_controller.c
        pc_port/scanline_timer.c
        pc_port/irq_policy.c
        src/main/80043060.c
        src/main/8005c29c.c
        src/main/8005c388.c
        src/main/8005ccc8.c
        src/main/8005cd48.c
        src/main/8005c1c0.c
        src/main/8005bd7c.c
        src/main/800426fc.c
        src/main/80042c64.c
        src/main/800429dc.c
        src/main/80042f8c.c
        src/main/800425b0.c
        src/main/800425e0.c
        src/main/8001096c.c
        src/main/80042ce8.c
        src/main/80042e08.c
        src/main/800427f4.c
        src/main/800616d0.c
        src/main/8006291c.c
        src/main/80062988.c
        pc_port/vblank_bindings.c
        src/main/80016714.c
        src/main/80029044.c
        src/main/8002906c.c
        ${MUSASHI_PLATFORM_SOURCE}
    )
    # Only this decomp-owned translation unit receives the native word binding.
    # Retail compiler/oracle builds do not define it and retain the original ABI.
    set_source_files_properties(src/main/80043060.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_MEMORY_BINDING=1)
    set_source_files_properties(src/main/8005c388.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_CONSOLE_BINDING=1)
    set_source_files_properties(src/main/8005cd48.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_CONSOLE_BINDING=1)
    set_source_files_properties(src/main/8005c1c0.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_DEVICE_BINDING=1)
    set_source_files_properties(src/main/8005bd7c.c src/main/800426fc.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_DEVICE_BINDING=1)
    set_source_files_properties(src/main/80042c64.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_WORD_CLEAR_BINDING=1)
    set_source_files_properties(src/main/800429dc.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_CALLBACK_REGISTRATION=1)
    set_source_files_properties(src/main/80042f8c.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_DMA_REGISTRATION=1)
    set_source_files_properties(src/main/800425b0.c src/main/800425e0.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_CALLBACK_DISPATCH=1)
    set_source_files_properties(src/main/80042ce8.c src/main/8001096c.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_CALLBACK_HANDLER=1)
    set_source_files_properties(src/main/80042e08.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_DMA_IRQ_HANDLER=1)
    set_source_files_properties(src/main/800427f4.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_IRQ_DISPATCH=1)
    set_source_files_properties(src/main/800616d0.c src/main/8006291c.c src/main/80062988.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_VBLANK=1)
    set_source_files_properties(src/main/80016714.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_MEMSET_BINDING=1)
    set_source_files_properties(src/main/80029044.c src/main/8002906c.c PROPERTIES
        COMPILE_DEFINITIONS MUSASHI_NATIVE_TABLE_CLEAR_BINDING=1)
    target_include_directories(musashi_pc_port
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/pc_port/include
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/pc_port
            ${MUSASHI_GENERATED_DIR}
    )
    target_compile_features(musashi_pc_port PUBLIC c_std_99)
    target_link_libraries(musashi_pc_port PUBLIC musashi_shared PRIVATE OpenSSL::Crypto)
    if(MUSASHI_WITH_PSYCROSS)
        target_sources(musashi_pc_port PRIVATE
            pc_port/psyq_probe.c
            pc_port/irq_scheduler.c
            pc_port/gpu_psycross.c
            pc_port/gte_owner.c
            pc_port/audio_sdl.c
        )
        target_link_libraries(musashi_pc_port PUBLIC psycross_static)
        target_compile_definitions(musashi_pc_port PUBLIC MUSASHI_WITH_PSYCROSS=1)
    endif()

    add_executable(musashi_pc_smoke pc_port/main.c)
    target_compile_features(musashi_pc_smoke PRIVATE c_std_99)
    target_link_libraries(musashi_pc_smoke PRIVATE musashi_pc_port)

    enable_testing()
    add_test(NAME musashi_pc_smoke COMMAND musashi_pc_smoke)
    add_executable(musashi_entry_cpu_probe tests/entry_cpu_probe.c)
    target_compile_features(musashi_entry_cpu_probe PRIVATE c_std_99)
    target_link_libraries(musashi_entry_cpu_probe PRIVATE musashi_pc_port)
    add_test(NAME entry_cpu_boundary COMMAND musashi_entry_cpu_probe
        ${CMAKE_CURRENT_SOURCE_DIR}/extracted/disc/files/SLUS_007.26)
    set_tests_properties(entry_cpu_boundary PROPERTIES SKIP_RETURN_CODE 77)

    add_executable(musashi_boot_data_probe tests/boot_data_probe.c)
    target_compile_features(musashi_boot_data_probe PRIVATE c_std_99)
    target_link_libraries(musashi_boot_data_probe PRIVATE musashi_pc_port)
    add_test(NAME boot_data_boundary COMMAND musashi_boot_data_probe)

    add_executable(musashi_gpu_device_probe tests/gpu_device_probe.c)
    target_compile_features(musashi_gpu_device_probe PRIVATE c_std_99)
    target_link_libraries(musashi_gpu_device_probe PRIVATE musashi_pc_port)
    add_test(NAME gpu_device_boundary COMMAND musashi_gpu_device_probe)

    add_executable(musashi_device_reset_probe tests/device_reset_probe.c)
    target_compile_features(musashi_device_reset_probe PRIVATE c_std_99)
    target_link_libraries(musashi_device_reset_probe PRIVATE musashi_pc_port)
    add_test(NAME device_reset_boundary COMMAND musashi_device_reset_probe)

    add_executable(musashi_word_clear_probe tests/word_clear_probe.c)
    target_compile_features(musashi_word_clear_probe PRIVATE c_std_99)
    target_link_libraries(musashi_word_clear_probe PRIVATE musashi_pc_port)
    add_test(NAME word_clear_boundary COMMAND musashi_word_clear_probe)

    add_executable(musashi_heap_continuation_probe tests/heap_continuation_probe.c)
    target_compile_features(musashi_heap_continuation_probe PRIVATE c_std_99)
    target_include_directories(musashi_heap_continuation_probe PRIVATE "${MUSASHI_GENERATED_DIR}")
    target_link_libraries(musashi_heap_continuation_probe PRIVATE musashi_pc_port)
    add_test(NAME heap_continuation_source_cpu COMMAND musashi_heap_continuation_probe
        ${CMAKE_CURRENT_SOURCE_DIR}/extracted/disc/files/SLUS_007.26)
    set_tests_properties(heap_continuation_source_cpu PROPERTIES SKIP_RETURN_CODE 77)

    add_executable(musashi_event_registration_cpu_probe tests/event_registration_cpu_probe.c)
    target_compile_features(musashi_event_registration_cpu_probe PRIVATE c_std_99)
    target_include_directories(musashi_event_registration_cpu_probe PRIVATE "${MUSASHI_GENERATED_DIR}")
    target_link_libraries(musashi_event_registration_cpu_probe PRIVATE musashi_pc_port)
    add_test(NAME event_registration_source_cpu COMMAND musashi_event_registration_cpu_probe)

    add_executable(musashi_mips_formatter_probe tests/mips_formatter_probe.c)
    target_compile_features(musashi_mips_formatter_probe PRIVATE c_std_99)
    target_link_libraries(musashi_mips_formatter_probe PRIVATE musashi_pc_port)
    add_test(NAME mips_formatter_boundary COMMAND musashi_mips_formatter_probe)

    add_executable(musashi_callback_registration_probe tests/callback_registration_probe.c)
    target_compile_features(musashi_callback_registration_probe PRIVATE c_std_99)
    target_link_libraries(musashi_callback_registration_probe PRIVATE musashi_pc_port)
    add_test(NAME callback_registration_startup
        COMMAND musashi_callback_registration_probe
                ${CMAKE_CURRENT_SOURCE_DIR}/extracted/disc/files/SLUS_007.26)

    add_executable(musashi_irq_controller_probe tests/irq_controller_probe.c)
    target_compile_features(musashi_irq_controller_probe PRIVATE c_std_99)
    target_link_libraries(musashi_irq_controller_probe PRIVATE musashi_pc_port)
    add_test(NAME irq_controller_boundary COMMAND musashi_irq_controller_probe)

    if(MUSASHI_WITH_PSYCROSS)
        # Own pinned entry state and IRQ lifetime in an executable. This
        # currently stops at the first missing device; it is not a menu demo.
        add_library(musashi_x11_nograb SHARED pc_port/x11_nograb.c)
        target_include_directories(musashi_x11_nograb PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/pc_port/include)
        target_link_libraries(musashi_x11_nograb PRIVATE ${CMAKE_DL_LIBS})
        add_executable(musashi_native_boot pc_port/native_boot.c)
        target_compile_features(musashi_native_boot PRIVATE c_std_99)
        target_link_libraries(musashi_native_boot PRIVATE musashi_pc_port musashi_x11_nograb ${CMAKE_DL_LIBS})

        add_executable(musashi_gpu_psycross_probe tests/gpu_psycross_probe.c)
        target_compile_features(musashi_gpu_psycross_probe PRIVATE c_std_99)
        target_link_libraries(musashi_gpu_psycross_probe PRIVATE musashi_pc_port)
        add_test(NAME gpu_psycross_live COMMAND musashi_gpu_psycross_probe)
        set_tests_properties(gpu_psycross_live PROPERTIES SKIP_RETURN_CODE 77)

        # The probe supplies a test-owned VSyncCallback. Production resolves
        # the same bridge against PsyCross's actual VBlank event source.
        add_executable(musashi_irq_scheduler_probe
            tests/irq_scheduler_probe.c
            pc_port/irq_scheduler.c
            pc_port/cpu_status.c
            pc_port/mips_formatter.c
            pc_port/irq_controller.c
            pc_port/boot_memory.c
            src/main/800427f4.c
            src/main/80042ce8.c
            src/main/8001096c.c
            src/main/80042e08.c
            src/main/80042f8c.c
            src/main/800616d0.c
            src/main/8006291c.c
            src/main/80062988.c
        )
        target_compile_features(musashi_irq_scheduler_probe PRIVATE c_std_99)
        target_compile_definitions(musashi_irq_scheduler_probe PRIVATE
            MUSASHI_NATIVE_IRQ_DISPATCH=1
            MUSASHI_NATIVE_CALLBACK_HANDLER=1
            MUSASHI_NATIVE_DMA_IRQ_HANDLER=1
            MUSASHI_NATIVE_VBLANK=1
        )
        target_include_directories(musashi_irq_scheduler_probe PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/pc_port/include
            ${MUSASHI_GENERATED_DIR}
        )
        # Link the real CD executor without importing the PsyCross worker
        # into this synthetic source-registration fixture.
        target_compile_options(musashi_irq_scheduler_probe PRIVATE -ffunction-sections -fdata-sections)
        target_link_options(musashi_irq_scheduler_probe PRIVATE -Wl,--gc-sections)
        target_link_libraries(musashi_irq_scheduler_probe PRIVATE OpenSSL::Crypto SDL2::SDL2)
        add_test(NAME irq_scheduler_boundary COMMAND musashi_irq_scheduler_probe)

        # This one requires a real SDL/GL display because PsyCross owns the
        # VBlank thread. It returns 77 when no display can be initialized.
        add_executable(musashi_irq_scheduler_live_probe tests/irq_scheduler_live_probe.c)
        target_compile_features(musashi_irq_scheduler_live_probe PRIVATE c_std_99)
        target_link_libraries(musashi_irq_scheduler_live_probe PRIVATE musashi_pc_port)
        add_test(NAME irq_scheduler_live COMMAND musashi_irq_scheduler_live_probe)
        set_tests_properties(irq_scheduler_live PROPERTIES SKIP_RETURN_CODE 77)

        add_executable(musashi_input_irq_live_probe tests/input_irq_live_probe.c)
        target_compile_features(musashi_input_irq_live_probe PRIVATE c_std_99)
        target_link_libraries(musashi_input_irq_live_probe PRIVATE musashi_pc_port)
        add_test(NAME input_irq_live COMMAND musashi_input_irq_live_probe
            ${CMAKE_CURRENT_SOURCE_DIR}/extracted/disc/files/SLUS_007.26)
        set_tests_properties(input_irq_live PROPERTIES SKIP_RETURN_CODE 77)

        add_executable(musashi_card_irq_live_probe tests/card_irq_live_probe.c)
        target_compile_features(musashi_card_irq_live_probe PRIVATE c_std_99)
        target_link_libraries(musashi_card_irq_live_probe PRIVATE musashi_pc_port)
        add_test(NAME card_irq_live COMMAND musashi_card_irq_live_probe)
        set_tests_properties(card_irq_live PROPERTIES SKIP_RETURN_CODE 77)

        add_test(NAME callback_registration_live
            COMMAND musashi_callback_registration_probe
                    ${CMAKE_CURRENT_SOURCE_DIR}/extracted/disc/files/SLUS_007.26 --live)
        set_tests_properties(callback_registration_live PROPERTIES SKIP_RETURN_CODE 77)

        # Synthetic checks of retail startup's GTE command/register boundary.
        add_executable(musashi_startup_gte_probe tests/startup_gte_probe.c)
        target_compile_features(musashi_startup_gte_probe PRIVATE c_std_99)
        target_link_libraries(musashi_startup_gte_probe PRIVATE psycross_static)
        add_test(NAME startup_gte_probe COMMAND musashi_startup_gte_probe)
        add_test(NAME startup_gte_wrong_register
                 COMMAND musashi_startup_gte_probe --wrong-v0)
        set_tests_properties(startup_gte_wrong_register PROPERTIES WILL_FAIL TRUE)

        # Draws one quad through the Psy-Q layer and reports sampled pixels.
        # The verdict is made by tools/render_check.py so the comparison stays
        # unit-tested; the smoke test above stays display-free on purpose.
        add_executable(musashi_render_quad pc_port/render_quad.c)
        target_compile_features(musashi_render_quad PRIVATE c_std_99)
        target_link_libraries(musashi_render_quad PRIVATE musashi_pc_port)

        find_package(Python3 COMPONENTS Interpreter REQUIRED)
        add_test(NAME native_startup_boundary
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/native_boot_check.py
                    $<TARGET_FILE:musashi_native_boot>
                    ${CMAKE_CURRENT_SOURCE_DIR}/extracted/disc/files/SLUS_007.26)
        set_tests_properties(native_startup_boundary PROPERTIES SKIP_RETURN_CODE 77)
        add_test(
            NAME render_quad
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/render_check.py
                    $<TARGET_FILE:musashi_render_quad>
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
        # Without xvfb-run the check exits 77, which ctest reports as skipped
        # rather than passed vacuously or failed spuriously.
        set_tests_properties(render_quad PROPERTIES SKIP_RETURN_CODE 77)

        # Draws a real model from the disc. Needs the extracted model, which is
        # retail-derived and untracked, so the test is registered only when it
        # is present and is otherwise skipped rather than failed.
        add_executable(musashi_render_tmd pc_port/render_tmd.c)
        target_compile_features(musashi_render_tmd PRIVATE c_std_99)
        target_link_libraries(musashi_render_tmd PRIVATE musashi_pc_port)

        set(MUSASHI_TMD_MODEL ${CMAKE_CURRENT_SOURCE_DIR}/extracted/models/sc01_a97000.tmd)
        add_test(
            NAME render_tmd
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/render_check.py
                    $<TARGET_FILE:musashi_render_tmd>
                    --argument ${MUSASHI_TMD_MODEL}
                    --expect-inside 240,197,152
                    --expect-outside 0,0,255
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
        set_tests_properties(render_tmd PROPERTIES SKIP_RETURN_CODE 77)
        if(NOT EXISTS ${MUSASHI_TMD_MODEL})
            set_tests_properties(render_tmd PROPERTIES DISABLED TRUE)
            message(STATUS
                "render_tmd disabled: extract the model first with "
                "tools/extract_tmd.py --offset 0xA97000")
        endif()
    endif()
endif()
