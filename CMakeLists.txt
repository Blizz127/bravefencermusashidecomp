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
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e934.c
                ${MUSASHI_GENERATED_DIR}/8014e934_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014E934_RESULT)
    if(NOT MUSASHI_SC02_8014E934_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e934 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014e98c.c
                ${MUSASHI_GENERATED_DIR}/8014e98c_sc02_0031_words.inc --expected-words 48
        RESULT_VARIABLE MUSASHI_SC02_8014E98C_RESULT)
    if(NOT MUSASHI_SC02_8014E98C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014e98c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ea4c.c
                ${MUSASHI_GENERATED_DIR}/8014ea4c_sc02_0031_words.inc --expected-words 183
        RESULT_VARIABLE MUSASHI_SC02_8014EA4C_RESULT)
    if(NOT MUSASHI_SC02_8014EA4C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ea4c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ed28.c
                ${MUSASHI_GENERATED_DIR}/8014ed28_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014ED28_RESULT)
    if(NOT MUSASHI_SC02_8014ED28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ed28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ed80.c
                ${MUSASHI_GENERATED_DIR}/8014ed80_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_8014ED80_RESULT)
    if(NOT MUSASHI_SC02_8014ED80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ed80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ee14.c
                ${MUSASHI_GENERATED_DIR}/8014ee14_sc02_0031_words.inc --expected-words 248
        RESULT_VARIABLE MUSASHI_SC02_8014EE14_RESULT)
    if(NOT MUSASHI_SC02_8014EE14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ee14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014f1f4.c
                ${MUSASHI_GENERATED_DIR}/8014f1f4_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014F1F4_RESULT)
    if(NOT MUSASHI_SC02_8014F1F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014f1f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014f24c.c
                ${MUSASHI_GENERATED_DIR}/8014f24c_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_8014F24C_RESULT)
    if(NOT MUSASHI_SC02_8014F24C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014f24c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014f2e0.c
                ${MUSASHI_GENERATED_DIR}/8014f2e0_sc02_0031_words.inc --expected-words 66
        RESULT_VARIABLE MUSASHI_SC02_8014F2E0_RESULT)
    if(NOT MUSASHI_SC02_8014F2E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014f2e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014f3e8.c
                ${MUSASHI_GENERATED_DIR}/8014f3e8_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_8014F3E8_RESULT)
    if(NOT MUSASHI_SC02_8014F3E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014f3e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014f468.c
                ${MUSASHI_GENERATED_DIR}/8014f468_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014F468_RESULT)
    if(NOT MUSASHI_SC02_8014F468_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014f468 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014f4c0.c
                ${MUSASHI_GENERATED_DIR}/8014f4c0_sc02_0031_words.inc --expected-words 141
        RESULT_VARIABLE MUSASHI_SC02_8014F4C0_RESULT)
    if(NOT MUSASHI_SC02_8014F4C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014f4c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014f6f4.c
                ${MUSASHI_GENERATED_DIR}/8014f6f4_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014F6F4_RESULT)
    if(NOT MUSASHI_SC02_8014F6F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014f6f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014f74c.c
                ${MUSASHI_GENERATED_DIR}/8014f74c_sc02_0031_words.inc --expected-words 174
        RESULT_VARIABLE MUSASHI_SC02_8014F74C_RESULT)
    if(NOT MUSASHI_SC02_8014F74C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014f74c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014fa04.c
                ${MUSASHI_GENERATED_DIR}/8014fa04_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8014FA04_RESULT)
    if(NOT MUSASHI_SC02_8014FA04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014fa04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014fa70.c
                ${MUSASHI_GENERATED_DIR}/8014fa70_sc02_0031_words.inc --expected-words 84
        RESULT_VARIABLE MUSASHI_SC02_8014FA70_RESULT)
    if(NOT MUSASHI_SC02_8014FA70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014fa70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014fbc0.c
                ${MUSASHI_GENERATED_DIR}/8014fbc0_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014FBC0_RESULT)
    if(NOT MUSASHI_SC02_8014FBC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014fbc0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014fc18.c
                ${MUSASHI_GENERATED_DIR}/8014fc18_sc02_0031_words.inc --expected-words 57
        RESULT_VARIABLE MUSASHI_SC02_8014FC18_RESULT)
    if(NOT MUSASHI_SC02_8014FC18_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014fc18 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014fcfc.c
                ${MUSASHI_GENERATED_DIR}/8014fcfc_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014FCFC_RESULT)
    if(NOT MUSASHI_SC02_8014FCFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014fcfc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014fd54.c
                ${MUSASHI_GENERATED_DIR}/8014fd54_sc02_0031_words.inc --expected-words 40
        RESULT_VARIABLE MUSASHI_SC02_8014FD54_RESULT)
    if(NOT MUSASHI_SC02_8014FD54_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014fd54 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014fdf4.c
                ${MUSASHI_GENERATED_DIR}/8014fdf4_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8014FDF4_RESULT)
    if(NOT MUSASHI_SC02_8014FDF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014fdf4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014fe60.c
                ${MUSASHI_GENERATED_DIR}/8014fe60_sc02_0031_words.inc --expected-words 95
        RESULT_VARIABLE MUSASHI_SC02_8014FE60_RESULT)
    if(NOT MUSASHI_SC02_8014FE60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014fe60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014ffdc.c
                ${MUSASHI_GENERATED_DIR}/8014ffdc_sc02_0031_words.inc --expected-words 93
        RESULT_VARIABLE MUSASHI_SC02_8014FFDC_RESULT)
    if(NOT MUSASHI_SC02_8014FFDC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014ffdc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150150.c
                ${MUSASHI_GENERATED_DIR}/80150150_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150150_RESULT)
    if(NOT MUSASHI_SC02_80150150_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150150 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150170.c
                ${MUSASHI_GENERATED_DIR}/80150170_sc02_0031_words.inc --expected-words 95
        RESULT_VARIABLE MUSASHI_SC02_80150170_RESULT)
    if(NOT MUSASHI_SC02_80150170_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150170 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801502ec.c
                ${MUSASHI_GENERATED_DIR}/801502ec_sc02_0031_words.inc --expected-words 93
        RESULT_VARIABLE MUSASHI_SC02_801502EC_RESULT)
    if(NOT MUSASHI_SC02_801502EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801502ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150460.c
                ${MUSASHI_GENERATED_DIR}/80150460_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150460_RESULT)
    if(NOT MUSASHI_SC02_80150460_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150460 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150480.c
                ${MUSASHI_GENERATED_DIR}/80150480_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80150480_RESULT)
    if(NOT MUSASHI_SC02_80150480_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150480 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801504d8.c
                ${MUSASHI_GENERATED_DIR}/801504d8_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_801504D8_RESULT)
    if(NOT MUSASHI_SC02_801504D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801504d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150528.c
                ${MUSASHI_GENERATED_DIR}/80150528_sc02_0031_words.inc --expected-words 53
        RESULT_VARIABLE MUSASHI_SC02_80150528_RESULT)
    if(NOT MUSASHI_SC02_80150528_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150528 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801505fc.c
                ${MUSASHI_GENERATED_DIR}/801505fc_sc02_0031_words.inc --expected-words 42
        RESULT_VARIABLE MUSASHI_SC02_801505FC_RESULT)
    if(NOT MUSASHI_SC02_801505FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801505fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801506a4.c
                ${MUSASHI_GENERATED_DIR}/801506a4_sc02_0031_words.inc --expected-words 95
        RESULT_VARIABLE MUSASHI_SC02_801506A4_RESULT)
    if(NOT MUSASHI_SC02_801506A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801506a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150820.c
                ${MUSASHI_GENERATED_DIR}/80150820_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80150820_RESULT)
    if(NOT MUSASHI_SC02_80150820_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150820 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015086c.c
                ${MUSASHI_GENERATED_DIR}/8015086c_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8015086C_RESULT)
    if(NOT MUSASHI_SC02_8015086C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015086c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801508b4.c
                ${MUSASHI_GENERATED_DIR}/801508b4_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_801508B4_RESULT)
    if(NOT MUSASHI_SC02_801508B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801508b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801508f8.c
                ${MUSASHI_GENERATED_DIR}/801508f8_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_801508F8_RESULT)
    if(NOT MUSASHI_SC02_801508F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801508f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015094c.c
                ${MUSASHI_GENERATED_DIR}/8015094c_sc02_0031_words.inc --expected-words 73
        RESULT_VARIABLE MUSASHI_SC02_8015094C_RESULT)
    if(NOT MUSASHI_SC02_8015094C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015094c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150a70.c
                ${MUSASHI_GENERATED_DIR}/80150a70_sc02_0031_words.inc --expected-words 46
        RESULT_VARIABLE MUSASHI_SC02_80150A70_RESULT)
    if(NOT MUSASHI_SC02_80150A70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150a70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150b28.c
                ${MUSASHI_GENERATED_DIR}/80150b28_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_80150B28_RESULT)
    if(NOT MUSASHI_SC02_80150B28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150b28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150b9c.c
                ${MUSASHI_GENERATED_DIR}/80150b9c_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80150B9C_RESULT)
    if(NOT MUSASHI_SC02_80150B9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150b9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150ba4.c
                ${MUSASHI_GENERATED_DIR}/80150ba4_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80150BA4_RESULT)
    if(NOT MUSASHI_SC02_80150BA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150ba4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150bc8.c
                ${MUSASHI_GENERATED_DIR}/80150bc8_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_80150BC8_RESULT)
    if(NOT MUSASHI_SC02_80150BC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150bc8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150c48.c
                ${MUSASHI_GENERATED_DIR}/80150c48_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80150C48_RESULT)
    if(NOT MUSASHI_SC02_80150C48_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150c48 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150ca0.c
                ${MUSASHI_GENERATED_DIR}/80150ca0_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80150CA0_RESULT)
    if(NOT MUSASHI_SC02_80150CA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150ca0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150cc4.c
                ${MUSASHI_GENERATED_DIR}/80150cc4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150CC4_RESULT)
    if(NOT MUSASHI_SC02_80150CC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150cc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150ce4.c
                ${MUSASHI_GENERATED_DIR}/80150ce4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150CE4_RESULT)
    if(NOT MUSASHI_SC02_80150CE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150ce4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150d04.c
                ${MUSASHI_GENERATED_DIR}/80150d04_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150D04_RESULT)
    if(NOT MUSASHI_SC02_80150D04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150d04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150d24.c
                ${MUSASHI_GENERATED_DIR}/80150d24_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150D24_RESULT)
    if(NOT MUSASHI_SC02_80150D24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150d24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150d44.c
                ${MUSASHI_GENERATED_DIR}/80150d44_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150D44_RESULT)
    if(NOT MUSASHI_SC02_80150D44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150d44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150d64.c
                ${MUSASHI_GENERATED_DIR}/80150d64_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150D64_RESULT)
    if(NOT MUSASHI_SC02_80150D64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150d64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150d84.c
                ${MUSASHI_GENERATED_DIR}/80150d84_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150D84_RESULT)
    if(NOT MUSASHI_SC02_80150D84_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150d84 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150da4.c
                ${MUSASHI_GENERATED_DIR}/80150da4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150DA4_RESULT)
    if(NOT MUSASHI_SC02_80150DA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150da4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150dc4.c
                ${MUSASHI_GENERATED_DIR}/80150dc4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150DC4_RESULT)
    if(NOT MUSASHI_SC02_80150DC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150dc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150de4.c
                ${MUSASHI_GENERATED_DIR}/80150de4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150DE4_RESULT)
    if(NOT MUSASHI_SC02_80150DE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150de4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150e04.c
                ${MUSASHI_GENERATED_DIR}/80150e04_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150E04_RESULT)
    if(NOT MUSASHI_SC02_80150E04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150e04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150e24.c
                ${MUSASHI_GENERATED_DIR}/80150e24_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150E24_RESULT)
    if(NOT MUSASHI_SC02_80150E24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150e24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150e44.c
                ${MUSASHI_GENERATED_DIR}/80150e44_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150E44_RESULT)
    if(NOT MUSASHI_SC02_80150E44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150e44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150e64.c
                ${MUSASHI_GENERATED_DIR}/80150e64_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150E64_RESULT)
    if(NOT MUSASHI_SC02_80150E64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150e64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150e84.c
                ${MUSASHI_GENERATED_DIR}/80150e84_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150E84_RESULT)
    if(NOT MUSASHI_SC02_80150E84_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150e84 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150ea4.c
                ${MUSASHI_GENERATED_DIR}/80150ea4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80150EA4_RESULT)
    if(NOT MUSASHI_SC02_80150EA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150ea4 words")
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
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80180d74.c
                ${MUSASHI_GENERATED_DIR}/80180d74_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80180D74_RESULT)
    if(NOT MUSASHI_SC02_80180D74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80180d74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80180db0.c
                ${MUSASHI_GENERATED_DIR}/80180db0_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80180DB0_RESULT)
    if(NOT MUSASHI_SC02_80180DB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80180db0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80181224.c
                ${MUSASHI_GENERATED_DIR}/80181224_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80181224_RESULT)
    if(NOT MUSASHI_SC02_80181224_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80181224 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801599a4.c
                ${MUSASHI_GENERATED_DIR}/801599a4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801599A4_RESULT)
    if(NOT MUSASHI_SC02_801599A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801599a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015a1c8.c
                ${MUSASHI_GENERATED_DIR}/8015a1c8_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015A1C8_RESULT)
    if(NOT MUSASHI_SC02_8015A1C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015a1c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801553c0.c
                ${MUSASHI_GENERATED_DIR}/801553c0_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_801553C0_RESULT)
    if(NOT MUSASHI_SC02_801553C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801553c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154a74.c
                ${MUSASHI_GENERATED_DIR}/80154a74_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80154A74_RESULT)
    if(NOT MUSASHI_SC02_80154A74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154a74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154ab4.c
                ${MUSASHI_GENERATED_DIR}/80154ab4_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80154AB4_RESULT)
    if(NOT MUSASHI_SC02_80154AB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154ab4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154ae0.c
                ${MUSASHI_GENERATED_DIR}/80154ae0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80154AE0_RESULT)
    if(NOT MUSASHI_SC02_80154AE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154ae0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154b20.c
                ${MUSASHI_GENERATED_DIR}/80154b20_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80154B20_RESULT)
    if(NOT MUSASHI_SC02_80154B20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154b20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154b4c.c
                ${MUSASHI_GENERATED_DIR}/80154b4c_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80154B4C_RESULT)
    if(NOT MUSASHI_SC02_80154B4C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154b4c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154b7c.c
                ${MUSASHI_GENERATED_DIR}/80154b7c_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_80154B7C_RESULT)
    if(NOT MUSASHI_SC02_80154B7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154b7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154b98.c
                ${MUSASHI_GENERATED_DIR}/80154b98_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80154B98_RESULT)
    if(NOT MUSASHI_SC02_80154B98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154b98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154bc8.c
                ${MUSASHI_GENERATED_DIR}/80154bc8_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_80154BC8_RESULT)
    if(NOT MUSASHI_SC02_80154BC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154bc8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154be4.c
                ${MUSASHI_GENERATED_DIR}/80154be4_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80154BE4_RESULT)
    if(NOT MUSASHI_SC02_80154BE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154be4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154c24.c
                ${MUSASHI_GENERATED_DIR}/80154c24_sc02_0031_words.inc --expected-words 173
        RESULT_VARIABLE MUSASHI_SC02_80154C24_RESULT)
    if(NOT MUSASHI_SC02_80154C24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154c24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154ed8.c
                ${MUSASHI_GENERATED_DIR}/80154ed8_sc02_0031_words.inc --expected-words 49
        RESULT_VARIABLE MUSASHI_SC02_80154ED8_RESULT)
    if(NOT MUSASHI_SC02_80154ED8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154ed8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154f9c.c
                ${MUSASHI_GENERATED_DIR}/80154f9c_sc02_0031_words.inc --expected-words 88
        RESULT_VARIABLE MUSASHI_SC02_80154F9C_RESULT)
    if(NOT MUSASHI_SC02_80154F9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154f9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801550fc.c
                ${MUSASHI_GENERATED_DIR}/801550fc_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_801550FC_RESULT)
    if(NOT MUSASHI_SC02_801550FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801550fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155150.c
                ${MUSASHI_GENERATED_DIR}/80155150_sc02_0031_words.inc --expected-words 105
        RESULT_VARIABLE MUSASHI_SC02_80155150_RESULT)
    if(NOT MUSASHI_SC02_80155150_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155150 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151944.c
                ${MUSASHI_GENERATED_DIR}/80151944_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80151944_RESULT)
    if(NOT MUSASHI_SC02_80151944_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151944 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151d24.c
                ${MUSASHI_GENERATED_DIR}/80151d24_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80151D24_RESULT)
    if(NOT MUSASHI_SC02_80151D24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151d24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152058.c
                ${MUSASHI_GENERATED_DIR}/80152058_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80152058_RESULT)
    if(NOT MUSASHI_SC02_80152058_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152058 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801520dc.c
                ${MUSASHI_GENERATED_DIR}/801520dc_sc02_0031_words.inc --expected-words 46
        RESULT_VARIABLE MUSASHI_SC02_801520DC_RESULT)
    if(NOT MUSASHI_SC02_801520DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801520dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152370.c
                ${MUSASHI_GENERATED_DIR}/80152370_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80152370_RESULT)
    if(NOT MUSASHI_SC02_80152370_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152370 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152698.c
                ${MUSASHI_GENERATED_DIR}/80152698_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80152698_RESULT)
    if(NOT MUSASHI_SC02_80152698_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152698 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015282c.c
                ${MUSASHI_GENERATED_DIR}/8015282c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015282C_RESULT)
    if(NOT MUSASHI_SC02_8015282C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015282c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801528b0.c
                ${MUSASHI_GENERATED_DIR}/801528b0_sc02_0031_words.inc --expected-words 39
        RESULT_VARIABLE MUSASHI_SC02_801528B0_RESULT)
    if(NOT MUSASHI_SC02_801528B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801528b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152b6c.c
                ${MUSASHI_GENERATED_DIR}/80152b6c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80152B6C_RESULT)
    if(NOT MUSASHI_SC02_80152B6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152b6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152d24.c
                ${MUSASHI_GENERATED_DIR}/80152d24_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80152D24_RESULT)
    if(NOT MUSASHI_SC02_80152D24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152d24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152da8.c
                ${MUSASHI_GENERATED_DIR}/80152da8_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_80152DA8_RESULT)
    if(NOT MUSASHI_SC02_80152DA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152da8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153060.c
                ${MUSASHI_GENERATED_DIR}/80153060_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80153060_RESULT)
    if(NOT MUSASHI_SC02_80153060_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153060 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153320.c
                ${MUSASHI_GENERATED_DIR}/80153320_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80153320_RESULT)
    if(NOT MUSASHI_SC02_80153320_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153320 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128288.c
                ${MUSASHI_GENERATED_DIR}/80128288_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80128288_RESULT)
    if(NOT MUSASHI_SC02_80128288_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128288 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801612b8.c
                ${MUSASHI_GENERATED_DIR}/801612b8_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_801612B8_RESULT)
    if(NOT MUSASHI_SC02_801612B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801612b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80133784.c
                ${MUSASHI_GENERATED_DIR}/80133784_sc02_0031_words.inc --expected-words 203
        RESULT_VARIABLE MUSASHI_SC02_80133784_RESULT)
    if(NOT MUSASHI_SC02_80133784_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80133784 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80133ab0.c
                ${MUSASHI_GENERATED_DIR}/80133ab0_sc02_0031_words.inc --expected-words 137
        RESULT_VARIABLE MUSASHI_SC02_80133AB0_RESULT)
    if(NOT MUSASHI_SC02_80133AB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80133ab0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80159be4.c
                ${MUSASHI_GENERATED_DIR}/80159be4_sc02_0031_words.inc --expected-words 40
        RESULT_VARIABLE MUSASHI_SC02_80159BE4_RESULT)
    if(NOT MUSASHI_SC02_80159BE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80159be4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015444c.c
                ${MUSASHI_GENERATED_DIR}/8015444c_sc02_0031_words.inc --expected-words 363
        RESULT_VARIABLE MUSASHI_SC02_8015444C_RESULT)
    if(NOT MUSASHI_SC02_8015444C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015444c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155458.c
                ${MUSASHI_GENERATED_DIR}/80155458_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80155458_RESULT)
    if(NOT MUSASHI_SC02_80155458_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155458 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128218.c
                ${MUSASHI_GENERATED_DIR}/80128218_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80128218_RESULT)
    if(NOT MUSASHI_SC02_80128218_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128218 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801288b0.c
                ${MUSASHI_GENERATED_DIR}/801288b0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801288B0_RESULT)
    if(NOT MUSASHI_SC02_801288B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801288b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128940.c
                ${MUSASHI_GENERATED_DIR}/80128940_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80128940_RESULT)
    if(NOT MUSASHI_SC02_80128940_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128940 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128998.c
                ${MUSASHI_GENERATED_DIR}/80128998_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80128998_RESULT)
    if(NOT MUSASHI_SC02_80128998_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128998 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801289f0.c
                ${MUSASHI_GENERATED_DIR}/801289f0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801289F0_RESULT)
    if(NOT MUSASHI_SC02_801289F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801289f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128c98.c
                ${MUSASHI_GENERATED_DIR}/80128c98_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80128C98_RESULT)
    if(NOT MUSASHI_SC02_80128C98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128c98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128cfc.c
                ${MUSASHI_GENERATED_DIR}/80128cfc_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80128CFC_RESULT)
    if(NOT MUSASHI_SC02_80128CFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128cfc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128fac.c
                ${MUSASHI_GENERATED_DIR}/80128fac_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80128FAC_RESULT)
    if(NOT MUSASHI_SC02_80128FAC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128fac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012db84.c
                ${MUSASHI_GENERATED_DIR}/8012db84_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8012DB84_RESULT)
    if(NOT MUSASHI_SC02_8012DB84_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012db84 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013373c.c
                ${MUSASHI_GENERATED_DIR}/8013373c_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8013373C_RESULT)
    if(NOT MUSASHI_SC02_8013373C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013373c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80133cd4.c
                ${MUSASHI_GENERATED_DIR}/80133cd4_sc02_0031_words.inc --expected-words 399
        RESULT_VARIABLE MUSASHI_SC02_80133CD4_RESULT)
    if(NOT MUSASHI_SC02_80133CD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80133cd4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80136c90.c
                ${MUSASHI_GENERATED_DIR}/80136c90_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80136C90_RESULT)
    if(NOT MUSASHI_SC02_80136C90_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80136c90 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80137b80.c
                ${MUSASHI_GENERATED_DIR}/80137b80_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80137B80_RESULT)
    if(NOT MUSASHI_SC02_80137B80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80137b80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013ad38.c
                ${MUSASHI_GENERATED_DIR}/8013ad38_sc02_0031_words.inc --expected-words 122
        RESULT_VARIABLE MUSASHI_SC02_8013AD38_RESULT)
    if(NOT MUSASHI_SC02_8013AD38_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013ad38 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013b274.c
                ${MUSASHI_GENERATED_DIR}/8013b274_sc02_0031_words.inc --expected-words 189
        RESULT_VARIABLE MUSASHI_SC02_8013B274_RESULT)
    if(NOT MUSASHI_SC02_8013B274_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013b274 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013b7ac.c
                ${MUSASHI_GENERATED_DIR}/8013b7ac_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8013B7AC_RESULT)
    if(NOT MUSASHI_SC02_8013B7AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013b7ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013b7f4.c
                ${MUSASHI_GENERATED_DIR}/8013b7f4_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8013B7F4_RESULT)
    if(NOT MUSASHI_SC02_8013B7F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013b7f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013bd34.c
                ${MUSASHI_GENERATED_DIR}/8013bd34_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8013BD34_RESULT)
    if(NOT MUSASHI_SC02_8013BD34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013bd34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013c938.c
                ${MUSASHI_GENERATED_DIR}/8013c938_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8013C938_RESULT)
    if(NOT MUSASHI_SC02_8013C938_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013c938 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013c964.c
                ${MUSASHI_GENERATED_DIR}/8013c964_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8013C964_RESULT)
    if(NOT MUSASHI_SC02_8013C964_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013c964 words")
    endif()

    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161c24.c
                ${MUSASHI_GENERATED_DIR}/80161c24_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_80161C24_RESULT)
    if(NOT MUSASHI_SC02_80161C24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161c24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013c9c4.c
                ${MUSASHI_GENERATED_DIR}/8013c9c4_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8013C9C4_RESULT)
    if(NOT MUSASHI_SC02_8013C9C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013c9c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013d330.c
                ${MUSASHI_GENERATED_DIR}/8013d330_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_8013D330_RESULT)
    if(NOT MUSASHI_SC02_8013D330_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013d330 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80164e40.c
                ${MUSASHI_GENERATED_DIR}/80164e40_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80164E40_RESULT)
    if(NOT MUSASHI_SC02_80164E40_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80164e40 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013cabc.c
                ${MUSASHI_GENERATED_DIR}/8013cabc_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8013CABC_RESULT)
    if(NOT MUSASHI_SC02_8013CABC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013cabc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013cae8.c
                ${MUSASHI_GENERATED_DIR}/8013cae8_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8013CAE8_RESULT)
    if(NOT MUSASHI_SC02_8013CAE8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013cae8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013cb20.c
                ${MUSASHI_GENERATED_DIR}/8013cb20_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8013CB20_RESULT)
    if(NOT MUSASHI_SC02_8013CB20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013cb20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013cb5c.c
                ${MUSASHI_GENERATED_DIR}/8013cb5c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8013CB5C_RESULT)
    if(NOT MUSASHI_SC02_8013CB5C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013cb5c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013d064.c
                ${MUSASHI_GENERATED_DIR}/8013d064_sc02_0031_words.inc --expected-words 54
        RESULT_VARIABLE MUSASHI_SC02_8013D064_RESULT)
    if(NOT MUSASHI_SC02_8013D064_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013d064 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013d13c.c
                ${MUSASHI_GENERATED_DIR}/8013d13c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8013D13C_RESULT)
    if(NOT MUSASHI_SC02_8013D13C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013d13c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013d164.c
                ${MUSASHI_GENERATED_DIR}/8013d164_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8013D164_RESULT)
    if(NOT MUSASHI_SC02_8013D164_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013d164 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013d9b0.c
                ${MUSASHI_GENERATED_DIR}/8013d9b0_sc02_0031_words.inc --expected-words 141
        RESULT_VARIABLE MUSASHI_SC02_8013D9B0_RESULT)
    if(NOT MUSASHI_SC02_8013D9B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013d9b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e054.c
                ${MUSASHI_GENERATED_DIR}/8013e054_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8013E054_RESULT)
    if(NOT MUSASHI_SC02_8013E054_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e054 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80140f00.c
                ${MUSASHI_GENERATED_DIR}/80140f00_sc02_0031_words.inc --expected-words 128
        RESULT_VARIABLE MUSASHI_SC02_80140F00_RESULT)
    if(NOT MUSASHI_SC02_80140F00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80140f00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014358c.c
                ${MUSASHI_GENERATED_DIR}/8014358c_sc02_0031_words.inc --expected-words 45
        RESULT_VARIABLE MUSASHI_SC02_8014358C_RESULT)
    if(NOT MUSASHI_SC02_8014358C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014358c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153ccc.c
                ${MUSASHI_GENERATED_DIR}/80153ccc_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_80153CCC_RESULT)
    if(NOT MUSASHI_SC02_80153CCC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153ccc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157788.c
                ${MUSASHI_GENERATED_DIR}/80157788_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80157788_RESULT)
    if(NOT MUSASHI_SC02_80157788_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157788 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801577c8.c
                ${MUSASHI_GENERATED_DIR}/801577c8_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801577C8_RESULT)
    if(NOT MUSASHI_SC02_801577C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801577c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157808.c
                ${MUSASHI_GENERATED_DIR}/80157808_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_80157808_RESULT)
    if(NOT MUSASHI_SC02_80157808_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157808 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015879c.c
                ${MUSASHI_GENERATED_DIR}/8015879c_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_8015879C_RESULT)
    if(NOT MUSASHI_SC02_8015879C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015879c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80158814.c
                ${MUSASHI_GENERATED_DIR}/80158814_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80158814_RESULT)
    if(NOT MUSASHI_SC02_80158814_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80158814 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80158fa4.c
                ${MUSASHI_GENERATED_DIR}/80158fa4_sc02_0031_words.inc --expected-words 51
        RESULT_VARIABLE MUSASHI_SC02_80158FA4_RESULT)
    if(NOT MUSASHI_SC02_80158FA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80158fa4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015934c.c
                ${MUSASHI_GENERATED_DIR}/8015934c_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_8015934C_RESULT)
    if(NOT MUSASHI_SC02_8015934C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015934c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015c7e4.c
                ${MUSASHI_GENERATED_DIR}/8015c7e4_sc02_0031_words.inc --expected-words 88
        RESULT_VARIABLE MUSASHI_SC02_8015C7E4_RESULT)
    if(NOT MUSASHI_SC02_8015C7E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015c7e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ca28.c
                ${MUSASHI_GENERATED_DIR}/8015ca28_sc02_0031_words.inc --expected-words 91
        RESULT_VARIABLE MUSASHI_SC02_8015CA28_RESULT)
    if(NOT MUSASHI_SC02_8015CA28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ca28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015cd20.c
                ${MUSASHI_GENERATED_DIR}/8015cd20_sc02_0031_words.inc --expected-words 129
        RESULT_VARIABLE MUSASHI_SC02_8015CD20_RESULT)
    if(NOT MUSASHI_SC02_8015CD20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015cd20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015d5e8.c
                ${MUSASHI_GENERATED_DIR}/8015d5e8_sc02_0031_words.inc --expected-words 84
        RESULT_VARIABLE MUSASHI_SC02_8015D5E8_RESULT)
    if(NOT MUSASHI_SC02_8015D5E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015d5e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016216c.c
                ${MUSASHI_GENERATED_DIR}/8016216c_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8016216C_RESULT)
    if(NOT MUSASHI_SC02_8016216C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016216c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801622c4.c
                ${MUSASHI_GENERATED_DIR}/801622c4_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_801622C4_RESULT)
    if(NOT MUSASHI_SC02_801622C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801622c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162760.c
                ${MUSASHI_GENERATED_DIR}/80162760_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80162760_RESULT)
    if(NOT MUSASHI_SC02_80162760_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162760 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80163408.c
                ${MUSASHI_GENERATED_DIR}/80163408_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80163408_RESULT)
    if(NOT MUSASHI_SC02_80163408_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80163408 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801634d8.c
                ${MUSASHI_GENERATED_DIR}/801634d8_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_801634D8_RESULT)
    if(NOT MUSASHI_SC02_801634D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801634d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80164ee0.c
                ${MUSASHI_GENERATED_DIR}/80164ee0_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80164EE0_RESULT)
    if(NOT MUSASHI_SC02_80164EE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80164ee0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165e2c.c
                ${MUSASHI_GENERATED_DIR}/80165e2c_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80165E2C_RESULT)
    if(NOT MUSASHI_SC02_80165E2C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165e2c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80169f3c.c
                ${MUSASHI_GENERATED_DIR}/80169f3c_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_80169F3C_RESULT)
    if(NOT MUSASHI_SC02_80169F3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80169f3c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016b9f8.c
                ${MUSASHI_GENERATED_DIR}/8016b9f8_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8016B9F8_RESULT)
    if(NOT MUSASHI_SC02_8016B9F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016b9f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016bea0.c
                ${MUSASHI_GENERATED_DIR}/8016bea0_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_8016BEA0_RESULT)
    if(NOT MUSASHI_SC02_8016BEA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016bea0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016bfa8.c
                ${MUSASHI_GENERATED_DIR}/8016bfa8_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8016BFA8_RESULT)
    if(NOT MUSASHI_SC02_8016BFA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016bfa8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016da7c.c
                ${MUSASHI_GENERATED_DIR}/8016da7c_sc02_0031_words.inc --expected-words 46
        RESULT_VARIABLE MUSASHI_SC02_8016DA7C_RESULT)
    if(NOT MUSASHI_SC02_8016DA7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016da7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80178438.c
                ${MUSASHI_GENERATED_DIR}/80178438_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80178438_RESULT)
    if(NOT MUSASHI_SC02_80178438_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80178438 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80178840.c
                ${MUSASHI_GENERATED_DIR}/80178840_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_80178840_RESULT)
    if(NOT MUSASHI_SC02_80178840_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80178840 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80178cbc.c
                ${MUSASHI_GENERATED_DIR}/80178cbc_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80178CBC_RESULT)
    if(NOT MUSASHI_SC02_80178CBC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80178cbc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80178d18.c
                ${MUSASHI_GENERATED_DIR}/80178d18_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80178D18_RESULT)
    if(NOT MUSASHI_SC02_80178D18_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80178d18 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a094.c
                ${MUSASHI_GENERATED_DIR}/8017a094_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8017A094_RESULT)
    if(NOT MUSASHI_SC02_8017A094_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a094 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a0c4.c
                ${MUSASHI_GENERATED_DIR}/8017a0c4_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8017A0C4_RESULT)
    if(NOT MUSASHI_SC02_8017A0C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a0c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a144.c
                ${MUSASHI_GENERATED_DIR}/8017a144_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017A144_RESULT)
    if(NOT MUSASHI_SC02_8017A144_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a144 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017b1d8.c
                ${MUSASHI_GENERATED_DIR}/8017b1d8_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8017B1D8_RESULT)
    if(NOT MUSASHI_SC02_8017B1D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017b1d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017b7a8.c
                ${MUSASHI_GENERATED_DIR}/8017b7a8_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_8017B7A8_RESULT)
    if(NOT MUSASHI_SC02_8017B7A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017b7a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017b880.c
                ${MUSASHI_GENERATED_DIR}/8017b880_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_8017B880_RESULT)
    if(NOT MUSASHI_SC02_8017B880_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017b880 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017b8e8.c
                ${MUSASHI_GENERATED_DIR}/8017b8e8_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8017B8E8_RESULT)
    if(NOT MUSASHI_SC02_8017B8E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017b8e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017bc38.c
                ${MUSASHI_GENERATED_DIR}/8017bc38_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_8017BC38_RESULT)
    if(NOT MUSASHI_SC02_8017BC38_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017bc38 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017bca0.c
                ${MUSASHI_GENERATED_DIR}/8017bca0_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8017BCA0_RESULT)
    if(NOT MUSASHI_SC02_8017BCA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017bca0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017bcf4.c
                ${MUSASHI_GENERATED_DIR}/8017bcf4_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_8017BCF4_RESULT)
    if(NOT MUSASHI_SC02_8017BCF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017bcf4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e9c0.c
                ${MUSASHI_GENERATED_DIR}/8012e9c0_sc02_0031_words.inc --expected-words 52
        RESULT_VARIABLE MUSASHI_SC02_8012E9C0_RESULT)
    if(NOT MUSASHI_SC02_8012E9C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e9c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f828.c
                ${MUSASHI_GENERATED_DIR}/8012f828_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8012F828_RESULT)
    if(NOT MUSASHI_SC02_8012F828_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f828 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f8c8.c
                ${MUSASHI_GENERATED_DIR}/8012f8c8_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8012F8C8_RESULT)
    if(NOT MUSASHI_SC02_8012F8C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f8c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012fcc4.c
                ${MUSASHI_GENERATED_DIR}/8012fcc4_sc02_0031_words.inc --expected-words 57
        RESULT_VARIABLE MUSASHI_SC02_8012FCC4_RESULT)
    if(NOT MUSASHI_SC02_8012FCC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012fcc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130d0c.c
                ${MUSASHI_GENERATED_DIR}/80130d0c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80130D0C_RESULT)
    if(NOT MUSASHI_SC02_80130D0C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130d0c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80131e00.c
                ${MUSASHI_GENERATED_DIR}/80131e00_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80131E00_RESULT)
    if(NOT MUSASHI_SC02_80131E00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80131e00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80131eec.c
                ${MUSASHI_GENERATED_DIR}/80131eec_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80131EEC_RESULT)
    if(NOT MUSASHI_SC02_80131EEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80131eec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80131f28.c
                ${MUSASHI_GENERATED_DIR}/80131f28_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80131F28_RESULT)
    if(NOT MUSASHI_SC02_80131F28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80131f28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80131f64.c
                ${MUSASHI_GENERATED_DIR}/80131f64_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80131F64_RESULT)
    if(NOT MUSASHI_SC02_80131F64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80131f64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80131fa0.c
                ${MUSASHI_GENERATED_DIR}/80131fa0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80131FA0_RESULT)
    if(NOT MUSASHI_SC02_80131FA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80131fa0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801320d8.c
                ${MUSASHI_GENERATED_DIR}/801320d8_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_801320D8_RESULT)
    if(NOT MUSASHI_SC02_801320D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801320d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80132144.c
                ${MUSASHI_GENERATED_DIR}/80132144_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80132144_RESULT)
    if(NOT MUSASHI_SC02_80132144_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80132144 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801321b0.c
                ${MUSASHI_GENERATED_DIR}/801321b0_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_801321B0_RESULT)
    if(NOT MUSASHI_SC02_801321B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801321b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80136c54.c
                ${MUSASHI_GENERATED_DIR}/80136c54_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80136C54_RESULT)
    if(NOT MUSASHI_SC02_80136C54_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80136c54 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80137d08.c
                ${MUSASHI_GENERATED_DIR}/80137d08_sc02_0031_words.inc --expected-words 51
        RESULT_VARIABLE MUSASHI_SC02_80137D08_RESULT)
    if(NOT MUSASHI_SC02_80137D08_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80137d08 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80138be0.c
                ${MUSASHI_GENERATED_DIR}/80138be0_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80138BE0_RESULT)
    if(NOT MUSASHI_SC02_80138BE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80138be0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013bc7c.c
                ${MUSASHI_GENERATED_DIR}/8013bc7c_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8013BC7C_RESULT)
    if(NOT MUSASHI_SC02_8013BC7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013bc7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80141788.c
                ${MUSASHI_GENERATED_DIR}/80141788_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80141788_RESULT)
    if(NOT MUSASHI_SC02_80141788_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80141788 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80141c0c.c
                ${MUSASHI_GENERATED_DIR}/80141c0c_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80141C0C_RESULT)
    if(NOT MUSASHI_SC02_80141C0C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80141c0c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801425cc.c
                ${MUSASHI_GENERATED_DIR}/801425cc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801425CC_RESULT)
    if(NOT MUSASHI_SC02_801425CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801425cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801427ec.c
                ${MUSASHI_GENERATED_DIR}/801427ec_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_801427EC_RESULT)
    if(NOT MUSASHI_SC02_801427EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801427ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014292c.c
                ${MUSASHI_GENERATED_DIR}/8014292c_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8014292C_RESULT)
    if(NOT MUSASHI_SC02_8014292C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014292c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142978.c
                ${MUSASHI_GENERATED_DIR}/80142978_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80142978_RESULT)
    if(NOT MUSASHI_SC02_80142978_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142978 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801429c4.c
                ${MUSASHI_GENERATED_DIR}/801429c4_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_801429C4_RESULT)
    if(NOT MUSASHI_SC02_801429C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801429c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142a10.c
                ${MUSASHI_GENERATED_DIR}/80142a10_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80142A10_RESULT)
    if(NOT MUSASHI_SC02_80142A10_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142a10 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143458.c
                ${MUSASHI_GENERATED_DIR}/80143458_sc02_0031_words.inc --expected-words 45
        RESULT_VARIABLE MUSASHI_SC02_80143458_RESULT)
    if(NOT MUSASHI_SC02_80143458_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143458 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143b30.c
                ${MUSASHI_GENERATED_DIR}/80143b30_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80143B30_RESULT)
    if(NOT MUSASHI_SC02_80143B30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143b30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143c38.c
                ${MUSASHI_GENERATED_DIR}/80143c38_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80143C38_RESULT)
    if(NOT MUSASHI_SC02_80143C38_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143c38 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143c98.c
                ${MUSASHI_GENERATED_DIR}/80143c98_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80143C98_RESULT)
    if(NOT MUSASHI_SC02_80143C98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143c98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143e68.c
                ${MUSASHI_GENERATED_DIR}/80143e68_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80143E68_RESULT)
    if(NOT MUSASHI_SC02_80143E68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143e68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155580.c
                ${MUSASHI_GENERATED_DIR}/80155580_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80155580_RESULT)
    if(NOT MUSASHI_SC02_80155580_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155580 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801563ec.c
                ${MUSASHI_GENERATED_DIR}/801563ec_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801563EC_RESULT)
    if(NOT MUSASHI_SC02_801563EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801563ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80156a1c.c
                ${MUSASHI_GENERATED_DIR}/80156a1c_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80156A1C_RESULT)
    if(NOT MUSASHI_SC02_80156A1C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80156a1c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157544.c
                ${MUSASHI_GENERATED_DIR}/80157544_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80157544_RESULT)
    if(NOT MUSASHI_SC02_80157544_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157544 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801578c0.c
                ${MUSASHI_GENERATED_DIR}/801578c0_sc02_0031_words.inc --expected-words 39
        RESULT_VARIABLE MUSASHI_SC02_801578C0_RESULT)
    if(NOT MUSASHI_SC02_801578C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801578c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157d20.c
                ${MUSASHI_GENERATED_DIR}/80157d20_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80157D20_RESULT)
    if(NOT MUSASHI_SC02_80157D20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157d20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157dc4.c
                ${MUSASHI_GENERATED_DIR}/80157dc4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80157DC4_RESULT)
    if(NOT MUSASHI_SC02_80157DC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157dc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157fc4.c
                ${MUSASHI_GENERATED_DIR}/80157fc4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80157FC4_RESULT)
    if(NOT MUSASHI_SC02_80157FC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157fc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80158038.c
                ${MUSASHI_GENERATED_DIR}/80158038_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_80158038_RESULT)
    if(NOT MUSASHI_SC02_80158038_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80158038 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015824c.c
                ${MUSASHI_GENERATED_DIR}/8015824c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015824C_RESULT)
    if(NOT MUSASHI_SC02_8015824C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015824c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80158880.c
                ${MUSASHI_GENERATED_DIR}/80158880_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80158880_RESULT)
    if(NOT MUSASHI_SC02_80158880_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80158880 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80159698.c
                ${MUSASHI_GENERATED_DIR}/80159698_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80159698_RESULT)
    if(NOT MUSASHI_SC02_80159698_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80159698 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80159968.c
                ${MUSASHI_GENERATED_DIR}/80159968_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80159968_RESULT)
    if(NOT MUSASHI_SC02_80159968_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80159968 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80159b70.c
                ${MUSASHI_GENERATED_DIR}/80159b70_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80159B70_RESULT)
    if(NOT MUSASHI_SC02_80159B70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80159b70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015a264.c
                ${MUSASHI_GENERATED_DIR}/8015a264_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015A264_RESULT)
    if(NOT MUSASHI_SC02_8015A264_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015a264 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ac48.c
                ${MUSASHI_GENERATED_DIR}/8015ac48_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8015AC48_RESULT)
    if(NOT MUSASHI_SC02_8015AC48_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ac48 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ad3c.c
                ${MUSASHI_GENERATED_DIR}/8015ad3c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015AD3C_RESULT)
    if(NOT MUSASHI_SC02_8015AD3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ad3c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015be38.c
                ${MUSASHI_GENERATED_DIR}/8015be38_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015BE38_RESULT)
    if(NOT MUSASHI_SC02_8015BE38_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015be38 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015bff4.c
                ${MUSASHI_GENERATED_DIR}/8015bff4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015BFF4_RESULT)
    if(NOT MUSASHI_SC02_8015BFF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015bff4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015c714.c
                ${MUSASHI_GENERATED_DIR}/8015c714_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015C714_RESULT)
    if(NOT MUSASHI_SC02_8015C714_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015c714 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015c944.c
                ${MUSASHI_GENERATED_DIR}/8015c944_sc02_0031_words.inc --expected-words 57
        RESULT_VARIABLE MUSASHI_SC02_8015C944_RESULT)
    if(NOT MUSASHI_SC02_8015C944_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015c944 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015cc74.c
                ${MUSASHI_GENERATED_DIR}/8015cc74_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015CC74_RESULT)
    if(NOT MUSASHI_SC02_8015CC74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015cc74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015cfc0.c
                ${MUSASHI_GENERATED_DIR}/8015cfc0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015CFC0_RESULT)
    if(NOT MUSASHI_SC02_8015CFC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015cfc0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015d01c.c
                ${MUSASHI_GENERATED_DIR}/8015d01c_sc02_0031_words.inc --expected-words 58
        RESULT_VARIABLE MUSASHI_SC02_8015D01C_RESULT)
    if(NOT MUSASHI_SC02_8015D01C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015d01c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015d104.c
                ${MUSASHI_GENERATED_DIR}/8015d104_sc02_0031_words.inc --expected-words 45
        RESULT_VARIABLE MUSASHI_SC02_8015D104_RESULT)
    if(NOT MUSASHI_SC02_8015D104_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015d104 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015d414.c
                ${MUSASHI_GENERATED_DIR}/8015d414_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8015D414_RESULT)
    if(NOT MUSASHI_SC02_8015D414_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015d414 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015d4e8.c
                ${MUSASHI_GENERATED_DIR}/8015d4e8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015D4E8_RESULT)
    if(NOT MUSASHI_SC02_8015D4E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015d4e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015daf8.c
                ${MUSASHI_GENERATED_DIR}/8015daf8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015DAF8_RESULT)
    if(NOT MUSASHI_SC02_8015DAF8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015daf8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015dbd4.c
                ${MUSASHI_GENERATED_DIR}/8015dbd4_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_8015DBD4_RESULT)
    if(NOT MUSASHI_SC02_8015DBD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015dbd4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015de58.c
                ${MUSASHI_GENERATED_DIR}/8015de58_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015DE58_RESULT)
    if(NOT MUSASHI_SC02_8015DE58_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015de58 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015df34.c
                ${MUSASHI_GENERATED_DIR}/8015df34_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_8015DF34_RESULT)
    if(NOT MUSASHI_SC02_8015DF34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015df34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e1b8.c
                ${MUSASHI_GENERATED_DIR}/8015e1b8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015E1B8_RESULT)
    if(NOT MUSASHI_SC02_8015E1B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e1b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e344.c
                ${MUSASHI_GENERATED_DIR}/8015e344_sc02_0031_words.inc --expected-words 50
        RESULT_VARIABLE MUSASHI_SC02_8015E344_RESULT)
    if(NOT MUSASHI_SC02_8015E344_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e344 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e588.c
                ${MUSASHI_GENERATED_DIR}/8015e588_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8015E588_RESULT)
    if(NOT MUSASHI_SC02_8015E588_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e588 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e698.c
                ${MUSASHI_GENERATED_DIR}/8015e698_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_8015E698_RESULT)
    if(NOT MUSASHI_SC02_8015E698_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e698 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e8e8.c
                ${MUSASHI_GENERATED_DIR}/8015e8e8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015E8E8_RESULT)
    if(NOT MUSASHI_SC02_8015E8E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e8e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ee08.c
                ${MUSASHI_GENERATED_DIR}/8015ee08_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015EE08_RESULT)
    if(NOT MUSASHI_SC02_8015EE08_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ee08 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ee7c.c
                ${MUSASHI_GENERATED_DIR}/8015ee7c_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_8015EE7C_RESULT)
    if(NOT MUSASHI_SC02_8015EE7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ee7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015eee0.c
                ${MUSASHI_GENERATED_DIR}/8015eee0_sc02_0031_words.inc --expected-words 47
        RESULT_VARIABLE MUSASHI_SC02_8015EEE0_RESULT)
    if(NOT MUSASHI_SC02_8015EEE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015eee0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f00c.c
                ${MUSASHI_GENERATED_DIR}/8015f00c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015F00C_RESULT)
    if(NOT MUSASHI_SC02_8015F00C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f00c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f118.c
                ${MUSASHI_GENERATED_DIR}/8015f118_sc02_0031_words.inc --expected-words 82
        RESULT_VARIABLE MUSASHI_SC02_8015F118_RESULT)
    if(NOT MUSASHI_SC02_8015F118_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f118 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f324.c
                ${MUSASHI_GENERATED_DIR}/8015f324_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015F324_RESULT)
    if(NOT MUSASHI_SC02_8015F324_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f324 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f7d4.c
                ${MUSASHI_GENERATED_DIR}/8015f7d4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015F7D4_RESULT)
    if(NOT MUSASHI_SC02_8015F7D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f7d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f9a4.c
                ${MUSASHI_GENERATED_DIR}/8015f9a4_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_8015F9A4_RESULT)
    if(NOT MUSASHI_SC02_8015F9A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f9a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015faac.c
                ${MUSASHI_GENERATED_DIR}/8015faac_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8015FAAC_RESULT)
    if(NOT MUSASHI_SC02_8015FAAC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015faac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015fbe0.c
                ${MUSASHI_GENERATED_DIR}/8015fbe0_sc02_0031_words.inc --expected-words 58
        RESULT_VARIABLE MUSASHI_SC02_8015FBE0_RESULT)
    if(NOT MUSASHI_SC02_8015FBE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015fbe0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015fcc8.c
                ${MUSASHI_GENERATED_DIR}/8015fcc8_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_8015FCC8_RESULT)
    if(NOT MUSASHI_SC02_8015FCC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015fcc8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015fd74.c
                ${MUSASHI_GENERATED_DIR}/8015fd74_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8015FD74_RESULT)
    if(NOT MUSASHI_SC02_8015FD74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015fd74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015fe70.c
                ${MUSASHI_GENERATED_DIR}/8015fe70_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_8015FE70_RESULT)
    if(NOT MUSASHI_SC02_8015FE70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015fe70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160138.c
                ${MUSASHI_GENERATED_DIR}/80160138_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80160138_RESULT)
    if(NOT MUSASHI_SC02_80160138_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160138 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801602a4.c
                ${MUSASHI_GENERATED_DIR}/801602a4_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_801602A4_RESULT)
    if(NOT MUSASHI_SC02_801602A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801602a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016039c.c
                ${MUSASHI_GENERATED_DIR}/8016039c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016039C_RESULT)
    if(NOT MUSASHI_SC02_8016039C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016039c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016084c.c
                ${MUSASHI_GENERATED_DIR}/8016084c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016084C_RESULT)
    if(NOT MUSASHI_SC02_8016084C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016084c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160920.c
                ${MUSASHI_GENERATED_DIR}/80160920_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_80160920_RESULT)
    if(NOT MUSASHI_SC02_80160920_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160920 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801609b8.c
                ${MUSASHI_GENERATED_DIR}/801609b8_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_801609B8_RESULT)
    if(NOT MUSASHI_SC02_801609B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801609b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160b34.c
                ${MUSASHI_GENERATED_DIR}/80160b34_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80160B34_RESULT)
    if(NOT MUSASHI_SC02_80160B34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160b34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160ea4.c
                ${MUSASHI_GENERATED_DIR}/80160ea4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80160EA4_RESULT)
    if(NOT MUSASHI_SC02_80160EA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160ea4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161034.c
                ${MUSASHI_GENERATED_DIR}/80161034_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80161034_RESULT)
    if(NOT MUSASHI_SC02_80161034_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161034 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161c98.c
                ${MUSASHI_GENERATED_DIR}/80161c98_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80161C98_RESULT)
    if(NOT MUSASHI_SC02_80161C98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161c98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161cd0.c
                ${MUSASHI_GENERATED_DIR}/80161cd0_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80161CD0_RESULT)
    if(NOT MUSASHI_SC02_80161CD0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161cd0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161d20.c
                ${MUSASHI_GENERATED_DIR}/80161d20_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80161D20_RESULT)
    if(NOT MUSASHI_SC02_80161D20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161d20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161d88.c
                ${MUSASHI_GENERATED_DIR}/80161d88_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_80161D88_RESULT)
    if(NOT MUSASHI_SC02_80161D88_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161d88 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162330.c
                ${MUSASHI_GENERATED_DIR}/80162330_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80162330_RESULT)
    if(NOT MUSASHI_SC02_80162330_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162330 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162834.c
                ${MUSASHI_GENERATED_DIR}/80162834_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80162834_RESULT)
    if(NOT MUSASHI_SC02_80162834_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162834 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162870.c
                ${MUSASHI_GENERATED_DIR}/80162870_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_80162870_RESULT)
    if(NOT MUSASHI_SC02_80162870_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162870 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80163a58.c
                ${MUSASHI_GENERATED_DIR}/80163a58_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80163A58_RESULT)
    if(NOT MUSASHI_SC02_80163A58_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80163a58 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80164744.c
                ${MUSASHI_GENERATED_DIR}/80164744_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80164744_RESULT)
    if(NOT MUSASHI_SC02_80164744_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80164744 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80164ba0.c
                ${MUSASHI_GENERATED_DIR}/80164ba0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80164BA0_RESULT)
    if(NOT MUSASHI_SC02_80164BA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80164ba0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80164ea4.c
                ${MUSASHI_GENERATED_DIR}/80164ea4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80164EA4_RESULT)
    if(NOT MUSASHI_SC02_80164EA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80164ea4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165580.c
                ${MUSASHI_GENERATED_DIR}/80165580_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80165580_RESULT)
    if(NOT MUSASHI_SC02_80165580_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165580 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165658.c
                ${MUSASHI_GENERATED_DIR}/80165658_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80165658_RESULT)
    if(NOT MUSASHI_SC02_80165658_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165658 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165670.c
                ${MUSASHI_GENERATED_DIR}/80165670_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80165670_RESULT)
    if(NOT MUSASHI_SC02_80165670_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165670 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801656d0.c
                ${MUSASHI_GENERATED_DIR}/801656d0_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_801656D0_RESULT)
    if(NOT MUSASHI_SC02_801656D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801656d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801656e8.c
                ${MUSASHI_GENERATED_DIR}/801656e8_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_801656E8_RESULT)
    if(NOT MUSASHI_SC02_801656E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801656e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165700.c
                ${MUSASHI_GENERATED_DIR}/80165700_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80165700_RESULT)
    if(NOT MUSASHI_SC02_80165700_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165700 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165ac8.c
                ${MUSASHI_GENERATED_DIR}/80165ac8_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80165AC8_RESULT)
    if(NOT MUSASHI_SC02_80165AC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165ac8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165b28.c
                ${MUSASHI_GENERATED_DIR}/80165b28_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80165B28_RESULT)
    if(NOT MUSASHI_SC02_80165B28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165b28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80166018.c
                ${MUSASHI_GENERATED_DIR}/80166018_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80166018_RESULT)
    if(NOT MUSASHI_SC02_80166018_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80166018 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801663fc.c
                ${MUSASHI_GENERATED_DIR}/801663fc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801663FC_RESULT)
    if(NOT MUSASHI_SC02_801663FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801663fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80166618.c
                ${MUSASHI_GENERATED_DIR}/80166618_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80166618_RESULT)
    if(NOT MUSASHI_SC02_80166618_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80166618 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80166654.c
                ${MUSASHI_GENERATED_DIR}/80166654_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80166654_RESULT)
    if(NOT MUSASHI_SC02_80166654_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80166654 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801678b4.c
                ${MUSASHI_GENERATED_DIR}/801678b4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801678B4_RESULT)
    if(NOT MUSASHI_SC02_801678B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801678b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80167a9c.c
                ${MUSASHI_GENERATED_DIR}/80167a9c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80167A9C_RESULT)
    if(NOT MUSASHI_SC02_80167A9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80167a9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168744.c
                ${MUSASHI_GENERATED_DIR}/80168744_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80168744_RESULT)
    if(NOT MUSASHI_SC02_80168744_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168744 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801689d8.c
                ${MUSASHI_GENERATED_DIR}/801689d8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801689D8_RESULT)
    if(NOT MUSASHI_SC02_801689D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801689d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168aa8.c
                ${MUSASHI_GENERATED_DIR}/80168aa8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80168AA8_RESULT)
    if(NOT MUSASHI_SC02_80168AA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168aa8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168d58.c
                ${MUSASHI_GENERATED_DIR}/80168d58_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80168D58_RESULT)
    if(NOT MUSASHI_SC02_80168D58_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168d58 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016901c.c
                ${MUSASHI_GENERATED_DIR}/8016901c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016901C_RESULT)
    if(NOT MUSASHI_SC02_8016901C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016901c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801693cc.c
                ${MUSASHI_GENERATED_DIR}/801693cc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801693CC_RESULT)
    if(NOT MUSASHI_SC02_801693CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801693cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80169830.c
                ${MUSASHI_GENERATED_DIR}/80169830_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80169830_RESULT)
    if(NOT MUSASHI_SC02_80169830_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80169830 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80169b80.c
                ${MUSASHI_GENERATED_DIR}/80169b80_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80169B80_RESULT)
    if(NOT MUSASHI_SC02_80169B80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80169b80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80169f00.c
                ${MUSASHI_GENERATED_DIR}/80169f00_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80169F00_RESULT)
    if(NOT MUSASHI_SC02_80169F00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80169f00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016a020.c
                ${MUSASHI_GENERATED_DIR}/8016a020_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016A020_RESULT)
    if(NOT MUSASHI_SC02_8016A020_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016a020 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016a700.c
                ${MUSASHI_GENERATED_DIR}/8016a700_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016A700_RESULT)
    if(NOT MUSASHI_SC02_8016A700_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016a700 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016ab30.c
                ${MUSASHI_GENERATED_DIR}/8016ab30_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016AB30_RESULT)
    if(NOT MUSASHI_SC02_8016AB30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016ab30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016b4bc.c
                ${MUSASHI_GENERATED_DIR}/8016b4bc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016B4BC_RESULT)
    if(NOT MUSASHI_SC02_8016B4BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016b4bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016bba4.c
                ${MUSASHI_GENERATED_DIR}/8016bba4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016BBA4_RESULT)
    if(NOT MUSASHI_SC02_8016BBA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016bba4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016c14c.c
                ${MUSASHI_GENERATED_DIR}/8016c14c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016C14C_RESULT)
    if(NOT MUSASHI_SC02_8016C14C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016c14c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016cb84.c
                ${MUSASHI_GENERATED_DIR}/8016cb84_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016CB84_RESULT)
    if(NOT MUSASHI_SC02_8016CB84_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016cb84 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016d19c.c
                ${MUSASHI_GENERATED_DIR}/8016d19c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016D19C_RESULT)
    if(NOT MUSASHI_SC02_8016D19C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016d19c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016d428.c
                ${MUSASHI_GENERATED_DIR}/8016d428_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016D428_RESULT)
    if(NOT MUSASHI_SC02_8016D428_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016d428 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016da30.c
                ${MUSASHI_GENERATED_DIR}/8016da30_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8016DA30_RESULT)
    if(NOT MUSASHI_SC02_8016DA30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016da30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016dea4.c
                ${MUSASHI_GENERATED_DIR}/8016dea4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016DEA4_RESULT)
    if(NOT MUSASHI_SC02_8016DEA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016dea4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016df20.c
                ${MUSASHI_GENERATED_DIR}/8016df20_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016DF20_RESULT)
    if(NOT MUSASHI_SC02_8016DF20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016df20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e5b8.c
                ${MUSASHI_GENERATED_DIR}/8016e5b8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016E5B8_RESULT)
    if(NOT MUSASHI_SC02_8016E5B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e5b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016eac0.c
                ${MUSASHI_GENERATED_DIR}/8016eac0_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_8016EAC0_RESULT)
    if(NOT MUSASHI_SC02_8016EAC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016eac0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f6e0.c
                ${MUSASHI_GENERATED_DIR}/8016f6e0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016F6E0_RESULT)
    if(NOT MUSASHI_SC02_8016F6E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f6e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f798.c
                ${MUSASHI_GENERATED_DIR}/8016f798_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016F798_RESULT)
    if(NOT MUSASHI_SC02_8016F798_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f798 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f834.c
                ${MUSASHI_GENERATED_DIR}/8016f834_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016F834_RESULT)
    if(NOT MUSASHI_SC02_8016F834_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f834 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f8e4.c
                ${MUSASHI_GENERATED_DIR}/8016f8e4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016F8E4_RESULT)
    if(NOT MUSASHI_SC02_8016F8E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f8e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f9c4.c
                ${MUSASHI_GENERATED_DIR}/8016f9c4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016F9C4_RESULT)
    if(NOT MUSASHI_SC02_8016F9C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f9c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fa84.c
                ${MUSASHI_GENERATED_DIR}/8016fa84_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016FA84_RESULT)
    if(NOT MUSASHI_SC02_8016FA84_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fa84 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fb7c.c
                ${MUSASHI_GENERATED_DIR}/8016fb7c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016FB7C_RESULT)
    if(NOT MUSASHI_SC02_8016FB7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fb7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fc90.c
                ${MUSASHI_GENERATED_DIR}/8016fc90_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016FC90_RESULT)
    if(NOT MUSASHI_SC02_8016FC90_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fc90 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fdb4.c
                ${MUSASHI_GENERATED_DIR}/8016fdb4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016FDB4_RESULT)
    if(NOT MUSASHI_SC02_8016FDB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fdb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016ff30.c
                ${MUSASHI_GENERATED_DIR}/8016ff30_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016FF30_RESULT)
    if(NOT MUSASHI_SC02_8016FF30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016ff30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016ffdc.c
                ${MUSASHI_GENERATED_DIR}/8016ffdc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016FFDC_RESULT)
    if(NOT MUSASHI_SC02_8016FFDC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016ffdc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170150.c
                ${MUSASHI_GENERATED_DIR}/80170150_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170150_RESULT)
    if(NOT MUSASHI_SC02_80170150_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170150 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170240.c
                ${MUSASHI_GENERATED_DIR}/80170240_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170240_RESULT)
    if(NOT MUSASHI_SC02_80170240_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170240 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801702fc.c
                ${MUSASHI_GENERATED_DIR}/801702fc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801702FC_RESULT)
    if(NOT MUSASHI_SC02_801702FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801702fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801703e0.c
                ${MUSASHI_GENERATED_DIR}/801703e0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801703E0_RESULT)
    if(NOT MUSASHI_SC02_801703E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801703e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801704b0.c
                ${MUSASHI_GENERATED_DIR}/801704b0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801704B0_RESULT)
    if(NOT MUSASHI_SC02_801704B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801704b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170548.c
                ${MUSASHI_GENERATED_DIR}/80170548_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170548_RESULT)
    if(NOT MUSASHI_SC02_80170548_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170548 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801705f8.c
                ${MUSASHI_GENERATED_DIR}/801705f8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801705F8_RESULT)
    if(NOT MUSASHI_SC02_801705F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801705f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801706ac.c
                ${MUSASHI_GENERATED_DIR}/801706ac_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801706AC_RESULT)
    if(NOT MUSASHI_SC02_801706AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801706ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170748.c
                ${MUSASHI_GENERATED_DIR}/80170748_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170748_RESULT)
    if(NOT MUSASHI_SC02_80170748_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170748 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170810.c
                ${MUSASHI_GENERATED_DIR}/80170810_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170810_RESULT)
    if(NOT MUSASHI_SC02_80170810_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170810 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170ad8.c
                ${MUSASHI_GENERATED_DIR}/80170ad8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170AD8_RESULT)
    if(NOT MUSASHI_SC02_80170AD8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170ad8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170bd8.c
                ${MUSASHI_GENERATED_DIR}/80170bd8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170BD8_RESULT)
    if(NOT MUSASHI_SC02_80170BD8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170bd8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170c74.c
                ${MUSASHI_GENERATED_DIR}/80170c74_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170C74_RESULT)
    if(NOT MUSASHI_SC02_80170C74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170c74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170d68.c
                ${MUSASHI_GENERATED_DIR}/80170d68_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170D68_RESULT)
    if(NOT MUSASHI_SC02_80170D68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170d68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170e34.c
                ${MUSASHI_GENERATED_DIR}/80170e34_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170E34_RESULT)
    if(NOT MUSASHI_SC02_80170E34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170e34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170efc.c
                ${MUSASHI_GENERATED_DIR}/80170efc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170EFC_RESULT)
    if(NOT MUSASHI_SC02_80170EFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170efc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170fb0.c
                ${MUSASHI_GENERATED_DIR}/80170fb0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170FB0_RESULT)
    if(NOT MUSASHI_SC02_80170FB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170fb0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171064.c
                ${MUSASHI_GENERATED_DIR}/80171064_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80171064_RESULT)
    if(NOT MUSASHI_SC02_80171064_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171064 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171120.c
                ${MUSASHI_GENERATED_DIR}/80171120_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80171120_RESULT)
    if(NOT MUSASHI_SC02_80171120_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171120 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801711c0.c
                ${MUSASHI_GENERATED_DIR}/801711c0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801711C0_RESULT)
    if(NOT MUSASHI_SC02_801711C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801711c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171260.c
                ${MUSASHI_GENERATED_DIR}/80171260_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80171260_RESULT)
    if(NOT MUSASHI_SC02_80171260_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171260 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801714e4.c
                ${MUSASHI_GENERATED_DIR}/801714e4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801714E4_RESULT)
    if(NOT MUSASHI_SC02_801714E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801714e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801727d0.c
                ${MUSASHI_GENERATED_DIR}/801727d0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801727D0_RESULT)
    if(NOT MUSASHI_SC02_801727D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801727d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801728e4.c
                ${MUSASHI_GENERATED_DIR}/801728e4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801728E4_RESULT)
    if(NOT MUSASHI_SC02_801728E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801728e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801729f0.c
                ${MUSASHI_GENERATED_DIR}/801729f0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801729F0_RESULT)
    if(NOT MUSASHI_SC02_801729F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801729f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172b44.c
                ${MUSASHI_GENERATED_DIR}/80172b44_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80172B44_RESULT)
    if(NOT MUSASHI_SC02_80172B44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172b44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172ca0.c
                ${MUSASHI_GENERATED_DIR}/80172ca0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80172CA0_RESULT)
    if(NOT MUSASHI_SC02_80172CA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172ca0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172dac.c
                ${MUSASHI_GENERATED_DIR}/80172dac_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80172DAC_RESULT)
    if(NOT MUSASHI_SC02_80172DAC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172dac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173078.c
                ${MUSASHI_GENERATED_DIR}/80173078_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80173078_RESULT)
    if(NOT MUSASHI_SC02_80173078_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173078 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017319c.c
                ${MUSASHI_GENERATED_DIR}/8017319c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017319C_RESULT)
    if(NOT MUSASHI_SC02_8017319C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017319c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173220.c
                ${MUSASHI_GENERATED_DIR}/80173220_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_80173220_RESULT)
    if(NOT MUSASHI_SC02_80173220_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173220 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173544.c
                ${MUSASHI_GENERATED_DIR}/80173544_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80173544_RESULT)
    if(NOT MUSASHI_SC02_80173544_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173544 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801736fc.c
                ${MUSASHI_GENERATED_DIR}/801736fc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801736FC_RESULT)
    if(NOT MUSASHI_SC02_801736FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801736fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801737e8.c
                ${MUSASHI_GENERATED_DIR}/801737e8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801737E8_RESULT)
    if(NOT MUSASHI_SC02_801737E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801737e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017390c.c
                ${MUSASHI_GENERATED_DIR}/8017390c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017390C_RESULT)
    if(NOT MUSASHI_SC02_8017390C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017390c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173b4c.c
                ${MUSASHI_GENERATED_DIR}/80173b4c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80173B4C_RESULT)
    if(NOT MUSASHI_SC02_80173B4C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173b4c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801742a4.c
                ${MUSASHI_GENERATED_DIR}/801742a4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801742A4_RESULT)
    if(NOT MUSASHI_SC02_801742A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801742a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174384.c
                ${MUSASHI_GENERATED_DIR}/80174384_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80174384_RESULT)
    if(NOT MUSASHI_SC02_80174384_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174384 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174474.c
                ${MUSASHI_GENERATED_DIR}/80174474_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80174474_RESULT)
    if(NOT MUSASHI_SC02_80174474_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174474 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801747cc.c
                ${MUSASHI_GENERATED_DIR}/801747cc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801747CC_RESULT)
    if(NOT MUSASHI_SC02_801747CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801747cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174888.c
                ${MUSASHI_GENERATED_DIR}/80174888_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80174888_RESULT)
    if(NOT MUSASHI_SC02_80174888_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174888 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017496c.c
                ${MUSASHI_GENERATED_DIR}/8017496c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017496C_RESULT)
    if(NOT MUSASHI_SC02_8017496C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017496c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174bf4.c
                ${MUSASHI_GENERATED_DIR}/80174bf4_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80174BF4_RESULT)
    if(NOT MUSASHI_SC02_80174BF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174bf4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174f28.c
                ${MUSASHI_GENERATED_DIR}/80174f28_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80174F28_RESULT)
    if(NOT MUSASHI_SC02_80174F28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174f28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175184.c
                ${MUSASHI_GENERATED_DIR}/80175184_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80175184_RESULT)
    if(NOT MUSASHI_SC02_80175184_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175184 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017553c.c
                ${MUSASHI_GENERATED_DIR}/8017553c_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8017553C_RESULT)
    if(NOT MUSASHI_SC02_8017553C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017553c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175690.c
                ${MUSASHI_GENERATED_DIR}/80175690_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80175690_RESULT)
    if(NOT MUSASHI_SC02_80175690_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175690 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017be60.c
                ${MUSASHI_GENERATED_DIR}/8017be60_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017BE60_RESULT)
    if(NOT MUSASHI_SC02_8017BE60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017be60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128178.c
                ${MUSASHI_GENERATED_DIR}/80128178_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80128178_RESULT)
    if(NOT MUSASHI_SC02_80128178_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128178 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128198.c
                ${MUSASHI_GENERATED_DIR}/80128198_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80128198_RESULT)
    if(NOT MUSASHI_SC02_80128198_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128198 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801281b8.c
                ${MUSASHI_GENERATED_DIR}/801281b8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801281B8_RESULT)
    if(NOT MUSASHI_SC02_801281B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801281b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801281d8.c
                ${MUSASHI_GENERATED_DIR}/801281d8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801281D8_RESULT)
    if(NOT MUSASHI_SC02_801281D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801281d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801281f8.c
                ${MUSASHI_GENERATED_DIR}/801281f8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801281F8_RESULT)
    if(NOT MUSASHI_SC02_801281F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801281f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128228.c
                ${MUSASHI_GENERATED_DIR}/80128228_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80128228_RESULT)
    if(NOT MUSASHI_SC02_80128228_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128228 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128248.c
                ${MUSASHI_GENERATED_DIR}/80128248_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80128248_RESULT)
    if(NOT MUSASHI_SC02_80128248_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128248 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128268.c
                ${MUSASHI_GENERATED_DIR}/80128268_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80128268_RESULT)
    if(NOT MUSASHI_SC02_80128268_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128268 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801282cc.c
                ${MUSASHI_GENERATED_DIR}/801282cc_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801282CC_RESULT)
    if(NOT MUSASHI_SC02_801282CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801282cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801282ec.c
                ${MUSASHI_GENERATED_DIR}/801282ec_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801282EC_RESULT)
    if(NOT MUSASHI_SC02_801282EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801282ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128d60.c
                ${MUSASHI_GENERATED_DIR}/80128d60_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80128D60_RESULT)
    if(NOT MUSASHI_SC02_80128D60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128d60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80128ea8.c
                ${MUSASHI_GENERATED_DIR}/80128ea8_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80128EA8_RESULT)
    if(NOT MUSASHI_SC02_80128EA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80128ea8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801290dc.c
                ${MUSASHI_GENERATED_DIR}/801290dc_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_801290DC_RESULT)
    if(NOT MUSASHI_SC02_801290DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801290dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012913c.c
                ${MUSASHI_GENERATED_DIR}/8012913c_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_8012913C_RESULT)
    if(NOT MUSASHI_SC02_8012913C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012913c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801291c0.c
                ${MUSASHI_GENERATED_DIR}/801291c0_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_801291C0_RESULT)
    if(NOT MUSASHI_SC02_801291C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801291c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012927c.c
                ${MUSASHI_GENERATED_DIR}/8012927c_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8012927C_RESULT)
    if(NOT MUSASHI_SC02_8012927C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012927c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801292c8.c
                ${MUSASHI_GENERATED_DIR}/801292c8_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_801292C8_RESULT)
    if(NOT MUSASHI_SC02_801292C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801292c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012931c.c
                ${MUSASHI_GENERATED_DIR}/8012931c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8012931C_RESULT)
    if(NOT MUSASHI_SC02_8012931C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012931c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80129350.c
                ${MUSASHI_GENERATED_DIR}/80129350_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80129350_RESULT)
    if(NOT MUSASHI_SC02_80129350_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80129350 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80129374.c
                ${MUSASHI_GENERATED_DIR}/80129374_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80129374_RESULT)
    if(NOT MUSASHI_SC02_80129374_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80129374 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80129428.c
                ${MUSASHI_GENERATED_DIR}/80129428_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80129428_RESULT)
    if(NOT MUSASHI_SC02_80129428_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80129428 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012943c.c
                ${MUSASHI_GENERATED_DIR}/8012943c_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8012943C_RESULT)
    if(NOT MUSASHI_SC02_8012943C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012943c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80129ff4.c
                ${MUSASHI_GENERATED_DIR}/80129ff4_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80129FF4_RESULT)
    if(NOT MUSASHI_SC02_80129FF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80129ff4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a0e0.c
                ${MUSASHI_GENERATED_DIR}/8012a0e0_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8012A0E0_RESULT)
    if(NOT MUSASHI_SC02_8012A0E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a0e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a100.c
                ${MUSASHI_GENERATED_DIR}/8012a100_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8012A100_RESULT)
    if(NOT MUSASHI_SC02_8012A100_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a100 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a110.c
                ${MUSASHI_GENERATED_DIR}/8012a110_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_8012A110_RESULT)
    if(NOT MUSASHI_SC02_8012A110_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a110 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a2f4.c
                ${MUSASHI_GENERATED_DIR}/8012a2f4_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8012A2F4_RESULT)
    if(NOT MUSASHI_SC02_8012A2F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a2f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a304.c
                ${MUSASHI_GENERATED_DIR}/8012a304_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8012A304_RESULT)
    if(NOT MUSASHI_SC02_8012A304_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a304 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a418.c
                ${MUSASHI_GENERATED_DIR}/8012a418_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8012A418_RESULT)
    if(NOT MUSASHI_SC02_8012A418_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a418 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a464.c
                ${MUSASHI_GENERATED_DIR}/8012a464_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8012A464_RESULT)
    if(NOT MUSASHI_SC02_8012A464_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a464 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a4bc.c
                ${MUSASHI_GENERATED_DIR}/8012a4bc_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_8012A4BC_RESULT)
    if(NOT MUSASHI_SC02_8012A4BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a4bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a568.c
                ${MUSASHI_GENERATED_DIR}/8012a568_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8012A568_RESULT)
    if(NOT MUSASHI_SC02_8012A568_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a568 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a598.c
                ${MUSASHI_GENERATED_DIR}/8012a598_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8012A598_RESULT)
    if(NOT MUSASHI_SC02_8012A598_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a598 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a5f8.c
                ${MUSASHI_GENERATED_DIR}/8012a5f8_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8012A5F8_RESULT)
    if(NOT MUSASHI_SC02_8012A5F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a5f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a62c.c
                ${MUSASHI_GENERATED_DIR}/8012a62c_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8012A62C_RESULT)
    if(NOT MUSASHI_SC02_8012A62C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a62c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a68c.c
                ${MUSASHI_GENERATED_DIR}/8012a68c_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8012A68C_RESULT)
    if(NOT MUSASHI_SC02_8012A68C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a68c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a6d0.c
                ${MUSASHI_GENERATED_DIR}/8012a6d0_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_8012A6D0_RESULT)
    if(NOT MUSASHI_SC02_8012A6D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a6d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a758.c
                ${MUSASHI_GENERATED_DIR}/8012a758_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8012A758_RESULT)
    if(NOT MUSASHI_SC02_8012A758_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a758 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a79c.c
                ${MUSASHI_GENERATED_DIR}/8012a79c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8012A79C_RESULT)
    if(NOT MUSASHI_SC02_8012A79C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a79c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a7d4.c
                ${MUSASHI_GENERATED_DIR}/8012a7d4_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8012A7D4_RESULT)
    if(NOT MUSASHI_SC02_8012A7D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a7d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a860.c
                ${MUSASHI_GENERATED_DIR}/8012a860_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8012A860_RESULT)
    if(NOT MUSASHI_SC02_8012A860_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a860 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a8b0.c
                ${MUSASHI_GENERATED_DIR}/8012a8b0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8012A8B0_RESULT)
    if(NOT MUSASHI_SC02_8012A8B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a8b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a8e8.c
                ${MUSASHI_GENERATED_DIR}/8012a8e8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8012A8E8_RESULT)
    if(NOT MUSASHI_SC02_8012A8E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a8e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012a908.c
                ${MUSASHI_GENERATED_DIR}/8012a908_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_8012A908_RESULT)
    if(NOT MUSASHI_SC02_8012A908_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012a908 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ad3c.c
                ${MUSASHI_GENERATED_DIR}/8012ad3c_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_8012AD3C_RESULT)
    if(NOT MUSASHI_SC02_8012AD3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ad3c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ad64.c
                ${MUSASHI_GENERATED_DIR}/8012ad64_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_8012AD64_RESULT)
    if(NOT MUSASHI_SC02_8012AD64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ad64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ad6c.c
                ${MUSASHI_GENERATED_DIR}/8012ad6c_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8012AD6C_RESULT)
    if(NOT MUSASHI_SC02_8012AD6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ad6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ad80.c
                ${MUSASHI_GENERATED_DIR}/8012ad80_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_8012AD80_RESULT)
    if(NOT MUSASHI_SC02_8012AD80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ad80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ade4.c
                ${MUSASHI_GENERATED_DIR}/8012ade4_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_8012ADE4_RESULT)
    if(NOT MUSASHI_SC02_8012ADE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ade4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b178.c
                ${MUSASHI_GENERATED_DIR}/8012b178_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8012B178_RESULT)
    if(NOT MUSASHI_SC02_8012B178_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b178 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b1b4.c
                ${MUSASHI_GENERATED_DIR}/8012b1b4_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8012B1B4_RESULT)
    if(NOT MUSASHI_SC02_8012B1B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b1b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b200.c
                ${MUSASHI_GENERATED_DIR}/8012b200_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_8012B200_RESULT)
    if(NOT MUSASHI_SC02_8012B200_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b200 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b21c.c
                ${MUSASHI_GENERATED_DIR}/8012b21c_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8012B21C_RESULT)
    if(NOT MUSASHI_SC02_8012B21C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b21c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b23c.c
                ${MUSASHI_GENERATED_DIR}/8012b23c_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8012B23C_RESULT)
    if(NOT MUSASHI_SC02_8012B23C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b23c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b370.c
                ${MUSASHI_GENERATED_DIR}/8012b370_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_8012B370_RESULT)
    if(NOT MUSASHI_SC02_8012B370_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b370 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b414.c
                ${MUSASHI_GENERATED_DIR}/8012b414_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_8012B414_RESULT)
    if(NOT MUSASHI_SC02_8012B414_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b414 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b6d4.c
                ${MUSASHI_GENERATED_DIR}/8012b6d4_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8012B6D4_RESULT)
    if(NOT MUSASHI_SC02_8012B6D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b6d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b70c.c
                ${MUSASHI_GENERATED_DIR}/8012b70c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8012B70C_RESULT)
    if(NOT MUSASHI_SC02_8012B70C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b70c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b744.c
                ${MUSASHI_GENERATED_DIR}/8012b744_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8012B744_RESULT)
    if(NOT MUSASHI_SC02_8012B744_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b744 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b864.c
                ${MUSASHI_GENERATED_DIR}/8012b864_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8012B864_RESULT)
    if(NOT MUSASHI_SC02_8012B864_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b864 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012b8a4.c
                ${MUSASHI_GENERATED_DIR}/8012b8a4_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8012B8A4_RESULT)
    if(NOT MUSASHI_SC02_8012B8A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012b8a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012bc60.c
                ${MUSASHI_GENERATED_DIR}/8012bc60_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8012BC60_RESULT)
    if(NOT MUSASHI_SC02_8012BC60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012bc60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012bd14.c
                ${MUSASHI_GENERATED_DIR}/8012bd14_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8012BD14_RESULT)
    if(NOT MUSASHI_SC02_8012BD14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012bd14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012bd3c.c
                ${MUSASHI_GENERATED_DIR}/8012bd3c_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_8012BD3C_RESULT)
    if(NOT MUSASHI_SC02_8012BD3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012bd3c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012be54.c
                ${MUSASHI_GENERATED_DIR}/8012be54_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8012BE54_RESULT)
    if(NOT MUSASHI_SC02_8012BE54_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012be54 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012be98.c
                ${MUSASHI_GENERATED_DIR}/8012be98_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8012BE98_RESULT)
    if(NOT MUSASHI_SC02_8012BE98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012be98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012bf4c.c
                ${MUSASHI_GENERATED_DIR}/8012bf4c_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_8012BF4C_RESULT)
    if(NOT MUSASHI_SC02_8012BF4C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012bf4c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012bf54.c
                ${MUSASHI_GENERATED_DIR}/8012bf54_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8012BF54_RESULT)
    if(NOT MUSASHI_SC02_8012BF54_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012bf54 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012bf68.c
                ${MUSASHI_GENERATED_DIR}/8012bf68_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8012BF68_RESULT)
    if(NOT MUSASHI_SC02_8012BF68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012bf68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012bf7c.c
                ${MUSASHI_GENERATED_DIR}/8012bf7c_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8012BF7C_RESULT)
    if(NOT MUSASHI_SC02_8012BF7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012bf7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012bfa8.c
                ${MUSASHI_GENERATED_DIR}/8012bfa8_sc02_0031_words.inc --expected-words 39
        RESULT_VARIABLE MUSASHI_SC02_8012BFA8_RESULT)
    if(NOT MUSASHI_SC02_8012BFA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012bfa8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c044.c
                ${MUSASHI_GENERATED_DIR}/8012c044_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8012C044_RESULT)
    if(NOT MUSASHI_SC02_8012C044_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c044 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c098.c
                ${MUSASHI_GENERATED_DIR}/8012c098_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8012C098_RESULT)
    if(NOT MUSASHI_SC02_8012C098_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c098 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c31c.c
                ${MUSASHI_GENERATED_DIR}/8012c31c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8012C31C_RESULT)
    if(NOT MUSASHI_SC02_8012C31C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c31c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012c724.c
                ${MUSASHI_GENERATED_DIR}/8012c724_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8012C724_RESULT)
    if(NOT MUSASHI_SC02_8012C724_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012c724 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012cba4.c
                ${MUSASHI_GENERATED_DIR}/8012cba4_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8012CBA4_RESULT)
    if(NOT MUSASHI_SC02_8012CBA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012cba4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012cbcc.c
                ${MUSASHI_GENERATED_DIR}/8012cbcc_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8012CBCC_RESULT)
    if(NOT MUSASHI_SC02_8012CBCC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012cbcc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012cbf4.c
                ${MUSASHI_GENERATED_DIR}/8012cbf4_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8012CBF4_RESULT)
    if(NOT MUSASHI_SC02_8012CBF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012cbf4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012cc1c.c
                ${MUSASHI_GENERATED_DIR}/8012cc1c_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8012CC1C_RESULT)
    if(NOT MUSASHI_SC02_8012CC1C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012cc1c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012cc40.c
                ${MUSASHI_GENERATED_DIR}/8012cc40_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8012CC40_RESULT)
    if(NOT MUSASHI_SC02_8012CC40_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012cc40 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012cc64.c
                ${MUSASHI_GENERATED_DIR}/8012cc64_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8012CC64_RESULT)
    if(NOT MUSASHI_SC02_8012CC64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012cc64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012d38c.c
                ${MUSASHI_GENERATED_DIR}/8012d38c_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8012D38C_RESULT)
    if(NOT MUSASHI_SC02_8012D38C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012d38c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012d3b4.c
                ${MUSASHI_GENERATED_DIR}/8012d3b4_sc02_0031_words.inc --expected-words 64
        RESULT_VARIABLE MUSASHI_SC02_8012D3B4_RESULT)
    if(NOT MUSASHI_SC02_8012D3B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012d3b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012d4b4.c
                ${MUSASHI_GENERATED_DIR}/8012d4b4_sc02_0031_words.inc --expected-words 74
        RESULT_VARIABLE MUSASHI_SC02_8012D4B4_RESULT)
    if(NOT MUSASHI_SC02_8012D4B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012d4b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012d5e4.c
                ${MUSASHI_GENERATED_DIR}/8012d5e4_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8012D5E4_RESULT)
    if(NOT MUSASHI_SC02_8012D5E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012d5e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012d624.c
                ${MUSASHI_GENERATED_DIR}/8012d624_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8012D624_RESULT)
    if(NOT MUSASHI_SC02_8012D624_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012d624 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012dfd4.c
                ${MUSASHI_GENERATED_DIR}/8012dfd4_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8012DFD4_RESULT)
    if(NOT MUSASHI_SC02_8012DFD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012dfd4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e27c.c
                ${MUSASHI_GENERATED_DIR}/8012e27c_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_8012E27C_RESULT)
    if(NOT MUSASHI_SC02_8012E27C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e27c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e284.c
                ${MUSASHI_GENERATED_DIR}/8012e284_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_8012E284_RESULT)
    if(NOT MUSASHI_SC02_8012E284_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e284 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e28c.c
                ${MUSASHI_GENERATED_DIR}/8012e28c_sc02_0031_words.inc --expected-words 40
        RESULT_VARIABLE MUSASHI_SC02_8012E28C_RESULT)
    if(NOT MUSASHI_SC02_8012E28C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e28c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e32c.c
                ${MUSASHI_GENERATED_DIR}/8012e32c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8012E32C_RESULT)
    if(NOT MUSASHI_SC02_8012E32C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e32c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e504.c
                ${MUSASHI_GENERATED_DIR}/8012e504_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8012E504_RESULT)
    if(NOT MUSASHI_SC02_8012E504_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e504 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e544.c
                ${MUSASHI_GENERATED_DIR}/8012e544_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8012E544_RESULT)
    if(NOT MUSASHI_SC02_8012E544_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e544 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e57c.c
                ${MUSASHI_GENERATED_DIR}/8012e57c_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8012E57C_RESULT)
    if(NOT MUSASHI_SC02_8012E57C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e57c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e778.c
                ${MUSASHI_GENERATED_DIR}/8012e778_sc02_0031_words.inc --expected-words 69
        RESULT_VARIABLE MUSASHI_SC02_8012E778_RESULT)
    if(NOT MUSASHI_SC02_8012E778_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e778 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e88c.c
                ${MUSASHI_GENERATED_DIR}/8012e88c_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_8012E88C_RESULT)
    if(NOT MUSASHI_SC02_8012E88C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e88c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e8a8.c
                ${MUSASHI_GENERATED_DIR}/8012e8a8_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_8012E8A8_RESULT)
    if(NOT MUSASHI_SC02_8012E8A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e8a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012e8c4.c
                ${MUSASHI_GENERATED_DIR}/8012e8c4_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_8012E8C4_RESULT)
    if(NOT MUSASHI_SC02_8012E8C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012e8c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ec04.c
                ${MUSASHI_GENERATED_DIR}/8012ec04_sc02_0031_words.inc --expected-words 178
        RESULT_VARIABLE MUSASHI_SC02_8012EC04_RESULT)
    if(NOT MUSASHI_SC02_8012EC04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ec04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012eecc.c
                ${MUSASHI_GENERATED_DIR}/8012eecc_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_8012EECC_RESULT)
    if(NOT MUSASHI_SC02_8012EECC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012eecc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ef34.c
                ${MUSASHI_GENERATED_DIR}/8012ef34_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8012EF34_RESULT)
    if(NOT MUSASHI_SC02_8012EF34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ef34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ef70.c
                ${MUSASHI_GENERATED_DIR}/8012ef70_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8012EF70_RESULT)
    if(NOT MUSASHI_SC02_8012EF70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ef70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012efb8.c
                ${MUSASHI_GENERATED_DIR}/8012efb8_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_8012EFB8_RESULT)
    if(NOT MUSASHI_SC02_8012EFB8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012efb8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f038.c
                ${MUSASHI_GENERATED_DIR}/8012f038_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_8012F038_RESULT)
    if(NOT MUSASHI_SC02_8012F038_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f038 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f0bc.c
                ${MUSASHI_GENERATED_DIR}/8012f0bc_sc02_0031_words.inc --expected-words 36
        RESULT_VARIABLE MUSASHI_SC02_8012F0BC_RESULT)
    if(NOT MUSASHI_SC02_8012F0BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f0bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f1a4.c
                ${MUSASHI_GENERATED_DIR}/8012f1a4_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_8012F1A4_RESULT)
    if(NOT MUSASHI_SC02_8012F1A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f1a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f214.c
                ${MUSASHI_GENERATED_DIR}/8012f214_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8012F214_RESULT)
    if(NOT MUSASHI_SC02_8012F214_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f214 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f2e8.c
                ${MUSASHI_GENERATED_DIR}/8012f2e8_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_8012F2E8_RESULT)
    if(NOT MUSASHI_SC02_8012F2E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f2e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f374.c
                ${MUSASHI_GENERATED_DIR}/8012f374_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_8012F374_RESULT)
    if(NOT MUSASHI_SC02_8012F374_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f374 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f5f4.c
                ${MUSASHI_GENERATED_DIR}/8012f5f4_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_8012F5F4_RESULT)
    if(NOT MUSASHI_SC02_8012F5F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f5f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f75c.c
                ${MUSASHI_GENERATED_DIR}/8012f75c_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8012F75C_RESULT)
    if(NOT MUSASHI_SC02_8012F75C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f75c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f7b4.c
                ${MUSASHI_GENERATED_DIR}/8012f7b4_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_8012F7B4_RESULT)
    if(NOT MUSASHI_SC02_8012F7B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f7b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f87c.c
                ${MUSASHI_GENERATED_DIR}/8012f87c_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8012F87C_RESULT)
    if(NOT MUSASHI_SC02_8012F87C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f87c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012f91c.c
                ${MUSASHI_GENERATED_DIR}/8012f91c_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8012F91C_RESULT)
    if(NOT MUSASHI_SC02_8012F91C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012f91c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012fb54.c
                ${MUSASHI_GENERATED_DIR}/8012fb54_sc02_0031_words.inc --expected-words 55
        RESULT_VARIABLE MUSASHI_SC02_8012FB54_RESULT)
    if(NOT MUSASHI_SC02_8012FB54_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012fb54 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012fc30.c
                ${MUSASHI_GENERATED_DIR}/8012fc30_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_8012FC30_RESULT)
    if(NOT MUSASHI_SC02_8012FC30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012fc30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012fca4.c
                ${MUSASHI_GENERATED_DIR}/8012fca4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8012FCA4_RESULT)
    if(NOT MUSASHI_SC02_8012FCA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012fca4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012fda8.c
                ${MUSASHI_GENERATED_DIR}/8012fda8_sc02_0031_words.inc --expected-words 50
        RESULT_VARIABLE MUSASHI_SC02_8012FDA8_RESULT)
    if(NOT MUSASHI_SC02_8012FDA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012fda8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012fe70.c
                ${MUSASHI_GENERATED_DIR}/8012fe70_sc02_0031_words.inc --expected-words 36
        RESULT_VARIABLE MUSASHI_SC02_8012FE70_RESULT)
    if(NOT MUSASHI_SC02_8012FE70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012fe70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ff00.c
                ${MUSASHI_GENERATED_DIR}/8012ff00_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8012FF00_RESULT)
    if(NOT MUSASHI_SC02_8012FF00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ff00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ff4c.c
                ${MUSASHI_GENERATED_DIR}/8012ff4c_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8012FF4C_RESULT)
    if(NOT MUSASHI_SC02_8012FF4C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ff4c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8012ff98.c
                ${MUSASHI_GENERATED_DIR}/8012ff98_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_8012FF98_RESULT)
    if(NOT MUSASHI_SC02_8012FF98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8012ff98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130278.c
                ${MUSASHI_GENERATED_DIR}/80130278_sc02_0031_words.inc --expected-words 39
        RESULT_VARIABLE MUSASHI_SC02_80130278_RESULT)
    if(NOT MUSASHI_SC02_80130278_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130278 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130314.c
                ${MUSASHI_GENERATED_DIR}/80130314_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80130314_RESULT)
    if(NOT MUSASHI_SC02_80130314_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130314 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130360.c
                ${MUSASHI_GENERATED_DIR}/80130360_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80130360_RESULT)
    if(NOT MUSASHI_SC02_80130360_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130360 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801303a0.c
                ${MUSASHI_GENERATED_DIR}/801303a0_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_801303A0_RESULT)
    if(NOT MUSASHI_SC02_801303A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801303a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801303ec.c
                ${MUSASHI_GENERATED_DIR}/801303ec_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_801303EC_RESULT)
    if(NOT MUSASHI_SC02_801303EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801303ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130514.c
                ${MUSASHI_GENERATED_DIR}/80130514_sc02_0031_words.inc --expected-words 46
        RESULT_VARIABLE MUSASHI_SC02_80130514_RESULT)
    if(NOT MUSASHI_SC02_80130514_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130514 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801305cc.c
                ${MUSASHI_GENERATED_DIR}/801305cc_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_801305CC_RESULT)
    if(NOT MUSASHI_SC02_801305CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801305cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130650.c
                ${MUSASHI_GENERATED_DIR}/80130650_sc02_0031_words.inc --expected-words 60
        RESULT_VARIABLE MUSASHI_SC02_80130650_RESULT)
    if(NOT MUSASHI_SC02_80130650_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130650 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130740.c
                ${MUSASHI_GENERATED_DIR}/80130740_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80130740_RESULT)
    if(NOT MUSASHI_SC02_80130740_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130740 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801307b0.c
                ${MUSASHI_GENERATED_DIR}/801307b0_sc02_0031_words.inc --expected-words 42
        RESULT_VARIABLE MUSASHI_SC02_801307B0_RESULT)
    if(NOT MUSASHI_SC02_801307B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801307b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130858.c
                ${MUSASHI_GENERATED_DIR}/80130858_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80130858_RESULT)
    if(NOT MUSASHI_SC02_80130858_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130858 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130898.c
                ${MUSASHI_GENERATED_DIR}/80130898_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80130898_RESULT)
    if(NOT MUSASHI_SC02_80130898_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130898 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801308dc.c
                ${MUSASHI_GENERATED_DIR}/801308dc_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_801308DC_RESULT)
    if(NOT MUSASHI_SC02_801308DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801308dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130974.c
                ${MUSASHI_GENERATED_DIR}/80130974_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_80130974_RESULT)
    if(NOT MUSASHI_SC02_80130974_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130974 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130a18.c
                ${MUSASHI_GENERATED_DIR}/80130a18_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_80130A18_RESULT)
    if(NOT MUSASHI_SC02_80130A18_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130a18 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80130af0.c
                ${MUSASHI_GENERATED_DIR}/80130af0_sc02_0031_words.inc --expected-words 70
        RESULT_VARIABLE MUSASHI_SC02_80130AF0_RESULT)
    if(NOT MUSASHI_SC02_80130AF0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80130af0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801319e0.c
                ${MUSASHI_GENERATED_DIR}/801319e0_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_801319E0_RESULT)
    if(NOT MUSASHI_SC02_801319E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801319e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80131c78.c
                ${MUSASHI_GENERATED_DIR}/80131c78_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80131C78_RESULT)
    if(NOT MUSASHI_SC02_80131C78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80131c78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80131d68.c
                ${MUSASHI_GENERATED_DIR}/80131d68_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_80131D68_RESULT)
    if(NOT MUSASHI_SC02_80131D68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80131d68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80131e38.c
                ${MUSASHI_GENERATED_DIR}/80131e38_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80131E38_RESULT)
    if(NOT MUSASHI_SC02_80131E38_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80131e38 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80131e7c.c
                ${MUSASHI_GENERATED_DIR}/80131e7c_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_80131E7C_RESULT)
    if(NOT MUSASHI_SC02_80131E7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80131e7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80132784.c
                ${MUSASHI_GENERATED_DIR}/80132784_sc02_0031_words.inc --expected-words 400
        RESULT_VARIABLE MUSASHI_SC02_80132784_RESULT)
    if(NOT MUSASHI_SC02_80132784_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80132784 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80132dc4.c
                ${MUSASHI_GENERATED_DIR}/80132dc4_sc02_0031_words.inc --expected-words 42
        RESULT_VARIABLE MUSASHI_SC02_80132DC4_RESULT)
    if(NOT MUSASHI_SC02_80132DC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80132dc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80132e6c.c
                ${MUSASHI_GENERATED_DIR}/80132e6c_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80132E6C_RESULT)
    if(NOT MUSASHI_SC02_80132E6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80132e6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80132ec4.c
                ${MUSASHI_GENERATED_DIR}/80132ec4_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80132EC4_RESULT)
    if(NOT MUSASHI_SC02_80132EC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80132ec4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80132ef4.c
                ${MUSASHI_GENERATED_DIR}/80132ef4_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80132EF4_RESULT)
    if(NOT MUSASHI_SC02_80132EF4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80132ef4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80133060.c
                ${MUSASHI_GENERATED_DIR}/80133060_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_80133060_RESULT)
    if(NOT MUSASHI_SC02_80133060_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80133060 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801330e0.c
                ${MUSASHI_GENERATED_DIR}/801330e0_sc02_0031_words.inc --expected-words 110
        RESULT_VARIABLE MUSASHI_SC02_801330E0_RESULT)
    if(NOT MUSASHI_SC02_801330E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801330e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80134310.c
                ${MUSASHI_GENERATED_DIR}/80134310_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80134310_RESULT)
    if(NOT MUSASHI_SC02_80134310_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80134310 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013435c.c
                ${MUSASHI_GENERATED_DIR}/8013435c_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_8013435C_RESULT)
    if(NOT MUSASHI_SC02_8013435C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013435c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80134a28.c
                ${MUSASHI_GENERATED_DIR}/80134a28_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80134A28_RESULT)
    if(NOT MUSASHI_SC02_80134A28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80134a28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80134fb8.c
                ${MUSASHI_GENERATED_DIR}/80134fb8_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80134FB8_RESULT)
    if(NOT MUSASHI_SC02_80134FB8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80134fb8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80136c1c.c
                ${MUSASHI_GENERATED_DIR}/80136c1c_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80136C1C_RESULT)
    if(NOT MUSASHI_SC02_80136C1C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80136c1c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80136c3c.c
                ${MUSASHI_GENERATED_DIR}/80136c3c_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80136C3C_RESULT)
    if(NOT MUSASHI_SC02_80136C3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80136c3c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80136d08.c
                ${MUSASHI_GENERATED_DIR}/80136d08_sc02_0031_words.inc --expected-words 61
        RESULT_VARIABLE MUSASHI_SC02_80136D08_RESULT)
    if(NOT MUSASHI_SC02_80136D08_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80136d08 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80136dfc.c
                ${MUSASHI_GENERATED_DIR}/80136dfc_sc02_0031_words.inc --expected-words 50
        RESULT_VARIABLE MUSASHI_SC02_80136DFC_RESULT)
    if(NOT MUSASHI_SC02_80136DFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80136dfc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80136ecc.c
                ${MUSASHI_GENERATED_DIR}/80136ecc_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80136ECC_RESULT)
    if(NOT MUSASHI_SC02_80136ECC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80136ecc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801375ec.c
                ${MUSASHI_GENERATED_DIR}/801375ec_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_801375EC_RESULT)
    if(NOT MUSASHI_SC02_801375EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801375ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80137614.c
                ${MUSASHI_GENERATED_DIR}/80137614_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_80137614_RESULT)
    if(NOT MUSASHI_SC02_80137614_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80137614 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013767c.c
                ${MUSASHI_GENERATED_DIR}/8013767c_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8013767C_RESULT)
    if(NOT MUSASHI_SC02_8013767C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013767c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801376c8.c
                ${MUSASHI_GENERATED_DIR}/801376c8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801376C8_RESULT)
    if(NOT MUSASHI_SC02_801376C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801376c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80137840.c
                ${MUSASHI_GENERATED_DIR}/80137840_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_80137840_RESULT)
    if(NOT MUSASHI_SC02_80137840_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80137840 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801379d8.c
                ${MUSASHI_GENERATED_DIR}/801379d8_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801379D8_RESULT)
    if(NOT MUSASHI_SC02_801379D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801379d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801379ec.c
                ${MUSASHI_GENERATED_DIR}/801379ec_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_801379EC_RESULT)
    if(NOT MUSASHI_SC02_801379EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801379ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80138948.c
                ${MUSASHI_GENERATED_DIR}/80138948_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80138948_RESULT)
    if(NOT MUSASHI_SC02_80138948_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80138948 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80138b88.c
                ${MUSASHI_GENERATED_DIR}/80138b88_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80138B88_RESULT)
    if(NOT MUSASHI_SC02_80138B88_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80138b88 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80138c30.c
                ${MUSASHI_GENERATED_DIR}/80138c30_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80138C30_RESULT)
    if(NOT MUSASHI_SC02_80138C30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80138c30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80138d58.c
                ${MUSASHI_GENERATED_DIR}/80138d58_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80138D58_RESULT)
    if(NOT MUSASHI_SC02_80138D58_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80138d58 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80138db8.c
                ${MUSASHI_GENERATED_DIR}/80138db8_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80138DB8_RESULT)
    if(NOT MUSASHI_SC02_80138DB8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80138db8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801391f0.c
                ${MUSASHI_GENERATED_DIR}/801391f0_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801391F0_RESULT)
    if(NOT MUSASHI_SC02_801391F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801391f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139220.c
                ${MUSASHI_GENERATED_DIR}/80139220_sc02_0031_words.inc --expected-words 42
        RESULT_VARIABLE MUSASHI_SC02_80139220_RESULT)
    if(NOT MUSASHI_SC02_80139220_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139220 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801392c8.c
                ${MUSASHI_GENERATED_DIR}/801392c8_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_801392C8_RESULT)
    if(NOT MUSASHI_SC02_801392C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801392c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801395d4.c
                ${MUSASHI_GENERATED_DIR}/801395d4_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_801395D4_RESULT)
    if(NOT MUSASHI_SC02_801395D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801395d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139634.c
                ${MUSASHI_GENERATED_DIR}/80139634_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80139634_RESULT)
    if(NOT MUSASHI_SC02_80139634_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139634 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139788.c
                ${MUSASHI_GENERATED_DIR}/80139788_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80139788_RESULT)
    if(NOT MUSASHI_SC02_80139788_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139788 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139914.c
                ${MUSASHI_GENERATED_DIR}/80139914_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80139914_RESULT)
    if(NOT MUSASHI_SC02_80139914_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139914 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139954.c
                ${MUSASHI_GENERATED_DIR}/80139954_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80139954_RESULT)
    if(NOT MUSASHI_SC02_80139954_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139954 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801399a8.c
                ${MUSASHI_GENERATED_DIR}/801399a8_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_801399A8_RESULT)
    if(NOT MUSASHI_SC02_801399A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801399a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801399f0.c
                ${MUSASHI_GENERATED_DIR}/801399f0_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_801399F0_RESULT)
    if(NOT MUSASHI_SC02_801399F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801399f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139a34.c
                ${MUSASHI_GENERATED_DIR}/80139a34_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80139A34_RESULT)
    if(NOT MUSASHI_SC02_80139A34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139a34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139a44.c
                ${MUSASHI_GENERATED_DIR}/80139a44_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80139A44_RESULT)
    if(NOT MUSASHI_SC02_80139A44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139a44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139a68.c
                ${MUSASHI_GENERATED_DIR}/80139a68_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80139A68_RESULT)
    if(NOT MUSASHI_SC02_80139A68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139a68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139b18.c
                ${MUSASHI_GENERATED_DIR}/80139b18_sc02_0031_words.inc --expected-words 50
        RESULT_VARIABLE MUSASHI_SC02_80139B18_RESULT)
    if(NOT MUSASHI_SC02_80139B18_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139b18 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139c7c.c
                ${MUSASHI_GENERATED_DIR}/80139c7c_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_80139C7C_RESULT)
    if(NOT MUSASHI_SC02_80139C7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139c7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139dc8.c
                ${MUSASHI_GENERATED_DIR}/80139dc8_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80139DC8_RESULT)
    if(NOT MUSASHI_SC02_80139DC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139dc8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139f0c.c
                ${MUSASHI_GENERATED_DIR}/80139f0c_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_80139F0C_RESULT)
    if(NOT MUSASHI_SC02_80139F0C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139f0c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139fbc.c
                ${MUSASHI_GENERATED_DIR}/80139fbc_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80139FBC_RESULT)
    if(NOT MUSASHI_SC02_80139FBC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139fbc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80139fe8.c
                ${MUSASHI_GENERATED_DIR}/80139fe8_sc02_0031_words.inc --expected-words 47
        RESULT_VARIABLE MUSASHI_SC02_80139FE8_RESULT)
    if(NOT MUSASHI_SC02_80139FE8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80139fe8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013a0a4.c
                ${MUSASHI_GENERATED_DIR}/8013a0a4_sc02_0031_words.inc --expected-words 48
        RESULT_VARIABLE MUSASHI_SC02_8013A0A4_RESULT)
    if(NOT MUSASHI_SC02_8013A0A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013a0a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013a164.c
                ${MUSASHI_GENERATED_DIR}/8013a164_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_8013A164_RESULT)
    if(NOT MUSASHI_SC02_8013A164_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013a164 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013a1e8.c
                ${MUSASHI_GENERATED_DIR}/8013a1e8_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_8013A1E8_RESULT)
    if(NOT MUSASHI_SC02_8013A1E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013a1e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013a250.c
                ${MUSASHI_GENERATED_DIR}/8013a250_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8013A250_RESULT)
    if(NOT MUSASHI_SC02_8013A250_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013a250 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013a448.c
                ${MUSASHI_GENERATED_DIR}/8013a448_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_8013A448_RESULT)
    if(NOT MUSASHI_SC02_8013A448_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013a448 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013a4c4.c
                ${MUSASHI_GENERATED_DIR}/8013a4c4_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8013A4C4_RESULT)
    if(NOT MUSASHI_SC02_8013A4C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013a4c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013a8b0.c
                ${MUSASHI_GENERATED_DIR}/8013a8b0_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_8013A8B0_RESULT)
    if(NOT MUSASHI_SC02_8013A8B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013a8b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013a8bc.c
                ${MUSASHI_GENERATED_DIR}/8013a8bc_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8013A8BC_RESULT)
    if(NOT MUSASHI_SC02_8013A8BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013a8bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013a9b4.c
                ${MUSASHI_GENERATED_DIR}/8013a9b4_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8013A9B4_RESULT)
    if(NOT MUSASHI_SC02_8013A9B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013a9b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013aa24.c
                ${MUSASHI_GENERATED_DIR}/8013aa24_sc02_0031_words.inc --expected-words 76
        RESULT_VARIABLE MUSASHI_SC02_8013AA24_RESULT)
    if(NOT MUSASHI_SC02_8013AA24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013aa24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013ab54.c
                ${MUSASHI_GENERATED_DIR}/8013ab54_sc02_0031_words.inc --expected-words 121
        RESULT_VARIABLE MUSASHI_SC02_8013AB54_RESULT)
    if(NOT MUSASHI_SC02_8013AB54_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013ab54 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013b204.c
                ${MUSASHI_GENERATED_DIR}/8013b204_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_8013B204_RESULT)
    if(NOT MUSASHI_SC02_8013B204_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013b204 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e064.c
                ${MUSASHI_GENERATED_DIR}/8013e064_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_8013E064_RESULT)
    if(NOT MUSASHI_SC02_8013E064_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e064 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e0fc.c
                ${MUSASHI_GENERATED_DIR}/8013e0fc_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_8013E0FC_RESULT)
    if(NOT MUSASHI_SC02_8013E0FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e0fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e194.c
                ${MUSASHI_GENERATED_DIR}/8013e194_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_8013E194_RESULT)
    if(NOT MUSASHI_SC02_8013E194_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e194 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e22c.c
                ${MUSASHI_GENERATED_DIR}/8013e22c_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8013E22C_RESULT)
    if(NOT MUSASHI_SC02_8013E22C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e22c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e298.c
                ${MUSASHI_GENERATED_DIR}/8013e298_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8013E298_RESULT)
    if(NOT MUSASHI_SC02_8013E298_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e298 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e2c4.c
                ${MUSASHI_GENERATED_DIR}/8013e2c4_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_8013E2C4_RESULT)
    if(NOT MUSASHI_SC02_8013E2C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e2c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e370.c
                ${MUSASHI_GENERATED_DIR}/8013e370_sc02_0031_words.inc --expected-words 40
        RESULT_VARIABLE MUSASHI_SC02_8013E370_RESULT)
    if(NOT MUSASHI_SC02_8013E370_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e370 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e410.c
                ${MUSASHI_GENERATED_DIR}/8013e410_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8013E410_RESULT)
    if(NOT MUSASHI_SC02_8013E410_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e410 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e558.c
                ${MUSASHI_GENERATED_DIR}/8013e558_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8013E558_RESULT)
    if(NOT MUSASHI_SC02_8013E558_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e558 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e588.c
                ${MUSASHI_GENERATED_DIR}/8013e588_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8013E588_RESULT)
    if(NOT MUSASHI_SC02_8013E588_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e588 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e67c.c
                ${MUSASHI_GENERATED_DIR}/8013e67c_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8013E67C_RESULT)
    if(NOT MUSASHI_SC02_8013E67C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e67c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8013e814.c
                ${MUSASHI_GENERATED_DIR}/8013e814_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8013E814_RESULT)
    if(NOT MUSASHI_SC02_8013E814_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8013e814 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014168c.c
                ${MUSASHI_GENERATED_DIR}/8014168c_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8014168C_RESULT)
    if(NOT MUSASHI_SC02_8014168C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014168c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801417c4.c
                ${MUSASHI_GENERATED_DIR}/801417c4_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_801417C4_RESULT)
    if(NOT MUSASHI_SC02_801417C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801417c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801417f8.c
                ${MUSASHI_GENERATED_DIR}/801417f8_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_801417F8_RESULT)
    if(NOT MUSASHI_SC02_801417F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801417f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80141c04.c
                ${MUSASHI_GENERATED_DIR}/80141c04_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80141C04_RESULT)
    if(NOT MUSASHI_SC02_80141C04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80141c04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80141c50.c
                ${MUSASHI_GENERATED_DIR}/80141c50_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80141C50_RESULT)
    if(NOT MUSASHI_SC02_80141C50_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80141c50 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80141ca4.c
                ${MUSASHI_GENERATED_DIR}/80141ca4_sc02_0031_words.inc --expected-words 476
        RESULT_VARIABLE MUSASHI_SC02_80141CA4_RESULT)
    if(NOT MUSASHI_SC02_80141CA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80141ca4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142414.c
                ${MUSASHI_GENERATED_DIR}/80142414_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80142414_RESULT)
    if(NOT MUSASHI_SC02_80142414_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142414 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801426d4.c
                ${MUSASHI_GENERATED_DIR}/801426d4_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_801426D4_RESULT)
    if(NOT MUSASHI_SC02_801426D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801426d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142740.c
                ${MUSASHI_GENERATED_DIR}/80142740_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80142740_RESULT)
    if(NOT MUSASHI_SC02_80142740_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142740 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142778.c
                ${MUSASHI_GENERATED_DIR}/80142778_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80142778_RESULT)
    if(NOT MUSASHI_SC02_80142778_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142778 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142838.c
                ${MUSASHI_GENERATED_DIR}/80142838_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_80142838_RESULT)
    if(NOT MUSASHI_SC02_80142838_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142838 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801428cc.c
                ${MUSASHI_GENERATED_DIR}/801428cc_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_801428CC_RESULT)
    if(NOT MUSASHI_SC02_801428CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801428cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142b2c.c
                ${MUSASHI_GENERATED_DIR}/80142b2c_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_80142B2C_RESULT)
    if(NOT MUSASHI_SC02_80142B2C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142b2c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142bb4.c
                ${MUSASHI_GENERATED_DIR}/80142bb4_sc02_0031_words.inc --expected-words 50
        RESULT_VARIABLE MUSASHI_SC02_80142BB4_RESULT)
    if(NOT MUSASHI_SC02_80142BB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142bb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142c84.c
                ${MUSASHI_GENERATED_DIR}/80142c84_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80142C84_RESULT)
    if(NOT MUSASHI_SC02_80142C84_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142c84 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142d38.c
                ${MUSASHI_GENERATED_DIR}/80142d38_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_80142D38_RESULT)
    if(NOT MUSASHI_SC02_80142D38_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142d38 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142db8.c
                ${MUSASHI_GENERATED_DIR}/80142db8_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80142DB8_RESULT)
    if(NOT MUSASHI_SC02_80142DB8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142db8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142f68.c
                ${MUSASHI_GENERATED_DIR}/80142f68_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_80142F68_RESULT)
    if(NOT MUSASHI_SC02_80142F68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142f68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80142ffc.c
                ${MUSASHI_GENERATED_DIR}/80142ffc_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80142FFC_RESULT)
    if(NOT MUSASHI_SC02_80142FFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80142ffc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801430f4.c
                ${MUSASHI_GENERATED_DIR}/801430f4_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_801430F4_RESULT)
    if(NOT MUSASHI_SC02_801430F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801430f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143188.c
                ${MUSASHI_GENERATED_DIR}/80143188_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80143188_RESULT)
    if(NOT MUSASHI_SC02_80143188_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143188 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801432fc.c
                ${MUSASHI_GENERATED_DIR}/801432fc_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_801432FC_RESULT)
    if(NOT MUSASHI_SC02_801432FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801432fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143390.c
                ${MUSASHI_GENERATED_DIR}/80143390_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80143390_RESULT)
    if(NOT MUSASHI_SC02_80143390_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143390 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801433f0.c
                ${MUSASHI_GENERATED_DIR}/801433f0_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_801433F0_RESULT)
    if(NOT MUSASHI_SC02_801433F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801433f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014350c.c
                ${MUSASHI_GENERATED_DIR}/8014350c_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_8014350C_RESULT)
    if(NOT MUSASHI_SC02_8014350C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014350c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143994.c
                ${MUSASHI_GENERATED_DIR}/80143994_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80143994_RESULT)
    if(NOT MUSASHI_SC02_80143994_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143994 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801439c0.c
                ${MUSASHI_GENERATED_DIR}/801439c0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801439C0_RESULT)
    if(NOT MUSASHI_SC02_801439C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801439c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80143c74.c
                ${MUSASHI_GENERATED_DIR}/80143c74_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80143C74_RESULT)
    if(NOT MUSASHI_SC02_80143C74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80143c74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a680.c
                ${MUSASHI_GENERATED_DIR}/8014a680_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_8014A680_RESULT)
    if(NOT MUSASHI_SC02_8014A680_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a680 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a6a8.c
                ${MUSASHI_GENERATED_DIR}/8014a6a8_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_8014A6A8_RESULT)
    if(NOT MUSASHI_SC02_8014A6A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a6a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a6c4.c
                ${MUSASHI_GENERATED_DIR}/8014a6c4_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8014A6C4_RESULT)
    if(NOT MUSASHI_SC02_8014A6C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a6c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a71c.c
                ${MUSASHI_GENERATED_DIR}/8014a71c_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_8014A71C_RESULT)
    if(NOT MUSASHI_SC02_8014A71C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a71c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8014a830.c
                ${MUSASHI_GENERATED_DIR}/8014a830_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8014A830_RESULT)
    if(NOT MUSASHI_SC02_8014A830_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8014a830 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150f78.c
                ${MUSASHI_GENERATED_DIR}/80150f78_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80150F78_RESULT)
    if(NOT MUSASHI_SC02_80150F78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150f78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150f80.c
                ${MUSASHI_GENERATED_DIR}/80150f80_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80150F80_RESULT)
    if(NOT MUSASHI_SC02_80150F80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150f80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150fb4.c
                ${MUSASHI_GENERATED_DIR}/80150fb4_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80150FB4_RESULT)
    if(NOT MUSASHI_SC02_80150FB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150fb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80150fd8.c
                ${MUSASHI_GENERATED_DIR}/80150fd8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80150FD8_RESULT)
    if(NOT MUSASHI_SC02_80150FD8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80150fd8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151014.c
                ${MUSASHI_GENERATED_DIR}/80151014_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80151014_RESULT)
    if(NOT MUSASHI_SC02_80151014_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151014 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151038.c
                ${MUSASHI_GENERATED_DIR}/80151038_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80151038_RESULT)
    if(NOT MUSASHI_SC02_80151038_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151038 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151070.c
                ${MUSASHI_GENERATED_DIR}/80151070_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80151070_RESULT)
    if(NOT MUSASHI_SC02_80151070_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151070 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151094.c
                ${MUSASHI_GENERATED_DIR}/80151094_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80151094_RESULT)
    if(NOT MUSASHI_SC02_80151094_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151094 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801510c8.c
                ${MUSASHI_GENERATED_DIR}/801510c8_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_801510C8_RESULT)
    if(NOT MUSASHI_SC02_801510C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801510c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801510ec.c
                ${MUSASHI_GENERATED_DIR}/801510ec_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_801510EC_RESULT)
    if(NOT MUSASHI_SC02_801510EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801510ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151110.c
                ${MUSASHI_GENERATED_DIR}/80151110_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80151110_RESULT)
    if(NOT MUSASHI_SC02_80151110_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151110 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151138.c
                ${MUSASHI_GENERATED_DIR}/80151138_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80151138_RESULT)
    if(NOT MUSASHI_SC02_80151138_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151138 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151164.c
                ${MUSASHI_GENERATED_DIR}/80151164_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80151164_RESULT)
    if(NOT MUSASHI_SC02_80151164_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151164 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151184.c
                ${MUSASHI_GENERATED_DIR}/80151184_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80151184_RESULT)
    if(NOT MUSASHI_SC02_80151184_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151184 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801511a8.c
                ${MUSASHI_GENERATED_DIR}/801511a8_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_801511A8_RESULT)
    if(NOT MUSASHI_SC02_801511A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801511a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801511c4.c
                ${MUSASHI_GENERATED_DIR}/801511c4_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_801511C4_RESULT)
    if(NOT MUSASHI_SC02_801511C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801511c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801511e0.c
                ${MUSASHI_GENERATED_DIR}/801511e0_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_801511E0_RESULT)
    if(NOT MUSASHI_SC02_801511E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801511e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151204.c
                ${MUSASHI_GENERATED_DIR}/80151204_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80151204_RESULT)
    if(NOT MUSASHI_SC02_80151204_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151204 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151238.c
                ${MUSASHI_GENERATED_DIR}/80151238_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80151238_RESULT)
    if(NOT MUSASHI_SC02_80151238_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151238 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151664.c
                ${MUSASHI_GENERATED_DIR}/80151664_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_80151664_RESULT)
    if(NOT MUSASHI_SC02_80151664_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151664 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801516f0.c
                ${MUSASHI_GENERATED_DIR}/801516f0_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_801516F0_RESULT)
    if(NOT MUSASHI_SC02_801516F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801516f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015173c.c
                ${MUSASHI_GENERATED_DIR}/8015173c_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8015173C_RESULT)
    if(NOT MUSASHI_SC02_8015173C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015173c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151878.c
                ${MUSASHI_GENERATED_DIR}/80151878_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80151878_RESULT)
    if(NOT MUSASHI_SC02_80151878_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151878 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151924.c
                ${MUSASHI_GENERATED_DIR}/80151924_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80151924_RESULT)
    if(NOT MUSASHI_SC02_80151924_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151924 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151980.c
                ${MUSASHI_GENERATED_DIR}/80151980_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80151980_RESULT)
    if(NOT MUSASHI_SC02_80151980_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151980 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151ae4.c
                ${MUSASHI_GENERATED_DIR}/80151ae4_sc02_0031_words.inc --expected-words 45
        RESULT_VARIABLE MUSASHI_SC02_80151AE4_RESULT)
    if(NOT MUSASHI_SC02_80151AE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151ae4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151d60.c
                ${MUSASHI_GENERATED_DIR}/80151d60_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80151D60_RESULT)
    if(NOT MUSASHI_SC02_80151D60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151d60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151db0.c
                ${MUSASHI_GENERATED_DIR}/80151db0_sc02_0031_words.inc --expected-words 50
        RESULT_VARIABLE MUSASHI_SC02_80151DB0_RESULT)
    if(NOT MUSASHI_SC02_80151DB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151db0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151e78.c
                ${MUSASHI_GENERATED_DIR}/80151e78_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80151E78_RESULT)
    if(NOT MUSASHI_SC02_80151E78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151e78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151ecc.c
                ${MUSASHI_GENERATED_DIR}/80151ecc_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80151ECC_RESULT)
    if(NOT MUSASHI_SC02_80151ECC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151ecc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151f38.c
                ${MUSASHI_GENERATED_DIR}/80151f38_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_80151F38_RESULT)
    if(NOT MUSASHI_SC02_80151F38_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151f38 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80151fb4.c
                ${MUSASHI_GENERATED_DIR}/80151fb4_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_80151FB4_RESULT)
    if(NOT MUSASHI_SC02_80151FB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80151fb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152094.c
                ${MUSASHI_GENERATED_DIR}/80152094_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80152094_RESULT)
    if(NOT MUSASHI_SC02_80152094_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152094 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152194.c
                ${MUSASHI_GENERATED_DIR}/80152194_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_80152194_RESULT)
    if(NOT MUSASHI_SC02_80152194_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152194 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015220c.c
                ${MUSASHI_GENERATED_DIR}/8015220c_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8015220C_RESULT)
    if(NOT MUSASHI_SC02_8015220C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015220c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801522cc.c
                ${MUSASHI_GENERATED_DIR}/801522cc_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_801522CC_RESULT)
    if(NOT MUSASHI_SC02_801522CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801522cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801523ac.c
                ${MUSASHI_GENERATED_DIR}/801523ac_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_801523AC_RESULT)
    if(NOT MUSASHI_SC02_801523AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801523ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801525f4.c
                ${MUSASHI_GENERATED_DIR}/801525f4_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_801525F4_RESULT)
    if(NOT MUSASHI_SC02_801525F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801525f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801526d4.c
                ${MUSASHI_GENERATED_DIR}/801526d4_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801526D4_RESULT)
    if(NOT MUSASHI_SC02_801526D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801526d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152790.c
                ${MUSASHI_GENERATED_DIR}/80152790_sc02_0031_words.inc --expected-words 39
        RESULT_VARIABLE MUSASHI_SC02_80152790_RESULT)
    if(NOT MUSASHI_SC02_80152790_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152790 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152868.c
                ${MUSASHI_GENERATED_DIR}/80152868_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80152868_RESULT)
    if(NOT MUSASHI_SC02_80152868_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152868 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015294c.c
                ${MUSASHI_GENERATED_DIR}/8015294c_sc02_0031_words.inc --expected-words 47
        RESULT_VARIABLE MUSASHI_SC02_8015294C_RESULT)
    if(NOT MUSASHI_SC02_8015294C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015294c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152a08.c
                ${MUSASHI_GENERATED_DIR}/80152a08_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80152A08_RESULT)
    if(NOT MUSASHI_SC02_80152A08_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152a08 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152ac8.c
                ${MUSASHI_GENERATED_DIR}/80152ac8_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_80152AC8_RESULT)
    if(NOT MUSASHI_SC02_80152AC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152ac8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152ba8.c
                ${MUSASHI_GENERATED_DIR}/80152ba8_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80152BA8_RESULT)
    if(NOT MUSASHI_SC02_80152BA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152ba8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152bf0.c
                ${MUSASHI_GENERATED_DIR}/80152bf0_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80152BF0_RESULT)
    if(NOT MUSASHI_SC02_80152BF0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152bf0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152c40.c
                ${MUSASHI_GENERATED_DIR}/80152c40_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80152C40_RESULT)
    if(NOT MUSASHI_SC02_80152C40_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152c40 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152c80.c
                ${MUSASHI_GENERATED_DIR}/80152c80_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_80152C80_RESULT)
    if(NOT MUSASHI_SC02_80152C80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152c80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152d60.c
                ${MUSASHI_GENERATED_DIR}/80152d60_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80152D60_RESULT)
    if(NOT MUSASHI_SC02_80152D60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152d60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152e4c.c
                ${MUSASHI_GENERATED_DIR}/80152e4c_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_80152E4C_RESULT)
    if(NOT MUSASHI_SC02_80152E4C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152e4c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152efc.c
                ${MUSASHI_GENERATED_DIR}/80152efc_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80152EFC_RESULT)
    if(NOT MUSASHI_SC02_80152EFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152efc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80152fbc.c
                ${MUSASHI_GENERATED_DIR}/80152fbc_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_80152FBC_RESULT)
    if(NOT MUSASHI_SC02_80152FBC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80152fbc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015309c.c
                ${MUSASHI_GENERATED_DIR}/8015309c_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8015309C_RESULT)
    if(NOT MUSASHI_SC02_8015309C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015309c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801530e4.c
                ${MUSASHI_GENERATED_DIR}/801530e4_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_801530E4_RESULT)
    if(NOT MUSASHI_SC02_801530E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801530e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153150.c
                ${MUSASHI_GENERATED_DIR}/80153150_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80153150_RESULT)
    if(NOT MUSASHI_SC02_80153150_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153150 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801531bc.c
                ${MUSASHI_GENERATED_DIR}/801531bc_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_801531BC_RESULT)
    if(NOT MUSASHI_SC02_801531BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801531bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015327c.c
                ${MUSASHI_GENERATED_DIR}/8015327c_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_8015327C_RESULT)
    if(NOT MUSASHI_SC02_8015327C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015327c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015335c.c
                ${MUSASHI_GENERATED_DIR}/8015335c_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8015335C_RESULT)
    if(NOT MUSASHI_SC02_8015335C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015335c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801533a4.c
                ${MUSASHI_GENERATED_DIR}/801533a4_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_801533A4_RESULT)
    if(NOT MUSASHI_SC02_801533A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801533a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153410.c
                ${MUSASHI_GENERATED_DIR}/80153410_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_80153410_RESULT)
    if(NOT MUSASHI_SC02_80153410_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153410 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153490.c
                ${MUSASHI_GENERATED_DIR}/80153490_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80153490_RESULT)
    if(NOT MUSASHI_SC02_80153490_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153490 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153550.c
                ${MUSASHI_GENERATED_DIR}/80153550_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_80153550_RESULT)
    if(NOT MUSASHI_SC02_80153550_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153550 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015369c.c
                ${MUSASHI_GENERATED_DIR}/8015369c_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8015369C_RESULT)
    if(NOT MUSASHI_SC02_8015369C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015369c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153bd8.c
                ${MUSASHI_GENERATED_DIR}/80153bd8_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80153BD8_RESULT)
    if(NOT MUSASHI_SC02_80153BD8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153bd8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153bf0.c
                ${MUSASHI_GENERATED_DIR}/80153bf0_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80153BF0_RESULT)
    if(NOT MUSASHI_SC02_80153BF0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153bf0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153c18.c
                ${MUSASHI_GENERATED_DIR}/80153c18_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80153C18_RESULT)
    if(NOT MUSASHI_SC02_80153C18_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153c18 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153c30.c
                ${MUSASHI_GENERATED_DIR}/80153c30_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80153C30_RESULT)
    if(NOT MUSASHI_SC02_80153C30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153c30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153c44.c
                ${MUSASHI_GENERATED_DIR}/80153c44_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80153C44_RESULT)
    if(NOT MUSASHI_SC02_80153C44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153c44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153c74.c
                ${MUSASHI_GENERATED_DIR}/80153c74_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80153C74_RESULT)
    if(NOT MUSASHI_SC02_80153C74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153c74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153c9c.c
                ${MUSASHI_GENERATED_DIR}/80153c9c_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80153C9C_RESULT)
    if(NOT MUSASHI_SC02_80153C9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153c9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153cbc.c
                ${MUSASHI_GENERATED_DIR}/80153cbc_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80153CBC_RESULT)
    if(NOT MUSASHI_SC02_80153CBC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153cbc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80153d34.c
                ${MUSASHI_GENERATED_DIR}/80153d34_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80153D34_RESULT)
    if(NOT MUSASHI_SC02_80153D34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80153d34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015410c.c
                ${MUSASHI_GENERATED_DIR}/8015410c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8015410C_RESULT)
    if(NOT MUSASHI_SC02_8015410C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015410c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154134.c
                ${MUSASHI_GENERATED_DIR}/80154134_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_80154134_RESULT)
    if(NOT MUSASHI_SC02_80154134_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154134 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154150.c
                ${MUSASHI_GENERATED_DIR}/80154150_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80154150_RESULT)
    if(NOT MUSASHI_SC02_80154150_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154150 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154190.c
                ${MUSASHI_GENERATED_DIR}/80154190_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80154190_RESULT)
    if(NOT MUSASHI_SC02_80154190_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154190 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801541d8.c
                ${MUSASHI_GENERATED_DIR}/801541d8_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801541D8_RESULT)
    if(NOT MUSASHI_SC02_801541D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801541d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154218.c
                ${MUSASHI_GENERATED_DIR}/80154218_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80154218_RESULT)
    if(NOT MUSASHI_SC02_80154218_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154218 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154274.c
                ${MUSASHI_GENERATED_DIR}/80154274_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80154274_RESULT)
    if(NOT MUSASHI_SC02_80154274_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154274 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801542a4.c
                ${MUSASHI_GENERATED_DIR}/801542a4_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801542A4_RESULT)
    if(NOT MUSASHI_SC02_801542A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801542a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801542dc.c
                ${MUSASHI_GENERATED_DIR}/801542dc_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801542DC_RESULT)
    if(NOT MUSASHI_SC02_801542DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801542dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015430c.c
                ${MUSASHI_GENERATED_DIR}/8015430c_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8015430C_RESULT)
    if(NOT MUSASHI_SC02_8015430C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015430c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80154418.c
                ${MUSASHI_GENERATED_DIR}/80154418_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80154418_RESULT)
    if(NOT MUSASHI_SC02_80154418_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80154418 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155344.c
                ${MUSASHI_GENERATED_DIR}/80155344_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80155344_RESULT)
    if(NOT MUSASHI_SC02_80155344_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155344 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155394.c
                ${MUSASHI_GENERATED_DIR}/80155394_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80155394_RESULT)
    if(NOT MUSASHI_SC02_80155394_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155394 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801553a8.c
                ${MUSASHI_GENERATED_DIR}/801553a8_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_801553A8_RESULT)
    if(NOT MUSASHI_SC02_801553A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801553a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155440.c
                ${MUSASHI_GENERATED_DIR}/80155440_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80155440_RESULT)
    if(NOT MUSASHI_SC02_80155440_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155440 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801554b8.c
                ${MUSASHI_GENERATED_DIR}/801554b8_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_801554B8_RESULT)
    if(NOT MUSASHI_SC02_801554B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801554b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155518.c
                ${MUSASHI_GENERATED_DIR}/80155518_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80155518_RESULT)
    if(NOT MUSASHI_SC02_80155518_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155518 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015554c.c
                ${MUSASHI_GENERATED_DIR}/8015554c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015554C_RESULT)
    if(NOT MUSASHI_SC02_8015554C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015554c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801555bc.c
                ${MUSASHI_GENERATED_DIR}/801555bc_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801555BC_RESULT)
    if(NOT MUSASHI_SC02_801555BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801555bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155b20.c
                ${MUSASHI_GENERATED_DIR}/80155b20_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_80155B20_RESULT)
    if(NOT MUSASHI_SC02_80155B20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155b20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155b9c.c
                ${MUSASHI_GENERATED_DIR}/80155b9c_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80155B9C_RESULT)
    if(NOT MUSASHI_SC02_80155B9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155b9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155f60.c
                ${MUSASHI_GENERATED_DIR}/80155f60_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80155F60_RESULT)
    if(NOT MUSASHI_SC02_80155F60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155f60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155f80.c
                ${MUSASHI_GENERATED_DIR}/80155f80_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80155F80_RESULT)
    if(NOT MUSASHI_SC02_80155F80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155f80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155fb0.c
                ${MUSASHI_GENERATED_DIR}/80155fb0_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80155FB0_RESULT)
    if(NOT MUSASHI_SC02_80155FB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155fb0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80155fd4.c
                ${MUSASHI_GENERATED_DIR}/80155fd4_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80155FD4_RESULT)
    if(NOT MUSASHI_SC02_80155FD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80155fd4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801565c0.c
                ${MUSASHI_GENERATED_DIR}/801565c0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801565C0_RESULT)
    if(NOT MUSASHI_SC02_801565C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801565c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80156648.c
                ${MUSASHI_GENERATED_DIR}/80156648_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80156648_RESULT)
    if(NOT MUSASHI_SC02_80156648_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80156648 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801567bc.c
                ${MUSASHI_GENERATED_DIR}/801567bc_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_801567BC_RESULT)
    if(NOT MUSASHI_SC02_801567BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801567bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80156a14.c
                ${MUSASHI_GENERATED_DIR}/80156a14_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80156A14_RESULT)
    if(NOT MUSASHI_SC02_80156A14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80156a14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157158.c
                ${MUSASHI_GENERATED_DIR}/80157158_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80157158_RESULT)
    if(NOT MUSASHI_SC02_80157158_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157158 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801574dc.c
                ${MUSASHI_GENERATED_DIR}/801574dc_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_801574DC_RESULT)
    if(NOT MUSASHI_SC02_801574DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801574dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157510.c
                ${MUSASHI_GENERATED_DIR}/80157510_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80157510_RESULT)
    if(NOT MUSASHI_SC02_80157510_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157510 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157580.c
                ${MUSASHI_GENERATED_DIR}/80157580_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80157580_RESULT)
    if(NOT MUSASHI_SC02_80157580_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157580 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015771c.c
                ${MUSASHI_GENERATED_DIR}/8015771c_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8015771C_RESULT)
    if(NOT MUSASHI_SC02_8015771C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015771c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015773c.c
                ${MUSASHI_GENERATED_DIR}/8015773c_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8015773C_RESULT)
    if(NOT MUSASHI_SC02_8015773C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015773c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157880.c
                ${MUSASHI_GENERATED_DIR}/80157880_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80157880_RESULT)
    if(NOT MUSASHI_SC02_80157880_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157880 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157a8c.c
                ${MUSASHI_GENERATED_DIR}/80157a8c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80157A8C_RESULT)
    if(NOT MUSASHI_SC02_80157A8C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157a8c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157ac8.c
                ${MUSASHI_GENERATED_DIR}/80157ac8_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_80157AC8_RESULT)
    if(NOT MUSASHI_SC02_80157AC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157ac8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157b74.c
                ${MUSASHI_GENERATED_DIR}/80157b74_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80157B74_RESULT)
    if(NOT MUSASHI_SC02_80157B74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157b74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157ccc.c
                ${MUSASHI_GENERATED_DIR}/80157ccc_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80157CCC_RESULT)
    if(NOT MUSASHI_SC02_80157CCC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157ccc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157d74.c
                ${MUSASHI_GENERATED_DIR}/80157d74_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80157D74_RESULT)
    if(NOT MUSASHI_SC02_80157D74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157d74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157e00.c
                ${MUSASHI_GENERATED_DIR}/80157e00_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80157E00_RESULT)
    if(NOT MUSASHI_SC02_80157E00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157e00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157e38.c
                ${MUSASHI_GENERATED_DIR}/80157e38_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80157E38_RESULT)
    if(NOT MUSASHI_SC02_80157E38_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157e38 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157ea4.c
                ${MUSASHI_GENERATED_DIR}/80157ea4_sc02_0031_words.inc --expected-words 48
        RESULT_VARIABLE MUSASHI_SC02_80157EA4_RESULT)
    if(NOT MUSASHI_SC02_80157EA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157ea4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80157f64.c
                ${MUSASHI_GENERATED_DIR}/80157f64_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80157F64_RESULT)
    if(NOT MUSASHI_SC02_80157F64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80157f64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80158000.c
                ${MUSASHI_GENERATED_DIR}/80158000_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80158000_RESULT)
    if(NOT MUSASHI_SC02_80158000_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80158000 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80158288.c
                ${MUSASHI_GENERATED_DIR}/80158288_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80158288_RESULT)
    if(NOT MUSASHI_SC02_80158288_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80158288 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801582c0.c
                ${MUSASHI_GENERATED_DIR}/801582c0_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_801582C0_RESULT)
    if(NOT MUSASHI_SC02_801582C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801582c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80158548.c
                ${MUSASHI_GENERATED_DIR}/80158548_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80158548_RESULT)
    if(NOT MUSASHI_SC02_80158548_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80158548 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801585ac.c
                ${MUSASHI_GENERATED_DIR}/801585ac_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801585AC_RESULT)
    if(NOT MUSASHI_SC02_801585AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801585ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801585ec.c
                ${MUSASHI_GENERATED_DIR}/801585ec_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_801585EC_RESULT)
    if(NOT MUSASHI_SC02_801585EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801585ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80158ab4.c
                ${MUSASHI_GENERATED_DIR}/80158ab4_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80158AB4_RESULT)
    if(NOT MUSASHI_SC02_80158AB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80158ab4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80158ae4.c
                ${MUSASHI_GENERATED_DIR}/80158ae4_sc02_0031_words.inc --expected-words 51
        RESULT_VARIABLE MUSASHI_SC02_80158AE4_RESULT)
    if(NOT MUSASHI_SC02_80158AE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80158ae4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801592cc.c
                ${MUSASHI_GENERATED_DIR}/801592cc_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_801592CC_RESULT)
    if(NOT MUSASHI_SC02_801592CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801592cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801593e4.c
                ${MUSASHI_GENERATED_DIR}/801593e4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801593E4_RESULT)
    if(NOT MUSASHI_SC02_801593E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801593e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801596d4.c
                ${MUSASHI_GENERATED_DIR}/801596d4_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_801596D4_RESULT)
    if(NOT MUSASHI_SC02_801596D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801596d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80159874.c
                ${MUSASHI_GENERATED_DIR}/80159874_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80159874_RESULT)
    if(NOT MUSASHI_SC02_80159874_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80159874 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015987c.c
                ${MUSASHI_GENERATED_DIR}/8015987c_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8015987C_RESULT)
    if(NOT MUSASHI_SC02_8015987C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015987c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801598bc.c
                ${MUSASHI_GENERATED_DIR}/801598bc_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_801598BC_RESULT)
    if(NOT MUSASHI_SC02_801598BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801598bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801599e0.c
                ${MUSASHI_GENERATED_DIR}/801599e0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801599E0_RESULT)
    if(NOT MUSASHI_SC02_801599E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801599e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80159b08.c
                ${MUSASHI_GENERATED_DIR}/80159b08_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80159B08_RESULT)
    if(NOT MUSASHI_SC02_80159B08_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80159b08 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80159b3c.c
                ${MUSASHI_GENERATED_DIR}/80159b3c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80159B3C_RESULT)
    if(NOT MUSASHI_SC02_80159B3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80159b3c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80159bac.c
                ${MUSASHI_GENERATED_DIR}/80159bac_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80159BAC_RESULT)
    if(NOT MUSASHI_SC02_80159BAC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80159bac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015a1fc.c
                ${MUSASHI_GENERATED_DIR}/8015a1fc_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015A1FC_RESULT)
    if(NOT MUSASHI_SC02_8015A1FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015a1fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015a230.c
                ${MUSASHI_GENERATED_DIR}/8015a230_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015A230_RESULT)
    if(NOT MUSASHI_SC02_8015A230_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015a230 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015a2a0.c
                ${MUSASHI_GENERATED_DIR}/8015a2a0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015A2A0_RESULT)
    if(NOT MUSASHI_SC02_8015A2A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015a2a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015abd4.c
                ${MUSASHI_GENERATED_DIR}/8015abd4_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_8015ABD4_RESULT)
    if(NOT MUSASHI_SC02_8015ABD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015abd4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ac90.c
                ${MUSASHI_GENERATED_DIR}/8015ac90_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015AC90_RESULT)
    if(NOT MUSASHI_SC02_8015AC90_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ac90 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015acc4.c
                ${MUSASHI_GENERATED_DIR}/8015acc4_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8015ACC4_RESULT)
    if(NOT MUSASHI_SC02_8015ACC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015acc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ad08.c
                ${MUSASHI_GENERATED_DIR}/8015ad08_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015AD08_RESULT)
    if(NOT MUSASHI_SC02_8015AD08_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ad08 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ad78.c
                ${MUSASHI_GENERATED_DIR}/8015ad78_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015AD78_RESULT)
    if(NOT MUSASHI_SC02_8015AD78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ad78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015adb0.c
                ${MUSASHI_GENERATED_DIR}/8015adb0_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_8015ADB0_RESULT)
    if(NOT MUSASHI_SC02_8015ADB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015adb0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015b858.c
                ${MUSASHI_GENERATED_DIR}/8015b858_sc02_0031_words.inc --expected-words 40
        RESULT_VARIABLE MUSASHI_SC02_8015B858_RESULT)
    if(NOT MUSASHI_SC02_8015B858_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015b858 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015b8f8.c
                ${MUSASHI_GENERATED_DIR}/8015b8f8_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8015B8F8_RESULT)
    if(NOT MUSASHI_SC02_8015B8F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015b8f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015bd8c.c
                ${MUSASHI_GENERATED_DIR}/8015bd8c_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8015BD8C_RESULT)
    if(NOT MUSASHI_SC02_8015BD8C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015bd8c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015bdd0.c
                ${MUSASHI_GENERATED_DIR}/8015bdd0_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015BDD0_RESULT)
    if(NOT MUSASHI_SC02_8015BDD0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015bdd0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015be04.c
                ${MUSASHI_GENERATED_DIR}/8015be04_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015BE04_RESULT)
    if(NOT MUSASHI_SC02_8015BE04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015be04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015be74.c
                ${MUSASHI_GENERATED_DIR}/8015be74_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8015BE74_RESULT)
    if(NOT MUSASHI_SC02_8015BE74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015be74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015be94.c
                ${MUSASHI_GENERATED_DIR}/8015be94_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8015BE94_RESULT)
    if(NOT MUSASHI_SC02_8015BE94_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015be94 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015bec4.c
                ${MUSASHI_GENERATED_DIR}/8015bec4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8015BEC4_RESULT)
    if(NOT MUSASHI_SC02_8015BEC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015bec4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015bee4.c
                ${MUSASHI_GENERATED_DIR}/8015bee4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8015BEE4_RESULT)
    if(NOT MUSASHI_SC02_8015BEE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015bee4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015bf04.c
                ${MUSASHI_GENERATED_DIR}/8015bf04_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8015BF04_RESULT)
    if(NOT MUSASHI_SC02_8015BF04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015bf04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015bf48.c
                ${MUSASHI_GENERATED_DIR}/8015bf48_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015BF48_RESULT)
    if(NOT MUSASHI_SC02_8015BF48_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015bf48 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015bf7c.c
                ${MUSASHI_GENERATED_DIR}/8015bf7c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015BF7C_RESULT)
    if(NOT MUSASHI_SC02_8015BF7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015bf7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015bfb0.c
                ${MUSASHI_GENERATED_DIR}/8015bfb0_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8015BFB0_RESULT)
    if(NOT MUSASHI_SC02_8015BFB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015bfb0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015c08c.c
                ${MUSASHI_GENERATED_DIR}/8015c08c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015C08C_RESULT)
    if(NOT MUSASHI_SC02_8015C08C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015c08c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015c6ac.c
                ${MUSASHI_GENERATED_DIR}/8015c6ac_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015C6AC_RESULT)
    if(NOT MUSASHI_SC02_8015C6AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015c6ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015c6e0.c
                ${MUSASHI_GENERATED_DIR}/8015c6e0_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015C6E0_RESULT)
    if(NOT MUSASHI_SC02_8015C6E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015c6e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015c750.c
                ${MUSASHI_GENERATED_DIR}/8015c750_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015C750_RESULT)
    if(NOT MUSASHI_SC02_8015C750_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015c750 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015c788.c
                ${MUSASHI_GENERATED_DIR}/8015c788_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_8015C788_RESULT)
    if(NOT MUSASHI_SC02_8015C788_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015c788 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015cb94.c
                ${MUSASHI_GENERATED_DIR}/8015cb94_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015CB94_RESULT)
    if(NOT MUSASHI_SC02_8015CB94_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015cb94 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015cc0c.c
                ${MUSASHI_GENERATED_DIR}/8015cc0c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015CC0C_RESULT)
    if(NOT MUSASHI_SC02_8015CC0C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015cc0c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015cc40.c
                ${MUSASHI_GENERATED_DIR}/8015cc40_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015CC40_RESULT)
    if(NOT MUSASHI_SC02_8015CC40_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015cc40 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ccb0.c
                ${MUSASHI_GENERATED_DIR}/8015ccb0_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8015CCB0_RESULT)
    if(NOT MUSASHI_SC02_8015CCB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ccb0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ccd0.c
                ${MUSASHI_GENERATED_DIR}/8015ccd0_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8015CCD0_RESULT)
    if(NOT MUSASHI_SC02_8015CCD0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ccd0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015cf24.c
                ${MUSASHI_GENERATED_DIR}/8015cf24_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015CF24_RESULT)
    if(NOT MUSASHI_SC02_8015CF24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015cf24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015cf58.c
                ${MUSASHI_GENERATED_DIR}/8015cf58_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015CF58_RESULT)
    if(NOT MUSASHI_SC02_8015CF58_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015cf58 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015cf8c.c
                ${MUSASHI_GENERATED_DIR}/8015cf8c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015CF8C_RESULT)
    if(NOT MUSASHI_SC02_8015CF8C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015cf8c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015cffc.c
                ${MUSASHI_GENERATED_DIR}/8015cffc_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8015CFFC_RESULT)
    if(NOT MUSASHI_SC02_8015CFFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015cffc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015d480.c
                ${MUSASHI_GENERATED_DIR}/8015d480_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015D480_RESULT)
    if(NOT MUSASHI_SC02_8015D480_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015d480 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015d4b4.c
                ${MUSASHI_GENERATED_DIR}/8015d4b4_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015D4B4_RESULT)
    if(NOT MUSASHI_SC02_8015D4B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015d4b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015d524.c
                ${MUSASHI_GENERATED_DIR}/8015d524_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8015D524_RESULT)
    if(NOT MUSASHI_SC02_8015D524_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015d524 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015d544.c
                ${MUSASHI_GENERATED_DIR}/8015d544_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015D544_RESULT)
    if(NOT MUSASHI_SC02_8015D544_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015d544 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015d57c.c
                ${MUSASHI_GENERATED_DIR}/8015d57c_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8015D57C_RESULT)
    if(NOT MUSASHI_SC02_8015D57C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015d57c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015da5c.c
                ${MUSASHI_GENERATED_DIR}/8015da5c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015DA5C_RESULT)
    if(NOT MUSASHI_SC02_8015DA5C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015da5c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015da90.c
                ${MUSASHI_GENERATED_DIR}/8015da90_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015DA90_RESULT)
    if(NOT MUSASHI_SC02_8015DA90_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015da90 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015dac4.c
                ${MUSASHI_GENERATED_DIR}/8015dac4_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015DAC4_RESULT)
    if(NOT MUSASHI_SC02_8015DAC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015dac4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015db34.c
                ${MUSASHI_GENERATED_DIR}/8015db34_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015DB34_RESULT)
    if(NOT MUSASHI_SC02_8015DB34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015db34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015db6c.c
                ${MUSASHI_GENERATED_DIR}/8015db6c_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_8015DB6C_RESULT)
    if(NOT MUSASHI_SC02_8015DB6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015db6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015dc84.c
                ${MUSASHI_GENERATED_DIR}/8015dc84_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015DC84_RESULT)
    if(NOT MUSASHI_SC02_8015DC84_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015dc84 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015dd74.c
                ${MUSASHI_GENERATED_DIR}/8015dd74_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_8015DD74_RESULT)
    if(NOT MUSASHI_SC02_8015DD74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015dd74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ddf0.c
                ${MUSASHI_GENERATED_DIR}/8015ddf0_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015DDF0_RESULT)
    if(NOT MUSASHI_SC02_8015DDF0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ddf0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015de24.c
                ${MUSASHI_GENERATED_DIR}/8015de24_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015DE24_RESULT)
    if(NOT MUSASHI_SC02_8015DE24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015de24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015de94.c
                ${MUSASHI_GENERATED_DIR}/8015de94_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015DE94_RESULT)
    if(NOT MUSASHI_SC02_8015DE94_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015de94 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015decc.c
                ${MUSASHI_GENERATED_DIR}/8015decc_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_8015DECC_RESULT)
    if(NOT MUSASHI_SC02_8015DECC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015decc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015dfe4.c
                ${MUSASHI_GENERATED_DIR}/8015dfe4_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015DFE4_RESULT)
    if(NOT MUSASHI_SC02_8015DFE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015dfe4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e0d4.c
                ${MUSASHI_GENERATED_DIR}/8015e0d4_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_8015E0D4_RESULT)
    if(NOT MUSASHI_SC02_8015E0D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e0d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e150.c
                ${MUSASHI_GENERATED_DIR}/8015e150_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015E150_RESULT)
    if(NOT MUSASHI_SC02_8015E150_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e150 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e184.c
                ${MUSASHI_GENERATED_DIR}/8015e184_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015E184_RESULT)
    if(NOT MUSASHI_SC02_8015E184_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e184 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e1f4.c
                ${MUSASHI_GENERATED_DIR}/8015e1f4_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015E1F4_RESULT)
    if(NOT MUSASHI_SC02_8015E1F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e1f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e22c.c
                ${MUSASHI_GENERATED_DIR}/8015e22c_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_8015E22C_RESULT)
    if(NOT MUSASHI_SC02_8015E22C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e22c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e288.c
                ${MUSASHI_GENERATED_DIR}/8015e288_sc02_0031_words.inc --expected-words 47
        RESULT_VARIABLE MUSASHI_SC02_8015E288_RESULT)
    if(NOT MUSASHI_SC02_8015E288_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e288 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e40c.c
                ${MUSASHI_GENERATED_DIR}/8015e40c_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_8015E40C_RESULT)
    if(NOT MUSASHI_SC02_8015E40C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e40c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e5b0.c
                ${MUSASHI_GENERATED_DIR}/8015e5b0_sc02_0031_words.inc --expected-words 58
        RESULT_VARIABLE MUSASHI_SC02_8015E5B0_RESULT)
    if(NOT MUSASHI_SC02_8015E5B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e5b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e714.c
                ${MUSASHI_GENERATED_DIR}/8015e714_sc02_0031_words.inc --expected-words 78
        RESULT_VARIABLE MUSASHI_SC02_8015E714_RESULT)
    if(NOT MUSASHI_SC02_8015E714_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e714 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e84c.c
                ${MUSASHI_GENERATED_DIR}/8015e84c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015E84C_RESULT)
    if(NOT MUSASHI_SC02_8015E84C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e84c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e880.c
                ${MUSASHI_GENERATED_DIR}/8015e880_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015E880_RESULT)
    if(NOT MUSASHI_SC02_8015E880_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e880 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e8b4.c
                ${MUSASHI_GENERATED_DIR}/8015e8b4_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015E8B4_RESULT)
    if(NOT MUSASHI_SC02_8015E8B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e8b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e924.c
                ${MUSASHI_GENERATED_DIR}/8015e924_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015E924_RESULT)
    if(NOT MUSASHI_SC02_8015E924_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e924 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e95c.c
                ${MUSASHI_GENERATED_DIR}/8015e95c_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_8015E95C_RESULT)
    if(NOT MUSASHI_SC02_8015E95C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e95c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015e9b8.c
                ${MUSASHI_GENERATED_DIR}/8015e9b8_sc02_0031_words.inc --expected-words 33
        RESULT_VARIABLE MUSASHI_SC02_8015E9B8_RESULT)
    if(NOT MUSASHI_SC02_8015E9B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015e9b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015eda0.c
                ${MUSASHI_GENERATED_DIR}/8015eda0_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015EDA0_RESULT)
    if(NOT MUSASHI_SC02_8015EDA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015eda0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015edd4.c
                ${MUSASHI_GENERATED_DIR}/8015edd4_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015EDD4_RESULT)
    if(NOT MUSASHI_SC02_8015EDD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015edd4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015ee44.c
                ${MUSASHI_GENERATED_DIR}/8015ee44_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015EE44_RESULT)
    if(NOT MUSASHI_SC02_8015EE44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015ee44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015efa4.c
                ${MUSASHI_GENERATED_DIR}/8015efa4_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015EFA4_RESULT)
    if(NOT MUSASHI_SC02_8015EFA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015efa4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015efd8.c
                ${MUSASHI_GENERATED_DIR}/8015efd8_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015EFD8_RESULT)
    if(NOT MUSASHI_SC02_8015EFD8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015efd8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f048.c
                ${MUSASHI_GENERATED_DIR}/8015f048_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015F048_RESULT)
    if(NOT MUSASHI_SC02_8015F048_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f048 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f080.c
                ${MUSASHI_GENERATED_DIR}/8015f080_sc02_0031_words.inc --expected-words 38
        RESULT_VARIABLE MUSASHI_SC02_8015F080_RESULT)
    if(NOT MUSASHI_SC02_8015F080_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f080 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f260.c
                ${MUSASHI_GENERATED_DIR}/8015f260_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_8015F260_RESULT)
    if(NOT MUSASHI_SC02_8015F260_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f260 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f2bc.c
                ${MUSASHI_GENERATED_DIR}/8015f2bc_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015F2BC_RESULT)
    if(NOT MUSASHI_SC02_8015F2BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f2bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f2f0.c
                ${MUSASHI_GENERATED_DIR}/8015f2f0_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015F2F0_RESULT)
    if(NOT MUSASHI_SC02_8015F2F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f2f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f360.c
                ${MUSASHI_GENERATED_DIR}/8015f360_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8015F360_RESULT)
    if(NOT MUSASHI_SC02_8015F360_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f360 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f380.c
                ${MUSASHI_GENERATED_DIR}/8015f380_sc02_0031_words.inc --expected-words 50
        RESULT_VARIABLE MUSASHI_SC02_8015F380_RESULT)
    if(NOT MUSASHI_SC02_8015F380_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f380 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f738.c
                ${MUSASHI_GENERATED_DIR}/8015f738_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015F738_RESULT)
    if(NOT MUSASHI_SC02_8015F738_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f738 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f76c.c
                ${MUSASHI_GENERATED_DIR}/8015f76c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015F76C_RESULT)
    if(NOT MUSASHI_SC02_8015F76C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f76c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f7a0.c
                ${MUSASHI_GENERATED_DIR}/8015f7a0_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015F7A0_RESULT)
    if(NOT MUSASHI_SC02_8015F7A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f7a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f810.c
                ${MUSASHI_GENERATED_DIR}/8015f810_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8015F810_RESULT)
    if(NOT MUSASHI_SC02_8015F810_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f810 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f848.c
                ${MUSASHI_GENERATED_DIR}/8015f848_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8015F848_RESULT)
    if(NOT MUSASHI_SC02_8015F848_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f848 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015f948.c
                ${MUSASHI_GENERATED_DIR}/8015f948_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_8015F948_RESULT)
    if(NOT MUSASHI_SC02_8015F948_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015f948 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015fa24.c
                ${MUSASHI_GENERATED_DIR}/8015fa24_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8015FA24_RESULT)
    if(NOT MUSASHI_SC02_8015FA24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015fa24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015fa44.c
                ${MUSASHI_GENERATED_DIR}/8015fa44_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015FA44_RESULT)
    if(NOT MUSASHI_SC02_8015FA44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015fa44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8015fa78.c
                ${MUSASHI_GENERATED_DIR}/8015fa78_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8015FA78_RESULT)
    if(NOT MUSASHI_SC02_8015FA78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8015fa78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801600d0.c
                ${MUSASHI_GENERATED_DIR}/801600d0_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_801600D0_RESULT)
    if(NOT MUSASHI_SC02_801600D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801600d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160104.c
                ${MUSASHI_GENERATED_DIR}/80160104_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80160104_RESULT)
    if(NOT MUSASHI_SC02_80160104_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160104 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160174.c
                ${MUSASHI_GENERATED_DIR}/80160174_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80160174_RESULT)
    if(NOT MUSASHI_SC02_80160174_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160174 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801601ac.c
                ${MUSASHI_GENERATED_DIR}/801601ac_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801601AC_RESULT)
    if(NOT MUSASHI_SC02_801601AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801601ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801601e4.c
                ${MUSASHI_GENERATED_DIR}/801601e4_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_801601E4_RESULT)
    if(NOT MUSASHI_SC02_801601E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801601e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160244.c
                ${MUSASHI_GENERATED_DIR}/80160244_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80160244_RESULT)
    if(NOT MUSASHI_SC02_80160244_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160244 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160334.c
                ${MUSASHI_GENERATED_DIR}/80160334_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80160334_RESULT)
    if(NOT MUSASHI_SC02_80160334_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160334 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160368.c
                ${MUSASHI_GENERATED_DIR}/80160368_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80160368_RESULT)
    if(NOT MUSASHI_SC02_80160368_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160368 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801603d8.c
                ${MUSASHI_GENERATED_DIR}/801603d8_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801603D8_RESULT)
    if(NOT MUSASHI_SC02_801603D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801603d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801607b8.c
                ${MUSASHI_GENERATED_DIR}/801607b8_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_801607B8_RESULT)
    if(NOT MUSASHI_SC02_801607B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801607b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801607e4.c
                ${MUSASHI_GENERATED_DIR}/801607e4_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_801607E4_RESULT)
    if(NOT MUSASHI_SC02_801607E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801607e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160818.c
                ${MUSASHI_GENERATED_DIR}/80160818_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80160818_RESULT)
    if(NOT MUSASHI_SC02_80160818_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160818 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160888.c
                ${MUSASHI_GENERATED_DIR}/80160888_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80160888_RESULT)
    if(NOT MUSASHI_SC02_80160888_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160888 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801608c0.c
                ${MUSASHI_GENERATED_DIR}/801608c0_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_801608C0_RESULT)
    if(NOT MUSASHI_SC02_801608C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801608c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160a28.c
                ${MUSASHI_GENERATED_DIR}/80160a28_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80160A28_RESULT)
    if(NOT MUSASHI_SC02_80160A28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160a28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160a74.c
                ${MUSASHI_GENERATED_DIR}/80160a74_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80160A74_RESULT)
    if(NOT MUSASHI_SC02_80160A74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160a74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160acc.c
                ${MUSASHI_GENERATED_DIR}/80160acc_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80160ACC_RESULT)
    if(NOT MUSASHI_SC02_80160ACC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160acc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160b00.c
                ${MUSASHI_GENERATED_DIR}/80160b00_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80160B00_RESULT)
    if(NOT MUSASHI_SC02_80160B00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160b00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160b70.c
                ${MUSASHI_GENERATED_DIR}/80160b70_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80160B70_RESULT)
    if(NOT MUSASHI_SC02_80160B70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160b70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160bb4.c
                ${MUSASHI_GENERATED_DIR}/80160bb4_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_80160BB4_RESULT)
    if(NOT MUSASHI_SC02_80160BB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160bb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160cb4.c
                ${MUSASHI_GENERATED_DIR}/80160cb4_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80160CB4_RESULT)
    if(NOT MUSASHI_SC02_80160CB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160cb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160dec.c
                ${MUSASHI_GENERATED_DIR}/80160dec_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80160DEC_RESULT)
    if(NOT MUSASHI_SC02_80160DEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160dec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160e3c.c
                ${MUSASHI_GENERATED_DIR}/80160e3c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80160E3C_RESULT)
    if(NOT MUSASHI_SC02_80160E3C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160e3c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160e70.c
                ${MUSASHI_GENERATED_DIR}/80160e70_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80160E70_RESULT)
    if(NOT MUSASHI_SC02_80160E70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160e70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160ee0.c
                ${MUSASHI_GENERATED_DIR}/80160ee0_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80160EE0_RESULT)
    if(NOT MUSASHI_SC02_80160EE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160ee0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160f00.c
                ${MUSASHI_GENERATED_DIR}/80160f00_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80160F00_RESULT)
    if(NOT MUSASHI_SC02_80160F00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160f00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160f70.c
                ${MUSASHI_GENERATED_DIR}/80160f70_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80160F70_RESULT)
    if(NOT MUSASHI_SC02_80160F70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160f70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80160fe0.c
                ${MUSASHI_GENERATED_DIR}/80160fe0_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80160FE0_RESULT)
    if(NOT MUSASHI_SC02_80160FE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80160fe0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161094.c
                ${MUSASHI_GENERATED_DIR}/80161094_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_80161094_RESULT)
    if(NOT MUSASHI_SC02_80161094_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161094 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161104.c
                ${MUSASHI_GENERATED_DIR}/80161104_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80161104_RESULT)
    if(NOT MUSASHI_SC02_80161104_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161104 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161124.c
                ${MUSASHI_GENERATED_DIR}/80161124_sc02_0031_words.inc --expected-words 57
        RESULT_VARIABLE MUSASHI_SC02_80161124_RESULT)
    if(NOT MUSASHI_SC02_80161124_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161124 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161208.c
                ${MUSASHI_GENERATED_DIR}/80161208_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80161208_RESULT)
    if(NOT MUSASHI_SC02_80161208_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161208 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161240.c
                ${MUSASHI_GENERATED_DIR}/80161240_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80161240_RESULT)
    if(NOT MUSASHI_SC02_80161240_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161240 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161278.c
                ${MUSASHI_GENERATED_DIR}/80161278_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80161278_RESULT)
    if(NOT MUSASHI_SC02_80161278_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161278 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016130c.c
                ${MUSASHI_GENERATED_DIR}/8016130c_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_8016130C_RESULT)
    if(NOT MUSASHI_SC02_8016130C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016130c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161418.c
                ${MUSASHI_GENERATED_DIR}/80161418_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80161418_RESULT)
    if(NOT MUSASHI_SC02_80161418_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161418 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161450.c
                ${MUSASHI_GENERATED_DIR}/80161450_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80161450_RESULT)
    if(NOT MUSASHI_SC02_80161450_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161450 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161488.c
                ${MUSASHI_GENERATED_DIR}/80161488_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80161488_RESULT)
    if(NOT MUSASHI_SC02_80161488_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161488 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801614e4.c
                ${MUSASHI_GENERATED_DIR}/801614e4_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801614E4_RESULT)
    if(NOT MUSASHI_SC02_801614E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801614e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016151c.c
                ${MUSASHI_GENERATED_DIR}/8016151c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8016151C_RESULT)
    if(NOT MUSASHI_SC02_8016151C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016151c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161554.c
                ${MUSASHI_GENERATED_DIR}/80161554_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80161554_RESULT)
    if(NOT MUSASHI_SC02_80161554_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161554 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016158c.c
                ${MUSASHI_GENERATED_DIR}/8016158c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8016158C_RESULT)
    if(NOT MUSASHI_SC02_8016158C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016158c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801615c4.c
                ${MUSASHI_GENERATED_DIR}/801615c4_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_801615C4_RESULT)
    if(NOT MUSASHI_SC02_801615C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801615c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161888.c
                ${MUSASHI_GENERATED_DIR}/80161888_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_80161888_RESULT)
    if(NOT MUSASHI_SC02_80161888_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161888 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016191c.c
                ${MUSASHI_GENERATED_DIR}/8016191c_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8016191C_RESULT)
    if(NOT MUSASHI_SC02_8016191C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016191c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801619d0.c
                ${MUSASHI_GENERATED_DIR}/801619d0_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801619D0_RESULT)
    if(NOT MUSASHI_SC02_801619D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801619d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161a00.c
                ${MUSASHI_GENERATED_DIR}/80161a00_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80161A00_RESULT)
    if(NOT MUSASHI_SC02_80161A00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161a00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161a30.c
                ${MUSASHI_GENERATED_DIR}/80161a30_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80161A30_RESULT)
    if(NOT MUSASHI_SC02_80161A30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161a30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161a60.c
                ${MUSASHI_GENERATED_DIR}/80161a60_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80161A60_RESULT)
    if(NOT MUSASHI_SC02_80161A60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161a60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161b84.c
                ${MUSASHI_GENERATED_DIR}/80161b84_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80161B84_RESULT)
    if(NOT MUSASHI_SC02_80161B84_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161b84 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161be0.c
                ${MUSASHI_GENERATED_DIR}/80161be0_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80161BE0_RESULT)
    if(NOT MUSASHI_SC02_80161BE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161be0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80161d58.c
                ${MUSASHI_GENERATED_DIR}/80161d58_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80161D58_RESULT)
    if(NOT MUSASHI_SC02_80161D58_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80161d58 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162120.c
                ${MUSASHI_GENERATED_DIR}/80162120_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80162120_RESULT)
    if(NOT MUSASHI_SC02_80162120_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162120 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016236c.c
                ${MUSASHI_GENERATED_DIR}/8016236c_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8016236C_RESULT)
    if(NOT MUSASHI_SC02_8016236C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016236c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801623b8.c
                ${MUSASHI_GENERATED_DIR}/801623b8_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_801623B8_RESULT)
    if(NOT MUSASHI_SC02_801623B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801623b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162414.c
                ${MUSASHI_GENERATED_DIR}/80162414_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80162414_RESULT)
    if(NOT MUSASHI_SC02_80162414_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162414 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162714.c
                ${MUSASHI_GENERATED_DIR}/80162714_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80162714_RESULT)
    if(NOT MUSASHI_SC02_80162714_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162714 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162acc.c
                ${MUSASHI_GENERATED_DIR}/80162acc_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80162ACC_RESULT)
    if(NOT MUSASHI_SC02_80162ACC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162acc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162ae0.c
                ${MUSASHI_GENERATED_DIR}/80162ae0_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80162AE0_RESULT)
    if(NOT MUSASHI_SC02_80162AE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162ae0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162cc4.c
                ${MUSASHI_GENERATED_DIR}/80162cc4_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80162CC4_RESULT)
    if(NOT MUSASHI_SC02_80162CC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162cc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162ccc.c
                ${MUSASHI_GENERATED_DIR}/80162ccc_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80162CCC_RESULT)
    if(NOT MUSASHI_SC02_80162CCC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162ccc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162d28.c
                ${MUSASHI_GENERATED_DIR}/80162d28_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80162D28_RESULT)
    if(NOT MUSASHI_SC02_80162D28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162d28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162d88.c
                ${MUSASHI_GENERATED_DIR}/80162d88_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80162D88_RESULT)
    if(NOT MUSASHI_SC02_80162D88_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162d88 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162de8.c
                ${MUSASHI_GENERATED_DIR}/80162de8_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80162DE8_RESULT)
    if(NOT MUSASHI_SC02_80162DE8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162de8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162e48.c
                ${MUSASHI_GENERATED_DIR}/80162e48_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80162E48_RESULT)
    if(NOT MUSASHI_SC02_80162E48_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162e48 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162ea8.c
                ${MUSASHI_GENERATED_DIR}/80162ea8_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80162EA8_RESULT)
    if(NOT MUSASHI_SC02_80162EA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162ea8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162f08.c
                ${MUSASHI_GENERATED_DIR}/80162f08_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80162F08_RESULT)
    if(NOT MUSASHI_SC02_80162F08_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162f08 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162f60.c
                ${MUSASHI_GENERATED_DIR}/80162f60_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80162F60_RESULT)
    if(NOT MUSASHI_SC02_80162F60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162f60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162f80.c
                ${MUSASHI_GENERATED_DIR}/80162f80_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80162F80_RESULT)
    if(NOT MUSASHI_SC02_80162F80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162f80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162fa0.c
                ${MUSASHI_GENERATED_DIR}/80162fa0_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80162FA0_RESULT)
    if(NOT MUSASHI_SC02_80162FA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162fa0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80162fc0.c
                ${MUSASHI_GENERATED_DIR}/80162fc0_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80162FC0_RESULT)
    if(NOT MUSASHI_SC02_80162FC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80162fc0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80163234.c
                ${MUSASHI_GENERATED_DIR}/80163234_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80163234_RESULT)
    if(NOT MUSASHI_SC02_80163234_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80163234 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801632e0.c
                ${MUSASHI_GENERATED_DIR}/801632e0_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_801632E0_RESULT)
    if(NOT MUSASHI_SC02_801632E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801632e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801632f0.c
                ${MUSASHI_GENERATED_DIR}/801632f0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801632F0_RESULT)
    if(NOT MUSASHI_SC02_801632F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801632f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801633a8.c
                ${MUSASHI_GENERATED_DIR}/801633a8_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_801633A8_RESULT)
    if(NOT MUSASHI_SC02_801633A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801633a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016345c.c
                ${MUSASHI_GENERATED_DIR}/8016345c_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_8016345C_RESULT)
    if(NOT MUSASHI_SC02_8016345C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016345c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80163664.c
                ${MUSASHI_GENERATED_DIR}/80163664_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80163664_RESULT)
    if(NOT MUSASHI_SC02_80163664_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80163664 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801636d0.c
                ${MUSASHI_GENERATED_DIR}/801636d0_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_801636D0_RESULT)
    if(NOT MUSASHI_SC02_801636D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801636d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80164270.c
                ${MUSASHI_GENERATED_DIR}/80164270_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80164270_RESULT)
    if(NOT MUSASHI_SC02_80164270_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80164270 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801642ac.c
                ${MUSASHI_GENERATED_DIR}/801642ac_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_801642AC_RESULT)
    if(NOT MUSASHI_SC02_801642AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801642ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80164a74.c
                ${MUSASHI_GENERATED_DIR}/80164a74_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80164A74_RESULT)
    if(NOT MUSASHI_SC02_80164A74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80164a74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80164cd4.c
                ${MUSASHI_GENERATED_DIR}/80164cd4_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_80164CD4_RESULT)
    if(NOT MUSASHI_SC02_80164CD4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80164cd4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80164d4c.c
                ${MUSASHI_GENERATED_DIR}/80164d4c_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_80164D4C_RESULT)
    if(NOT MUSASHI_SC02_80164D4C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80164d4c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80164db0.c
                ${MUSASHI_GENERATED_DIR}/80164db0_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80164DB0_RESULT)
    if(NOT MUSASHI_SC02_80164DB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80164db0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80164dd0.c
                ${MUSASHI_GENERATED_DIR}/80164dd0_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_80164DD0_RESULT)
    if(NOT MUSASHI_SC02_80164DD0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80164dd0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165024.c
                ${MUSASHI_GENERATED_DIR}/80165024_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80165024_RESULT)
    if(NOT MUSASHI_SC02_80165024_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165024 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165064.c
                ${MUSASHI_GENERATED_DIR}/80165064_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80165064_RESULT)
    if(NOT MUSASHI_SC02_80165064_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165064 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801650c4.c
                ${MUSASHI_GENERATED_DIR}/801650c4_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_801650C4_RESULT)
    if(NOT MUSASHI_SC02_801650C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801650c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165124.c
                ${MUSASHI_GENERATED_DIR}/80165124_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_80165124_RESULT)
    if(NOT MUSASHI_SC02_80165124_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165124 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165374.c
                ${MUSASHI_GENERATED_DIR}/80165374_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80165374_RESULT)
    if(NOT MUSASHI_SC02_80165374_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165374 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801653b8.c
                ${MUSASHI_GENERATED_DIR}/801653b8_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801653B8_RESULT)
    if(NOT MUSASHI_SC02_801653B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801653b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801655e4.c
                ${MUSASHI_GENERATED_DIR}/801655e4_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801655E4_RESULT)
    if(NOT MUSASHI_SC02_801655E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801655e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165624.c
                ${MUSASHI_GENERATED_DIR}/80165624_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80165624_RESULT)
    if(NOT MUSASHI_SC02_80165624_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165624 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165694.c
                ${MUSASHI_GENERATED_DIR}/80165694_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80165694_RESULT)
    if(NOT MUSASHI_SC02_80165694_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165694 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165770.c
                ${MUSASHI_GENERATED_DIR}/80165770_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80165770_RESULT)
    if(NOT MUSASHI_SC02_80165770_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165770 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801657a0.c
                ${MUSASHI_GENERATED_DIR}/801657a0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801657A0_RESULT)
    if(NOT MUSASHI_SC02_801657A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801657a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801657d8.c
                ${MUSASHI_GENERATED_DIR}/801657d8_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_801657D8_RESULT)
    if(NOT MUSASHI_SC02_801657D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801657d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165840.c
                ${MUSASHI_GENERATED_DIR}/80165840_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80165840_RESULT)
    if(NOT MUSASHI_SC02_80165840_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165840 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165874.c
                ${MUSASHI_GENERATED_DIR}/80165874_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_80165874_RESULT)
    if(NOT MUSASHI_SC02_80165874_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165874 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801658dc.c
                ${MUSASHI_GENERATED_DIR}/801658dc_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_801658DC_RESULT)
    if(NOT MUSASHI_SC02_801658DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801658dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801658ec.c
                ${MUSASHI_GENERATED_DIR}/801658ec_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801658EC_RESULT)
    if(NOT MUSASHI_SC02_801658EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801658ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165900.c
                ${MUSASHI_GENERATED_DIR}/80165900_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80165900_RESULT)
    if(NOT MUSASHI_SC02_80165900_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165900 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165958.c
                ${MUSASHI_GENERATED_DIR}/80165958_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80165958_RESULT)
    if(NOT MUSASHI_SC02_80165958_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165958 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165978.c
                ${MUSASHI_GENERATED_DIR}/80165978_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80165978_RESULT)
    if(NOT MUSASHI_SC02_80165978_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165978 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165988.c
                ${MUSASHI_GENERATED_DIR}/80165988_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80165988_RESULT)
    if(NOT MUSASHI_SC02_80165988_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165988 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801659a8.c
                ${MUSASHI_GENERATED_DIR}/801659a8_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_801659A8_RESULT)
    if(NOT MUSASHI_SC02_801659A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801659a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801659b8.c
                ${MUSASHI_GENERATED_DIR}/801659b8_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801659B8_RESULT)
    if(NOT MUSASHI_SC02_801659B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801659b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801659cc.c
                ${MUSASHI_GENERATED_DIR}/801659cc_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_801659CC_RESULT)
    if(NOT MUSASHI_SC02_801659CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801659cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165a20.c
                ${MUSASHI_GENERATED_DIR}/80165a20_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80165A20_RESULT)
    if(NOT MUSASHI_SC02_80165A20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165a20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165a50.c
                ${MUSASHI_GENERATED_DIR}/80165a50_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80165A50_RESULT)
    if(NOT MUSASHI_SC02_80165A50_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165a50 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165a78.c
                ${MUSASHI_GENERATED_DIR}/80165a78_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80165A78_RESULT)
    if(NOT MUSASHI_SC02_80165A78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165a78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165b6c.c
                ${MUSASHI_GENERATED_DIR}/80165b6c_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80165B6C_RESULT)
    if(NOT MUSASHI_SC02_80165B6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165b6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165bb4.c
                ${MUSASHI_GENERATED_DIR}/80165bb4_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80165BB4_RESULT)
    if(NOT MUSASHI_SC02_80165BB4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165bb4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165bfc.c
                ${MUSASHI_GENERATED_DIR}/80165bfc_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80165BFC_RESULT)
    if(NOT MUSASHI_SC02_80165BFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165bfc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165c58.c
                ${MUSASHI_GENERATED_DIR}/80165c58_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80165C58_RESULT)
    if(NOT MUSASHI_SC02_80165C58_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165c58 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80165fa4.c
                ${MUSASHI_GENERATED_DIR}/80165fa4_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_80165FA4_RESULT)
    if(NOT MUSASHI_SC02_80165FA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80165fa4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801661cc.c
                ${MUSASHI_GENERATED_DIR}/801661cc_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_801661CC_RESULT)
    if(NOT MUSASHI_SC02_801661CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801661cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80166244.c
                ${MUSASHI_GENERATED_DIR}/80166244_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80166244_RESULT)
    if(NOT MUSASHI_SC02_80166244_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80166244 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016629c.c
                ${MUSASHI_GENERATED_DIR}/8016629c_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8016629C_RESULT)
    if(NOT MUSASHI_SC02_8016629C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016629c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801662f4.c
                ${MUSASHI_GENERATED_DIR}/801662f4_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_801662F4_RESULT)
    if(NOT MUSASHI_SC02_801662F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801662f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016634c.c
                ${MUSASHI_GENERATED_DIR}/8016634c_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8016634C_RESULT)
    if(NOT MUSASHI_SC02_8016634C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016634c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801663a4.c
                ${MUSASHI_GENERATED_DIR}/801663a4_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_801663A4_RESULT)
    if(NOT MUSASHI_SC02_801663A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801663a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801665b4.c
                ${MUSASHI_GENERATED_DIR}/801665b4_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_801665B4_RESULT)
    if(NOT MUSASHI_SC02_801665B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801665b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016706c.c
                ${MUSASHI_GENERATED_DIR}/8016706c_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_8016706C_RESULT)
    if(NOT MUSASHI_SC02_8016706C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016706c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016829c.c
                ${MUSASHI_GENERATED_DIR}/8016829c_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_8016829C_RESULT)
    if(NOT MUSASHI_SC02_8016829C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016829c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168328.c
                ${MUSASHI_GENERATED_DIR}/80168328_sc02_0031_words.inc --expected-words 44
        RESULT_VARIABLE MUSASHI_SC02_80168328_RESULT)
    if(NOT MUSASHI_SC02_80168328_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168328 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801683d8.c
                ${MUSASHI_GENERATED_DIR}/801683d8_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_801683D8_RESULT)
    if(NOT MUSASHI_SC02_801683D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801683d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801684b4.c
                ${MUSASHI_GENERATED_DIR}/801684b4_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_801684B4_RESULT)
    if(NOT MUSASHI_SC02_801684B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801684b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168540.c
                ${MUSASHI_GENERATED_DIR}/80168540_sc02_0031_words.inc --expected-words 43
        RESULT_VARIABLE MUSASHI_SC02_80168540_RESULT)
    if(NOT MUSASHI_SC02_80168540_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168540 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801685ec.c
                ${MUSASHI_GENERATED_DIR}/801685ec_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_801685EC_RESULT)
    if(NOT MUSASHI_SC02_801685EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801685ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168640.c
                ${MUSASHI_GENERATED_DIR}/80168640_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80168640_RESULT)
    if(NOT MUSASHI_SC02_80168640_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168640 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168664.c
                ${MUSASHI_GENERATED_DIR}/80168664_sc02_0031_words.inc --expected-words 56
        RESULT_VARIABLE MUSASHI_SC02_80168664_RESULT)
    if(NOT MUSASHI_SC02_80168664_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168664 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168780.c
                ${MUSASHI_GENERATED_DIR}/80168780_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80168780_RESULT)
    if(NOT MUSASHI_SC02_80168780_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168780 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801687cc.c
                ${MUSASHI_GENERATED_DIR}/801687cc_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_801687CC_RESULT)
    if(NOT MUSASHI_SC02_801687CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801687cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168a14.c
                ${MUSASHI_GENERATED_DIR}/80168a14_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_80168A14_RESULT)
    if(NOT MUSASHI_SC02_80168A14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168a14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168a88.c
                ${MUSASHI_GENERATED_DIR}/80168a88_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80168A88_RESULT)
    if(NOT MUSASHI_SC02_80168A88_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168a88 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168ae4.c
                ${MUSASHI_GENERATED_DIR}/80168ae4_sc02_0031_words.inc --expected-words 35
        RESULT_VARIABLE MUSASHI_SC02_80168AE4_RESULT)
    if(NOT MUSASHI_SC02_80168AE4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168ae4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168b70.c
                ${MUSASHI_GENERATED_DIR}/80168b70_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80168B70_RESULT)
    if(NOT MUSASHI_SC02_80168B70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168b70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80168ec4.c
                ${MUSASHI_GENERATED_DIR}/80168ec4_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_80168EC4_RESULT)
    if(NOT MUSASHI_SC02_80168EC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80168ec4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801691b8.c
                ${MUSASHI_GENERATED_DIR}/801691b8_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_801691B8_RESULT)
    if(NOT MUSASHI_SC02_801691B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801691b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016951c.c
                ${MUSASHI_GENERATED_DIR}/8016951c_sc02_0031_words.inc --expected-words 26
        RESULT_VARIABLE MUSASHI_SC02_8016951C_RESULT)
    if(NOT MUSASHI_SC02_8016951C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016951c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801699d0.c
                ${MUSASHI_GENERATED_DIR}/801699d0_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_801699D0_RESULT)
    if(NOT MUSASHI_SC02_801699D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801699d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80169e44.c
                ${MUSASHI_GENERATED_DIR}/80169e44_sc02_0031_words.inc --expected-words 47
        RESULT_VARIABLE MUSASHI_SC02_80169E44_RESULT)
    if(NOT MUSASHI_SC02_80169E44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80169e44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80169fe0.c
                ${MUSASHI_GENERATED_DIR}/80169fe0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80169FE0_RESULT)
    if(NOT MUSASHI_SC02_80169FE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80169fe0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016a05c.c
                ${MUSASHI_GENERATED_DIR}/8016a05c_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016A05C_RESULT)
    if(NOT MUSASHI_SC02_8016A05C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016a05c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016a890.c
                ${MUSASHI_GENERATED_DIR}/8016a890_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8016A890_RESULT)
    if(NOT MUSASHI_SC02_8016A890_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016a890 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016b3f4.c
                ${MUSASHI_GENERATED_DIR}/8016b3f4_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8016B3F4_RESULT)
    if(NOT MUSASHI_SC02_8016B3F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016b3f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016b428.c
                ${MUSASHI_GENERATED_DIR}/8016b428_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8016B428_RESULT)
    if(NOT MUSASHI_SC02_8016B428_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016b428 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016b448.c
                ${MUSASHI_GENERATED_DIR}/8016b448_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_8016B448_RESULT)
    if(NOT MUSASHI_SC02_8016B448_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016b448 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016b91c.c
                ${MUSASHI_GENERATED_DIR}/8016b91c_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8016B91C_RESULT)
    if(NOT MUSASHI_SC02_8016B91C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016b91c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016b964.c
                ${MUSASHI_GENERATED_DIR}/8016b964_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8016B964_RESULT)
    if(NOT MUSASHI_SC02_8016B964_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016b964 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016b984.c
                ${MUSASHI_GENERATED_DIR}/8016b984_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_8016B984_RESULT)
    if(NOT MUSASHI_SC02_8016B984_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016b984 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016ba48.c
                ${MUSASHI_GENERATED_DIR}/8016ba48_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8016BA48_RESULT)
    if(NOT MUSASHI_SC02_8016BA48_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016ba48 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016ba68.c
                ${MUSASHI_GENERATED_DIR}/8016ba68_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_8016BA68_RESULT)
    if(NOT MUSASHI_SC02_8016BA68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016ba68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016badc.c
                ${MUSASHI_GENERATED_DIR}/8016badc_sc02_0031_words.inc --expected-words 50
        RESULT_VARIABLE MUSASHI_SC02_8016BADC_RESULT)
    if(NOT MUSASHI_SC02_8016BADC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016badc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016bf34.c
                ${MUSASHI_GENERATED_DIR}/8016bf34_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_8016BF34_RESULT)
    if(NOT MUSASHI_SC02_8016BF34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016bf34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016bf50.c
                ${MUSASHI_GENERATED_DIR}/8016bf50_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_8016BF50_RESULT)
    if(NOT MUSASHI_SC02_8016BF50_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016bf50 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016d464.c
                ${MUSASHI_GENERATED_DIR}/8016d464_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_8016D464_RESULT)
    if(NOT MUSASHI_SC02_8016D464_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016d464 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016d5ec.c
                ${MUSASHI_GENERATED_DIR}/8016d5ec_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8016D5EC_RESULT)
    if(NOT MUSASHI_SC02_8016D5EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016d5ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016d64c.c
                ${MUSASHI_GENERATED_DIR}/8016d64c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016D64C_RESULT)
    if(NOT MUSASHI_SC02_8016D64C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016d64c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016d984.c
                ${MUSASHI_GENERATED_DIR}/8016d984_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_8016D984_RESULT)
    if(NOT MUSASHI_SC02_8016D984_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016d984 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016da04.c
                ${MUSASHI_GENERATED_DIR}/8016da04_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8016DA04_RESULT)
    if(NOT MUSASHI_SC02_8016DA04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016da04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016db34.c
                ${MUSASHI_GENERATED_DIR}/8016db34_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_8016DB34_RESULT)
    if(NOT MUSASHI_SC02_8016DB34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016db34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016dbd8.c
                ${MUSASHI_GENERATED_DIR}/8016dbd8_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8016DBD8_RESULT)
    if(NOT MUSASHI_SC02_8016DBD8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016dbd8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016dee0.c
                ${MUSASHI_GENERATED_DIR}/8016dee0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8016DEE0_RESULT)
    if(NOT MUSASHI_SC02_8016DEE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016dee0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e1cc.c
                ${MUSASHI_GENERATED_DIR}/8016e1cc_sc02_0031_words.inc --expected-words 40
        RESULT_VARIABLE MUSASHI_SC02_8016E1CC_RESULT)
    if(NOT MUSASHI_SC02_8016E1CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e1cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e26c.c
                ${MUSASHI_GENERATED_DIR}/8016e26c_sc02_0031_words.inc --expected-words 31
        RESULT_VARIABLE MUSASHI_SC02_8016E26C_RESULT)
    if(NOT MUSASHI_SC02_8016E26C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e26c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e2e8.c
                ${MUSASHI_GENERATED_DIR}/8016e2e8_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_8016E2E8_RESULT)
    if(NOT MUSASHI_SC02_8016E2E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e2e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e358.c
                ${MUSASHI_GENERATED_DIR}/8016e358_sc02_0031_words.inc --expected-words 29
        RESULT_VARIABLE MUSASHI_SC02_8016E358_RESULT)
    if(NOT MUSASHI_SC02_8016E358_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e358 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e3cc.c
                ${MUSASHI_GENERATED_DIR}/8016e3cc_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_8016E3CC_RESULT)
    if(NOT MUSASHI_SC02_8016E3CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e3cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e5f4.c
                ${MUSASHI_GENERATED_DIR}/8016e5f4_sc02_0031_words.inc --expected-words 37
        RESULT_VARIABLE MUSASHI_SC02_8016E5F4_RESULT)
    if(NOT MUSASHI_SC02_8016E5F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e5f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e688.c
                ${MUSASHI_GENERATED_DIR}/8016e688_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_8016E688_RESULT)
    if(NOT MUSASHI_SC02_8016E688_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e688 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e6e4.c
                ${MUSASHI_GENERATED_DIR}/8016e6e4_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8016E6E4_RESULT)
    if(NOT MUSASHI_SC02_8016E6E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e6e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e728.c
                ${MUSASHI_GENERATED_DIR}/8016e728_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8016E728_RESULT)
    if(NOT MUSASHI_SC02_8016E728_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e728 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016e778.c
                ${MUSASHI_GENERATED_DIR}/8016e778_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8016E778_RESULT)
    if(NOT MUSASHI_SC02_8016E778_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016e778 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016ed6c.c
                ${MUSASHI_GENERATED_DIR}/8016ed6c_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8016ED6C_RESULT)
    if(NOT MUSASHI_SC02_8016ED6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016ed6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016ed8c.c
                ${MUSASHI_GENERATED_DIR}/8016ed8c_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016ED8C_RESULT)
    if(NOT MUSASHI_SC02_8016ED8C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016ed8c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016edbc.c
                ${MUSASHI_GENERATED_DIR}/8016edbc_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016EDBC_RESULT)
    if(NOT MUSASHI_SC02_8016EDBC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016edbc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016edec.c
                ${MUSASHI_GENERATED_DIR}/8016edec_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8016EDEC_RESULT)
    if(NOT MUSASHI_SC02_8016EDEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016edec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016efa8.c
                ${MUSASHI_GENERATED_DIR}/8016efa8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8016EFA8_RESULT)
    if(NOT MUSASHI_SC02_8016EFA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016efa8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f094.c
                ${MUSASHI_GENERATED_DIR}/8016f094_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_8016F094_RESULT)
    if(NOT MUSASHI_SC02_8016F094_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f094 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f0ac.c
                ${MUSASHI_GENERATED_DIR}/8016f0ac_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8016F0AC_RESULT)
    if(NOT MUSASHI_SC02_8016F0AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f0ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f1ac.c
                ${MUSASHI_GENERATED_DIR}/8016f1ac_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_8016F1AC_RESULT)
    if(NOT MUSASHI_SC02_8016F1AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f1ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f250.c
                ${MUSASHI_GENERATED_DIR}/8016f250_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8016F250_RESULT)
    if(NOT MUSASHI_SC02_8016F250_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f250 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f264.c
                ${MUSASHI_GENERATED_DIR}/8016f264_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8016F264_RESULT)
    if(NOT MUSASHI_SC02_8016F264_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f264 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f288.c
                ${MUSASHI_GENERATED_DIR}/8016f288_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8016F288_RESULT)
    if(NOT MUSASHI_SC02_8016F288_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f288 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f2a8.c
                ${MUSASHI_GENERATED_DIR}/8016f2a8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8016F2A8_RESULT)
    if(NOT MUSASHI_SC02_8016F2A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f2a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f2c8.c
                ${MUSASHI_GENERATED_DIR}/8016f2c8_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8016F2C8_RESULT)
    if(NOT MUSASHI_SC02_8016F2C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f2c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f2ec.c
                ${MUSASHI_GENERATED_DIR}/8016f2ec_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8016F2EC_RESULT)
    if(NOT MUSASHI_SC02_8016F2EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f2ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f30c.c
                ${MUSASHI_GENERATED_DIR}/8016f30c_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8016F30C_RESULT)
    if(NOT MUSASHI_SC02_8016F30C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f30c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f330.c
                ${MUSASHI_GENERATED_DIR}/8016f330_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8016F330_RESULT)
    if(NOT MUSASHI_SC02_8016F330_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f330 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f350.c
                ${MUSASHI_GENERATED_DIR}/8016f350_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8016F350_RESULT)
    if(NOT MUSASHI_SC02_8016F350_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f350 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f374.c
                ${MUSASHI_GENERATED_DIR}/8016f374_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8016F374_RESULT)
    if(NOT MUSASHI_SC02_8016F374_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f374 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f388.c
                ${MUSASHI_GENERATED_DIR}/8016f388_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8016F388_RESULT)
    if(NOT MUSASHI_SC02_8016F388_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f388 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f398.c
                ${MUSASHI_GENERATED_DIR}/8016f398_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_8016F398_RESULT)
    if(NOT MUSASHI_SC02_8016F398_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f398 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f410.c
                ${MUSASHI_GENERATED_DIR}/8016f410_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016F410_RESULT)
    if(NOT MUSASHI_SC02_8016F410_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f410 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f44c.c
                ${MUSASHI_GENERATED_DIR}/8016f44c_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8016F44C_RESULT)
    if(NOT MUSASHI_SC02_8016F44C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f44c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f470.c
                ${MUSASHI_GENERATED_DIR}/8016f470_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8016F470_RESULT)
    if(NOT MUSASHI_SC02_8016F470_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f470 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f494.c
                ${MUSASHI_GENERATED_DIR}/8016f494_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016F494_RESULT)
    if(NOT MUSASHI_SC02_8016F494_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f494 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f4c4.c
                ${MUSASHI_GENERATED_DIR}/8016f4c4_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016F4C4_RESULT)
    if(NOT MUSASHI_SC02_8016F4C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f4c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f4fc.c
                ${MUSASHI_GENERATED_DIR}/8016f4fc_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8016F4FC_RESULT)
    if(NOT MUSASHI_SC02_8016F4FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f4fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f540.c
                ${MUSASHI_GENERATED_DIR}/8016f540_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8016F540_RESULT)
    if(NOT MUSASHI_SC02_8016F540_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f540 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f578.c
                ${MUSASHI_GENERATED_DIR}/8016f578_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8016F578_RESULT)
    if(NOT MUSASHI_SC02_8016F578_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f578 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f5b0.c
                ${MUSASHI_GENERATED_DIR}/8016f5b0_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016F5B0_RESULT)
    if(NOT MUSASHI_SC02_8016F5B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f5b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f5e0.c
                ${MUSASHI_GENERATED_DIR}/8016f5e0_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016F5E0_RESULT)
    if(NOT MUSASHI_SC02_8016F5E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f5e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f610.c
                ${MUSASHI_GENERATED_DIR}/8016f610_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8016F610_RESULT)
    if(NOT MUSASHI_SC02_8016F610_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f610 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f648.c
                ${MUSASHI_GENERATED_DIR}/8016f648_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8016F648_RESULT)
    if(NOT MUSASHI_SC02_8016F648_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f648 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f680.c
                ${MUSASHI_GENERATED_DIR}/8016f680_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016F680_RESULT)
    if(NOT MUSASHI_SC02_8016F680_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f680 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f6b0.c
                ${MUSASHI_GENERATED_DIR}/8016f6b0_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016F6B0_RESULT)
    if(NOT MUSASHI_SC02_8016F6B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f6b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f71c.c
                ${MUSASHI_GENERATED_DIR}/8016f71c_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_8016F71C_RESULT)
    if(NOT MUSASHI_SC02_8016F71C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f71c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f764.c
                ${MUSASHI_GENERATED_DIR}/8016f764_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8016F764_RESULT)
    if(NOT MUSASHI_SC02_8016F764_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f764 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f7d4.c
                ${MUSASHI_GENERATED_DIR}/8016f7d4_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016F7D4_RESULT)
    if(NOT MUSASHI_SC02_8016F7D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f7d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f804.c
                ${MUSASHI_GENERATED_DIR}/8016f804_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016F804_RESULT)
    if(NOT MUSASHI_SC02_8016F804_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f804 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f870.c
                ${MUSASHI_GENERATED_DIR}/8016f870_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016F870_RESULT)
    if(NOT MUSASHI_SC02_8016F870_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f870 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f8ac.c
                ${MUSASHI_GENERATED_DIR}/8016f8ac_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8016F8AC_RESULT)
    if(NOT MUSASHI_SC02_8016F8AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f8ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016f920.c
                ${MUSASHI_GENERATED_DIR}/8016f920_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016F920_RESULT)
    if(NOT MUSASHI_SC02_8016F920_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016f920 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fa00.c
                ${MUSASHI_GENERATED_DIR}/8016fa00_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_8016FA00_RESULT)
    if(NOT MUSASHI_SC02_8016FA00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fa00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fa44.c
                ${MUSASHI_GENERATED_DIR}/8016fa44_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8016FA44_RESULT)
    if(NOT MUSASHI_SC02_8016FA44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fa44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fac0.c
                ${MUSASHI_GENERATED_DIR}/8016fac0_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_8016FAC0_RESULT)
    if(NOT MUSASHI_SC02_8016FAC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fac0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fb10.c
                ${MUSASHI_GENERATED_DIR}/8016fb10_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8016FB10_RESULT)
    if(NOT MUSASHI_SC02_8016FB10_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fb10 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fb50.c
                ${MUSASHI_GENERATED_DIR}/8016fb50_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8016FB50_RESULT)
    if(NOT MUSASHI_SC02_8016FB50_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fb50 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fbb8.c
                ${MUSASHI_GENERATED_DIR}/8016fbb8_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_8016FBB8_RESULT)
    if(NOT MUSASHI_SC02_8016FBB8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fbb8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fc24.c
                ${MUSASHI_GENERATED_DIR}/8016fc24_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_8016FC24_RESULT)
    if(NOT MUSASHI_SC02_8016FC24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fc24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fc64.c
                ${MUSASHI_GENERATED_DIR}/8016fc64_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8016FC64_RESULT)
    if(NOT MUSASHI_SC02_8016FC64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fc64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fccc.c
                ${MUSASHI_GENERATED_DIR}/8016fccc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016FCCC_RESULT)
    if(NOT MUSASHI_SC02_8016FCCC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fccc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fd7c.c
                ${MUSASHI_GENERATED_DIR}/8016fd7c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8016FD7C_RESULT)
    if(NOT MUSASHI_SC02_8016FD7C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fd7c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fdf0.c
                ${MUSASHI_GENERATED_DIR}/8016fdf0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016FDF0_RESULT)
    if(NOT MUSASHI_SC02_8016FDF0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fdf0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fe2c.c
                ${MUSASHI_GENERATED_DIR}/8016fe2c_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_8016FE2C_RESULT)
    if(NOT MUSASHI_SC02_8016FE2C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fe2c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016fed0.c
                ${MUSASHI_GENERATED_DIR}/8016fed0_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8016FED0_RESULT)
    if(NOT MUSASHI_SC02_8016FED0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016fed0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016ff6c.c
                ${MUSASHI_GENERATED_DIR}/8016ff6c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8016FF6C_RESULT)
    if(NOT MUSASHI_SC02_8016FF6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016ff6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016ffa8.c
                ${MUSASHI_GENERATED_DIR}/8016ffa8_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8016FFA8_RESULT)
    if(NOT MUSASHI_SC02_8016FFA8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016ffa8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170018.c
                ${MUSASHI_GENERATED_DIR}/80170018_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80170018_RESULT)
    if(NOT MUSASHI_SC02_80170018_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170018 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170068.c
                ${MUSASHI_GENERATED_DIR}/80170068_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80170068_RESULT)
    if(NOT MUSASHI_SC02_80170068_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170068 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801700b8.c
                ${MUSASHI_GENERATED_DIR}/801700b8_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_801700B8_RESULT)
    if(NOT MUSASHI_SC02_801700B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801700b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170100.c
                ${MUSASHI_GENERATED_DIR}/80170100_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80170100_RESULT)
    if(NOT MUSASHI_SC02_80170100_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170100 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017018c.c
                ${MUSASHI_GENERATED_DIR}/8017018c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017018C_RESULT)
    if(NOT MUSASHI_SC02_8017018C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017018c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801701c8.c
                ${MUSASHI_GENERATED_DIR}/801701c8_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_801701C8_RESULT)
    if(NOT MUSASHI_SC02_801701C8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801701c8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017027c.c
                ${MUSASHI_GENERATED_DIR}/8017027c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017027C_RESULT)
    if(NOT MUSASHI_SC02_8017027C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017027c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801702b8.c
                ${MUSASHI_GENERATED_DIR}/801702b8_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_801702B8_RESULT)
    if(NOT MUSASHI_SC02_801702B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801702b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170338.c
                ${MUSASHI_GENERATED_DIR}/80170338_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170338_RESULT)
    if(NOT MUSASHI_SC02_80170338_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170338 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170374.c
                ${MUSASHI_GENERATED_DIR}/80170374_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80170374_RESULT)
    if(NOT MUSASHI_SC02_80170374_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170374 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017041c.c
                ${MUSASHI_GENERATED_DIR}/8017041c_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8017041C_RESULT)
    if(NOT MUSASHI_SC02_8017041C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017041c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017044c.c
                ${MUSASHI_GENERATED_DIR}/8017044c_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_8017044C_RESULT)
    if(NOT MUSASHI_SC02_8017044C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017044c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801704ec.c
                ${MUSASHI_GENERATED_DIR}/801704ec_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801704EC_RESULT)
    if(NOT MUSASHI_SC02_801704EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801704ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017051c.c
                ${MUSASHI_GENERATED_DIR}/8017051c_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_8017051C_RESULT)
    if(NOT MUSASHI_SC02_8017051C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017051c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170584.c
                ${MUSASHI_GENERATED_DIR}/80170584_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170584_RESULT)
    if(NOT MUSASHI_SC02_80170584_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170584 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801705c0.c
                ${MUSASHI_GENERATED_DIR}/801705c0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801705C0_RESULT)
    if(NOT MUSASHI_SC02_801705C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801705c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170634.c
                ${MUSASHI_GENERATED_DIR}/80170634_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170634_RESULT)
    if(NOT MUSASHI_SC02_80170634_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170634 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170670.c
                ${MUSASHI_GENERATED_DIR}/80170670_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170670_RESULT)
    if(NOT MUSASHI_SC02_80170670_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170670 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801706e8.c
                ${MUSASHI_GENERATED_DIR}/801706e8_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801706E8_RESULT)
    if(NOT MUSASHI_SC02_801706E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801706e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170718.c
                ${MUSASHI_GENERATED_DIR}/80170718_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80170718_RESULT)
    if(NOT MUSASHI_SC02_80170718_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170718 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170784.c
                ${MUSASHI_GENERATED_DIR}/80170784_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80170784_RESULT)
    if(NOT MUSASHI_SC02_80170784_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170784 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801707d4.c
                ${MUSASHI_GENERATED_DIR}/801707d4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801707D4_RESULT)
    if(NOT MUSASHI_SC02_801707D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801707d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017084c.c
                ${MUSASHI_GENERATED_DIR}/8017084c_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_8017084C_RESULT)
    if(NOT MUSASHI_SC02_8017084C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017084c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801708b0.c
                ${MUSASHI_GENERATED_DIR}/801708b0_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_801708B0_RESULT)
    if(NOT MUSASHI_SC02_801708B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801708b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170928.c
                ${MUSASHI_GENERATED_DIR}/80170928_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80170928_RESULT)
    if(NOT MUSASHI_SC02_80170928_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170928 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170970.c
                ${MUSASHI_GENERATED_DIR}/80170970_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80170970_RESULT)
    if(NOT MUSASHI_SC02_80170970_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170970 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801709b8.c
                ${MUSASHI_GENERATED_DIR}/801709b8_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_801709B8_RESULT)
    if(NOT MUSASHI_SC02_801709B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801709b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170a00.c
                ${MUSASHI_GENERATED_DIR}/80170a00_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80170A00_RESULT)
    if(NOT MUSASHI_SC02_80170A00_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170a00 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170a48.c
                ${MUSASHI_GENERATED_DIR}/80170a48_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80170A48_RESULT)
    if(NOT MUSASHI_SC02_80170A48_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170a48 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170a90.c
                ${MUSASHI_GENERATED_DIR}/80170a90_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80170A90_RESULT)
    if(NOT MUSASHI_SC02_80170A90_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170a90 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170b14.c
                ${MUSASHI_GENERATED_DIR}/80170b14_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80170B14_RESULT)
    if(NOT MUSASHI_SC02_80170B14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170b14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170b48.c
                ${MUSASHI_GENERATED_DIR}/80170b48_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80170B48_RESULT)
    if(NOT MUSASHI_SC02_80170B48_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170b48 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170b90.c
                ${MUSASHI_GENERATED_DIR}/80170b90_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80170B90_RESULT)
    if(NOT MUSASHI_SC02_80170B90_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170b90 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170c14.c
                ${MUSASHI_GENERATED_DIR}/80170c14_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80170C14_RESULT)
    if(NOT MUSASHI_SC02_80170C14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170c14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170c44.c
                ${MUSASHI_GENERATED_DIR}/80170c44_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80170C44_RESULT)
    if(NOT MUSASHI_SC02_80170C44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170c44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170cb0.c
                ${MUSASHI_GENERATED_DIR}/80170cb0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80170CB0_RESULT)
    if(NOT MUSASHI_SC02_80170CB0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170cb0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170da4.c
                ${MUSASHI_GENERATED_DIR}/80170da4_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170DA4_RESULT)
    if(NOT MUSASHI_SC02_80170DA4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170da4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170de0.c
                ${MUSASHI_GENERATED_DIR}/80170de0_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80170DE0_RESULT)
    if(NOT MUSASHI_SC02_80170DE0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170de0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170e70.c
                ${MUSASHI_GENERATED_DIR}/80170e70_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170E70_RESULT)
    if(NOT MUSASHI_SC02_80170E70_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170e70 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170eac.c
                ${MUSASHI_GENERATED_DIR}/80170eac_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80170EAC_RESULT)
    if(NOT MUSASHI_SC02_80170EAC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170eac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170f38.c
                ${MUSASHI_GENERATED_DIR}/80170f38_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170F38_RESULT)
    if(NOT MUSASHI_SC02_80170F38_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170f38 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170f74.c
                ${MUSASHI_GENERATED_DIR}/80170f74_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170F74_RESULT)
    if(NOT MUSASHI_SC02_80170F74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170f74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80170fec.c
                ${MUSASHI_GENERATED_DIR}/80170fec_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80170FEC_RESULT)
    if(NOT MUSASHI_SC02_80170FEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80170fec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171028.c
                ${MUSASHI_GENERATED_DIR}/80171028_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80171028_RESULT)
    if(NOT MUSASHI_SC02_80171028_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171028 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801710a0.c
                ${MUSASHI_GENERATED_DIR}/801710a0_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801710A0_RESULT)
    if(NOT MUSASHI_SC02_801710A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801710a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801710dc.c
                ${MUSASHI_GENERATED_DIR}/801710dc_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_801710DC_RESULT)
    if(NOT MUSASHI_SC02_801710DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801710dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017115c.c
                ${MUSASHI_GENERATED_DIR}/8017115c_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8017115C_RESULT)
    if(NOT MUSASHI_SC02_8017115C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017115c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017118c.c
                ${MUSASHI_GENERATED_DIR}/8017118c_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_8017118C_RESULT)
    if(NOT MUSASHI_SC02_8017118C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017118c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801711fc.c
                ${MUSASHI_GENERATED_DIR}/801711fc_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_801711FC_RESULT)
    if(NOT MUSASHI_SC02_801711FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801711fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171238.c
                ${MUSASHI_GENERATED_DIR}/80171238_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80171238_RESULT)
    if(NOT MUSASHI_SC02_80171238_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171238 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017162c.c
                ${MUSASHI_GENERATED_DIR}/8017162c_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_8017162C_RESULT)
    if(NOT MUSASHI_SC02_8017162C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017162c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801717f4.c
                ${MUSASHI_GENERATED_DIR}/801717f4_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801717F4_RESULT)
    if(NOT MUSASHI_SC02_801717F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801717f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171824.c
                ${MUSASHI_GENERATED_DIR}/80171824_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80171824_RESULT)
    if(NOT MUSASHI_SC02_80171824_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171824 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171854.c
                ${MUSASHI_GENERATED_DIR}/80171854_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80171854_RESULT)
    if(NOT MUSASHI_SC02_80171854_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171854 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171884.c
                ${MUSASHI_GENERATED_DIR}/80171884_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80171884_RESULT)
    if(NOT MUSASHI_SC02_80171884_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171884 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801718ac.c
                ${MUSASHI_GENERATED_DIR}/801718ac_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_801718AC_RESULT)
    if(NOT MUSASHI_SC02_801718AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801718ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171904.c
                ${MUSASHI_GENERATED_DIR}/80171904_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80171904_RESULT)
    if(NOT MUSASHI_SC02_80171904_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171904 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171928.c
                ${MUSASHI_GENERATED_DIR}/80171928_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80171928_RESULT)
    if(NOT MUSASHI_SC02_80171928_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171928 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017196c.c
                ${MUSASHI_GENERATED_DIR}/8017196c_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_8017196C_RESULT)
    if(NOT MUSASHI_SC02_8017196C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017196c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017197c.c
                ${MUSASHI_GENERATED_DIR}/8017197c_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8017197C_RESULT)
    if(NOT MUSASHI_SC02_8017197C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017197c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171990.c
                ${MUSASHI_GENERATED_DIR}/80171990_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80171990_RESULT)
    if(NOT MUSASHI_SC02_80171990_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171990 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171a04.c
                ${MUSASHI_GENERATED_DIR}/80171a04_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80171A04_RESULT)
    if(NOT MUSASHI_SC02_80171A04_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171a04 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171a10.c
                ${MUSASHI_GENERATED_DIR}/80171a10_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80171A10_RESULT)
    if(NOT MUSASHI_SC02_80171A10_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171a10 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171a1c.c
                ${MUSASHI_GENERATED_DIR}/80171a1c_sc02_0031_words.inc --expected-words 6
        RESULT_VARIABLE MUSASHI_SC02_80171A1C_RESULT)
    if(NOT MUSASHI_SC02_80171A1C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171a1c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171a34.c
                ${MUSASHI_GENERATED_DIR}/80171a34_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80171A34_RESULT)
    if(NOT MUSASHI_SC02_80171A34_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171a34 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171a44.c
                ${MUSASHI_GENERATED_DIR}/80171a44_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80171A44_RESULT)
    if(NOT MUSASHI_SC02_80171A44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171a44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171a58.c
                ${MUSASHI_GENERATED_DIR}/80171a58_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80171A58_RESULT)
    if(NOT MUSASHI_SC02_80171A58_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171a58 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171a6c.c
                ${MUSASHI_GENERATED_DIR}/80171a6c_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80171A6C_RESULT)
    if(NOT MUSASHI_SC02_80171A6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171a6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171b10.c
                ${MUSASHI_GENERATED_DIR}/80171b10_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80171B10_RESULT)
    if(NOT MUSASHI_SC02_80171B10_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171b10 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171b44.c
                ${MUSASHI_GENERATED_DIR}/80171b44_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80171B44_RESULT)
    if(NOT MUSASHI_SC02_80171B44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171b44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171c64.c
                ${MUSASHI_GENERATED_DIR}/80171c64_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80171C64_RESULT)
    if(NOT MUSASHI_SC02_80171C64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171c64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171cc4.c
                ${MUSASHI_GENERATED_DIR}/80171cc4_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80171CC4_RESULT)
    if(NOT MUSASHI_SC02_80171CC4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171cc4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80171d1c.c
                ${MUSASHI_GENERATED_DIR}/80171d1c_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80171D1C_RESULT)
    if(NOT MUSASHI_SC02_80171D1C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80171d1c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801722cc.c
                ${MUSASHI_GENERATED_DIR}/801722cc_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801722CC_RESULT)
    if(NOT MUSASHI_SC02_801722CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801722cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172310.c
                ${MUSASHI_GENERATED_DIR}/80172310_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80172310_RESULT)
    if(NOT MUSASHI_SC02_80172310_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172310 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172358.c
                ${MUSASHI_GENERATED_DIR}/80172358_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80172358_RESULT)
    if(NOT MUSASHI_SC02_80172358_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172358 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801723c4.c
                ${MUSASHI_GENERATED_DIR}/801723c4_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_801723C4_RESULT)
    if(NOT MUSASHI_SC02_801723C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801723c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172414.c
                ${MUSASHI_GENERATED_DIR}/80172414_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_80172414_RESULT)
    if(NOT MUSASHI_SC02_80172414_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172414 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017248c.c
                ${MUSASHI_GENERATED_DIR}/8017248c_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_8017248C_RESULT)
    if(NOT MUSASHI_SC02_8017248C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017248c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801724ec.c
                ${MUSASHI_GENERATED_DIR}/801724ec_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801724EC_RESULT)
    if(NOT MUSASHI_SC02_801724EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801724ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017250c.c
                ${MUSASHI_GENERATED_DIR}/8017250c_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8017250C_RESULT)
    if(NOT MUSASHI_SC02_8017250C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017250c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172560.c
                ${MUSASHI_GENERATED_DIR}/80172560_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80172560_RESULT)
    if(NOT MUSASHI_SC02_80172560_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172560 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172588.c
                ${MUSASHI_GENERATED_DIR}/80172588_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_80172588_RESULT)
    if(NOT MUSASHI_SC02_80172588_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172588 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172590.c
                ${MUSASHI_GENERATED_DIR}/80172590_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80172590_RESULT)
    if(NOT MUSASHI_SC02_80172590_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172590 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801725a4.c
                ${MUSASHI_GENERATED_DIR}/801725a4_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801725A4_RESULT)
    if(NOT MUSASHI_SC02_801725A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801725a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801725b8.c
                ${MUSASHI_GENERATED_DIR}/801725b8_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801725B8_RESULT)
    if(NOT MUSASHI_SC02_801725B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801725b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801725cc.c
                ${MUSASHI_GENERATED_DIR}/801725cc_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801725CC_RESULT)
    if(NOT MUSASHI_SC02_801725CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801725cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801725e0.c
                ${MUSASHI_GENERATED_DIR}/801725e0_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801725E0_RESULT)
    if(NOT MUSASHI_SC02_801725E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801725e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801725f4.c
                ${MUSASHI_GENERATED_DIR}/801725f4_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_801725F4_RESULT)
    if(NOT MUSASHI_SC02_801725F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801725f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172608.c
                ${MUSASHI_GENERATED_DIR}/80172608_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80172608_RESULT)
    if(NOT MUSASHI_SC02_80172608_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172608 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017261c.c
                ${MUSASHI_GENERATED_DIR}/8017261c_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_8017261C_RESULT)
    if(NOT MUSASHI_SC02_8017261C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017261c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172630.c
                ${MUSASHI_GENERATED_DIR}/80172630_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80172630_RESULT)
    if(NOT MUSASHI_SC02_80172630_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172630 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172644.c
                ${MUSASHI_GENERATED_DIR}/80172644_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80172644_RESULT)
    if(NOT MUSASHI_SC02_80172644_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172644 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172658.c
                ${MUSASHI_GENERATED_DIR}/80172658_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80172658_RESULT)
    if(NOT MUSASHI_SC02_80172658_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172658 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172664.c
                ${MUSASHI_GENERATED_DIR}/80172664_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80172664_RESULT)
    if(NOT MUSASHI_SC02_80172664_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172664 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172670.c
                ${MUSASHI_GENERATED_DIR}/80172670_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80172670_RESULT)
    if(NOT MUSASHI_SC02_80172670_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172670 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017267c.c
                ${MUSASHI_GENERATED_DIR}/8017267c_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_8017267C_RESULT)
    if(NOT MUSASHI_SC02_8017267C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017267c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172688.c
                ${MUSASHI_GENERATED_DIR}/80172688_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80172688_RESULT)
    if(NOT MUSASHI_SC02_80172688_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172688 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172694.c
                ${MUSASHI_GENERATED_DIR}/80172694_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_80172694_RESULT)
    if(NOT MUSASHI_SC02_80172694_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172694 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801726a0.c
                ${MUSASHI_GENERATED_DIR}/801726a0_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_801726A0_RESULT)
    if(NOT MUSASHI_SC02_801726A0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801726a0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801726ac.c
                ${MUSASHI_GENERATED_DIR}/801726ac_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_801726AC_RESULT)
    if(NOT MUSASHI_SC02_801726AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801726ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801726b8.c
                ${MUSASHI_GENERATED_DIR}/801726b8_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_801726B8_RESULT)
    if(NOT MUSASHI_SC02_801726B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801726b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801726c4.c
                ${MUSASHI_GENERATED_DIR}/801726c4_sc02_0031_words.inc --expected-words 3
        RESULT_VARIABLE MUSASHI_SC02_801726C4_RESULT)
    if(NOT MUSASHI_SC02_801726C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801726c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172710.c
                ${MUSASHI_GENERATED_DIR}/80172710_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80172710_RESULT)
    if(NOT MUSASHI_SC02_80172710_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172710 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172738.c
                ${MUSASHI_GENERATED_DIR}/80172738_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80172738_RESULT)
    if(NOT MUSASHI_SC02_80172738_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172738 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172760.c
                ${MUSASHI_GENERATED_DIR}/80172760_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80172760_RESULT)
    if(NOT MUSASHI_SC02_80172760_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172760 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172780.c
                ${MUSASHI_GENERATED_DIR}/80172780_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80172780_RESULT)
    if(NOT MUSASHI_SC02_80172780_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172780 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017280c.c
                ${MUSASHI_GENERATED_DIR}/8017280c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_8017280C_RESULT)
    if(NOT MUSASHI_SC02_8017280C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017280c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172844.c
                ${MUSASHI_GENERATED_DIR}/80172844_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80172844_RESULT)
    if(NOT MUSASHI_SC02_80172844_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172844 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172894.c
                ${MUSASHI_GENERATED_DIR}/80172894_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80172894_RESULT)
    if(NOT MUSASHI_SC02_80172894_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172894 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172920.c
                ${MUSASHI_GENERATED_DIR}/80172920_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80172920_RESULT)
    if(NOT MUSASHI_SC02_80172920_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172920 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172958.c
                ${MUSASHI_GENERATED_DIR}/80172958_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80172958_RESULT)
    if(NOT MUSASHI_SC02_80172958_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172958 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801729b0.c
                ${MUSASHI_GENERATED_DIR}/801729b0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801729B0_RESULT)
    if(NOT MUSASHI_SC02_801729B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801729b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172a2c.c
                ${MUSASHI_GENERATED_DIR}/80172a2c_sc02_0031_words.inc --expected-words 24
        RESULT_VARIABLE MUSASHI_SC02_80172A2C_RESULT)
    if(NOT MUSASHI_SC02_80172A2C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172a2c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172a8c.c
                ${MUSASHI_GENERATED_DIR}/80172a8c_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80172A8C_RESULT)
    if(NOT MUSASHI_SC02_80172A8C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172a8c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172acc.c
                ${MUSASHI_GENERATED_DIR}/80172acc_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80172ACC_RESULT)
    if(NOT MUSASHI_SC02_80172ACC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172acc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172b14.c
                ${MUSASHI_GENERATED_DIR}/80172b14_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80172B14_RESULT)
    if(NOT MUSASHI_SC02_80172B14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172b14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172b80.c
                ${MUSASHI_GENERATED_DIR}/80172b80_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80172B80_RESULT)
    if(NOT MUSASHI_SC02_80172B80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172b80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172bc8.c
                ${MUSASHI_GENERATED_DIR}/80172bc8_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_80172BC8_RESULT)
    if(NOT MUSASHI_SC02_80172BC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172bc8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172c50.c
                ${MUSASHI_GENERATED_DIR}/80172c50_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80172C50_RESULT)
    if(NOT MUSASHI_SC02_80172C50_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172c50 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172cdc.c
                ${MUSASHI_GENERATED_DIR}/80172cdc_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80172CDC_RESULT)
    if(NOT MUSASHI_SC02_80172CDC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172cdc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172d14.c
                ${MUSASHI_GENERATED_DIR}/80172d14_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80172D14_RESULT)
    if(NOT MUSASHI_SC02_80172D14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172d14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172d68.c
                ${MUSASHI_GENERATED_DIR}/80172d68_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80172D68_RESULT)
    if(NOT MUSASHI_SC02_80172D68_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172d68 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172de8.c
                ${MUSASHI_GENERATED_DIR}/80172de8_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80172DE8_RESULT)
    if(NOT MUSASHI_SC02_80172DE8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172de8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172e20.c
                ${MUSASHI_GENERATED_DIR}/80172e20_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_80172E20_RESULT)
    if(NOT MUSASHI_SC02_80172E20_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172e20 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172e94.c
                ${MUSASHI_GENERATED_DIR}/80172e94_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80172E94_RESULT)
    if(NOT MUSASHI_SC02_80172E94_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172e94 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172ed4.c
                ${MUSASHI_GENERATED_DIR}/80172ed4_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80172ED4_RESULT)
    if(NOT MUSASHI_SC02_80172ED4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172ed4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172efc.c
                ${MUSASHI_GENERATED_DIR}/80172efc_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80172EFC_RESULT)
    if(NOT MUSASHI_SC02_80172EFC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172efc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172f24.c
                ${MUSASHI_GENERATED_DIR}/80172f24_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80172F24_RESULT)
    if(NOT MUSASHI_SC02_80172F24_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172f24 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172f4c.c
                ${MUSASHI_GENERATED_DIR}/80172f4c_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80172F4C_RESULT)
    if(NOT MUSASHI_SC02_80172F4C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172f4c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172f9c.c
                ${MUSASHI_GENERATED_DIR}/80172f9c_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80172F9C_RESULT)
    if(NOT MUSASHI_SC02_80172F9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172f9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80172fec.c
                ${MUSASHI_GENERATED_DIR}/80172fec_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80172FEC_RESULT)
    if(NOT MUSASHI_SC02_80172FEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80172fec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017303c.c
                ${MUSASHI_GENERATED_DIR}/8017303c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017303C_RESULT)
    if(NOT MUSASHI_SC02_8017303C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017303c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801730b4.c
                ${MUSASHI_GENERATED_DIR}/801730b4_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_801730B4_RESULT)
    if(NOT MUSASHI_SC02_801730B4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801730b4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801730fc.c
                ${MUSASHI_GENERATED_DIR}/801730fc_sc02_0031_words.inc --expected-words 28
        RESULT_VARIABLE MUSASHI_SC02_801730FC_RESULT)
    if(NOT MUSASHI_SC02_801730FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801730fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173174.c
                ${MUSASHI_GENERATED_DIR}/80173174_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80173174_RESULT)
    if(NOT MUSASHI_SC02_80173174_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173174 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801731d8.c
                ${MUSASHI_GENERATED_DIR}/801731d8_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_801731D8_RESULT)
    if(NOT MUSASHI_SC02_801731D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801731d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017329c.c
                ${MUSASHI_GENERATED_DIR}/8017329c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017329C_RESULT)
    if(NOT MUSASHI_SC02_8017329C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017329c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801732c4.c
                ${MUSASHI_GENERATED_DIR}/801732c4_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801732C4_RESULT)
    if(NOT MUSASHI_SC02_801732C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801732c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801732f4.c
                ${MUSASHI_GENERATED_DIR}/801732f4_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_801732F4_RESULT)
    if(NOT MUSASHI_SC02_801732F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801732f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017331c.c
                ${MUSASHI_GENERATED_DIR}/8017331c_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8017331C_RESULT)
    if(NOT MUSASHI_SC02_8017331C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017331c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017334c.c
                ${MUSASHI_GENERATED_DIR}/8017334c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017334C_RESULT)
    if(NOT MUSASHI_SC02_8017334C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017334c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173374.c
                ${MUSASHI_GENERATED_DIR}/80173374_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80173374_RESULT)
    if(NOT MUSASHI_SC02_80173374_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173374 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801733a4.c
                ${MUSASHI_GENERATED_DIR}/801733a4_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_801733A4_RESULT)
    if(NOT MUSASHI_SC02_801733A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801733a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801733cc.c
                ${MUSASHI_GENERATED_DIR}/801733cc_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801733CC_RESULT)
    if(NOT MUSASHI_SC02_801733CC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801733cc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801733fc.c
                ${MUSASHI_GENERATED_DIR}/801733fc_sc02_0031_words.inc --expected-words 25
        RESULT_VARIABLE MUSASHI_SC02_801733FC_RESULT)
    if(NOT MUSASHI_SC02_801733FC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801733fc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173460.c
                ${MUSASHI_GENERATED_DIR}/80173460_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_80173460_RESULT)
    if(NOT MUSASHI_SC02_80173460_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173460 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173580.c
                ${MUSASHI_GENERATED_DIR}/80173580_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80173580_RESULT)
    if(NOT MUSASHI_SC02_80173580_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173580 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801735b8.c
                ${MUSASHI_GENERATED_DIR}/801735b8_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_801735B8_RESULT)
    if(NOT MUSASHI_SC02_801735B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801735b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801735ec.c
                ${MUSASHI_GENERATED_DIR}/801735ec_sc02_0031_words.inc --expected-words 23
        RESULT_VARIABLE MUSASHI_SC02_801735EC_RESULT)
    if(NOT MUSASHI_SC02_801735EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801735ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801736b0.c
                ${MUSASHI_GENERATED_DIR}/801736b0_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_801736B0_RESULT)
    if(NOT MUSASHI_SC02_801736B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801736b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173738.c
                ${MUSASHI_GENERATED_DIR}/80173738_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80173738_RESULT)
    if(NOT MUSASHI_SC02_80173738_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173738 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173770.c
                ${MUSASHI_GENERATED_DIR}/80173770_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80173770_RESULT)
    if(NOT MUSASHI_SC02_80173770_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173770 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801737b8.c
                ${MUSASHI_GENERATED_DIR}/801737b8_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801737B8_RESULT)
    if(NOT MUSASHI_SC02_801737B8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801737b8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173824.c
                ${MUSASHI_GENERATED_DIR}/80173824_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80173824_RESULT)
    if(NOT MUSASHI_SC02_80173824_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173824 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801738dc.c
                ${MUSASHI_GENERATED_DIR}/801738dc_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801738DC_RESULT)
    if(NOT MUSASHI_SC02_801738DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801738dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173948.c
                ${MUSASHI_GENERATED_DIR}/80173948_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80173948_RESULT)
    if(NOT MUSASHI_SC02_80173948_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173948 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173980.c
                ${MUSASHI_GENERATED_DIR}/80173980_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80173980_RESULT)
    if(NOT MUSASHI_SC02_80173980_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173980 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801739d8.c
                ${MUSASHI_GENERATED_DIR}/801739d8_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_801739D8_RESULT)
    if(NOT MUSASHI_SC02_801739D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801739d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173a28.c
                ${MUSASHI_GENERATED_DIR}/80173a28_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80173A28_RESULT)
    if(NOT MUSASHI_SC02_80173A28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173a28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173b88.c
                ${MUSASHI_GENERATED_DIR}/80173b88_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80173B88_RESULT)
    if(NOT MUSASHI_SC02_80173B88_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173b88 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173bc0.c
                ${MUSASHI_GENERATED_DIR}/80173bc0_sc02_0031_words.inc --expected-words 41
        RESULT_VARIABLE MUSASHI_SC02_80173BC0_RESULT)
    if(NOT MUSASHI_SC02_80173BC0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173bc0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80173c64.c
                ${MUSASHI_GENERATED_DIR}/80173c64_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80173C64_RESULT)
    if(NOT MUSASHI_SC02_80173C64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80173c64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174158.c
                ${MUSASHI_GENERATED_DIR}/80174158_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80174158_RESULT)
    if(NOT MUSASHI_SC02_80174158_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174158 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174188.c
                ${MUSASHI_GENERATED_DIR}/80174188_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80174188_RESULT)
    if(NOT MUSASHI_SC02_80174188_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174188 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801741a8.c
                ${MUSASHI_GENERATED_DIR}/801741a8_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_801741A8_RESULT)
    if(NOT MUSASHI_SC02_801741A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801741a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801741ec.c
                ${MUSASHI_GENERATED_DIR}/801741ec_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_801741EC_RESULT)
    if(NOT MUSASHI_SC02_801741EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801741ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017427c.c
                ${MUSASHI_GENERATED_DIR}/8017427c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017427C_RESULT)
    if(NOT MUSASHI_SC02_8017427C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017427c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801742e0.c
                ${MUSASHI_GENERATED_DIR}/801742e0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801742E0_RESULT)
    if(NOT MUSASHI_SC02_801742E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801742e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174318.c
                ${MUSASHI_GENERATED_DIR}/80174318_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80174318_RESULT)
    if(NOT MUSASHI_SC02_80174318_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174318 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017435c.c
                ${MUSASHI_GENERATED_DIR}/8017435c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017435C_RESULT)
    if(NOT MUSASHI_SC02_8017435C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017435c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801743c0.c
                ${MUSASHI_GENERATED_DIR}/801743c0_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801743C0_RESULT)
    if(NOT MUSASHI_SC02_801743C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801743c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801743f0.c
                ${MUSASHI_GENERATED_DIR}/801743f0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801743F0_RESULT)
    if(NOT MUSASHI_SC02_801743F0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801743f0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174438.c
                ${MUSASHI_GENERATED_DIR}/80174438_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80174438_RESULT)
    if(NOT MUSASHI_SC02_80174438_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174438 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801744b0.c
                ${MUSASHI_GENERATED_DIR}/801744b0_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801744B0_RESULT)
    if(NOT MUSASHI_SC02_801744B0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801744b0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801744e0.c
                ${MUSASHI_GENERATED_DIR}/801744e0_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_801744E0_RESULT)
    if(NOT MUSASHI_SC02_801744E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801744e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017452c.c
                ${MUSASHI_GENERATED_DIR}/8017452c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017452C_RESULT)
    if(NOT MUSASHI_SC02_8017452C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017452c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174554.c
                ${MUSASHI_GENERATED_DIR}/80174554_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80174554_RESULT)
    if(NOT MUSASHI_SC02_80174554_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174554 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174584.c
                ${MUSASHI_GENERATED_DIR}/80174584_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80174584_RESULT)
    if(NOT MUSASHI_SC02_80174584_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174584 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801745ac.c
                ${MUSASHI_GENERATED_DIR}/801745ac_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_801745AC_RESULT)
    if(NOT MUSASHI_SC02_801745AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801745ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801745dc.c
                ${MUSASHI_GENERATED_DIR}/801745dc_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_801745DC_RESULT)
    if(NOT MUSASHI_SC02_801745DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801745dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174604.c
                ${MUSASHI_GENERATED_DIR}/80174604_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80174604_RESULT)
    if(NOT MUSASHI_SC02_80174604_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174604 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174630.c
                ${MUSASHI_GENERATED_DIR}/80174630_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80174630_RESULT)
    if(NOT MUSASHI_SC02_80174630_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174630 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174674.c
                ${MUSASHI_GENERATED_DIR}/80174674_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80174674_RESULT)
    if(NOT MUSASHI_SC02_80174674_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174674 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174684.c
                ${MUSASHI_GENERATED_DIR}/80174684_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80174684_RESULT)
    if(NOT MUSASHI_SC02_80174684_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174684 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801746a4.c
                ${MUSASHI_GENERATED_DIR}/801746a4_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801746A4_RESULT)
    if(NOT MUSASHI_SC02_801746A4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801746a4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801746dc.c
                ${MUSASHI_GENERATED_DIR}/801746dc_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_801746DC_RESULT)
    if(NOT MUSASHI_SC02_801746DC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801746dc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174714.c
                ${MUSASHI_GENERATED_DIR}/80174714_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80174714_RESULT)
    if(NOT MUSASHI_SC02_80174714_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174714 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174754.c
                ${MUSASHI_GENERATED_DIR}/80174754_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80174754_RESULT)
    if(NOT MUSASHI_SC02_80174754_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174754 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174764.c
                ${MUSASHI_GENERATED_DIR}/80174764_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80174764_RESULT)
    if(NOT MUSASHI_SC02_80174764_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174764 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174774.c
                ${MUSASHI_GENERATED_DIR}/80174774_sc02_0031_words.inc --expected-words 4
        RESULT_VARIABLE MUSASHI_SC02_80174774_RESULT)
    if(NOT MUSASHI_SC02_80174774_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174774 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174784.c
                ${MUSASHI_GENERATED_DIR}/80174784_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80174784_RESULT)
    if(NOT MUSASHI_SC02_80174784_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174784 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801747ac.c
                ${MUSASHI_GENERATED_DIR}/801747ac_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801747AC_RESULT)
    if(NOT MUSASHI_SC02_801747AC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801747ac words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174808.c
                ${MUSASHI_GENERATED_DIR}/80174808_sc02_0031_words.inc --expected-words 5
        RESULT_VARIABLE MUSASHI_SC02_80174808_RESULT)
    if(NOT MUSASHI_SC02_80174808_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174808 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017481c.c
                ${MUSASHI_GENERATED_DIR}/8017481c_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_8017481C_RESULT)
    if(NOT MUSASHI_SC02_8017481C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017481c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174824.c
                ${MUSASHI_GENERATED_DIR}/80174824_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80174824_RESULT)
    if(NOT MUSASHI_SC02_80174824_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174824 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017484c.c
                ${MUSASHI_GENERATED_DIR}/8017484c_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_8017484C_RESULT)
    if(NOT MUSASHI_SC02_8017484C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017484c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801748c4.c
                ${MUSASHI_GENERATED_DIR}/801748c4_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801748C4_RESULT)
    if(NOT MUSASHI_SC02_801748C4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801748c4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801748e4.c
                ${MUSASHI_GENERATED_DIR}/801748e4_sc02_0031_words.inc --expected-words 2
        RESULT_VARIABLE MUSASHI_SC02_801748E4_RESULT)
    if(NOT MUSASHI_SC02_801748E4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801748e4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801748ec.c
                ${MUSASHI_GENERATED_DIR}/801748ec_sc02_0031_words.inc --expected-words 32
        RESULT_VARIABLE MUSASHI_SC02_801748EC_RESULT)
    if(NOT MUSASHI_SC02_801748EC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801748ec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801749a8.c
                ${MUSASHI_GENERATED_DIR}/801749a8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_801749A8_RESULT)
    if(NOT MUSASHI_SC02_801749A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801749a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174b6c.c
                ${MUSASHI_GENERATED_DIR}/80174b6c_sc02_0031_words.inc --expected-words 20
        RESULT_VARIABLE MUSASHI_SC02_80174B6C_RESULT)
    if(NOT MUSASHI_SC02_80174B6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174b6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174bbc.c
                ${MUSASHI_GENERATED_DIR}/80174bbc_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80174BBC_RESULT)
    if(NOT MUSASHI_SC02_80174BBC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174bbc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174c60.c
                ${MUSASHI_GENERATED_DIR}/80174c60_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_80174C60_RESULT)
    if(NOT MUSASHI_SC02_80174C60_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174c60 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174c80.c
                ${MUSASHI_GENERATED_DIR}/80174c80_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80174C80_RESULT)
    if(NOT MUSASHI_SC02_80174C80_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174c80 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174e9c.c
                ${MUSASHI_GENERATED_DIR}/80174e9c_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80174E9C_RESULT)
    if(NOT MUSASHI_SC02_80174E9C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174e9c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174ed4.c
                ${MUSASHI_GENERATED_DIR}/80174ed4_sc02_0031_words.inc --expected-words 7
        RESULT_VARIABLE MUSASHI_SC02_80174ED4_RESULT)
    if(NOT MUSASHI_SC02_80174ED4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174ed4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174ef0.c
                ${MUSASHI_GENERATED_DIR}/80174ef0_sc02_0031_words.inc --expected-words 14
        RESULT_VARIABLE MUSASHI_SC02_80174EF0_RESULT)
    if(NOT MUSASHI_SC02_80174EF0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174ef0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174f64.c
                ${MUSASHI_GENERATED_DIR}/80174f64_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80174F64_RESULT)
    if(NOT MUSASHI_SC02_80174F64_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174f64 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174fbc.c
                ${MUSASHI_GENERATED_DIR}/80174fbc_sc02_0031_words.inc --expected-words 22
        RESULT_VARIABLE MUSASHI_SC02_80174FBC_RESULT)
    if(NOT MUSASHI_SC02_80174FBC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174fbc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175014.c
                ${MUSASHI_GENERATED_DIR}/80175014_sc02_0031_words.inc --expected-words 34
        RESULT_VARIABLE MUSASHI_SC02_80175014_RESULT)
    if(NOT MUSASHI_SC02_80175014_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175014 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017509c.c
                ${MUSASHI_GENERATED_DIR}/8017509c_sc02_0031_words.inc --expected-words 30
        RESULT_VARIABLE MUSASHI_SC02_8017509C_RESULT)
    if(NOT MUSASHI_SC02_8017509C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017509c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175114.c
                ${MUSASHI_GENERATED_DIR}/80175114_sc02_0031_words.inc --expected-words 15
        RESULT_VARIABLE MUSASHI_SC02_80175114_RESULT)
    if(NOT MUSASHI_SC02_80175114_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175114 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175150.c
                ${MUSASHI_GENERATED_DIR}/80175150_sc02_0031_words.inc --expected-words 13
        RESULT_VARIABLE MUSASHI_SC02_80175150_RESULT)
    if(NOT MUSASHI_SC02_80175150_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175150 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801751d8.c
                ${MUSASHI_GENERATED_DIR}/801751d8_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801751D8_RESULT)
    if(NOT MUSASHI_SC02_801751D8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801751d8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801752bc.c
                ${MUSASHI_GENERATED_DIR}/801752bc_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_801752BC_RESULT)
    if(NOT MUSASHI_SC02_801752BC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801752bc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175414.c
                ${MUSASHI_GENERATED_DIR}/80175414_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80175414_RESULT)
    if(NOT MUSASHI_SC02_80175414_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175414 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175454.c
                ${MUSASHI_GENERATED_DIR}/80175454_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80175454_RESULT)
    if(NOT MUSASHI_SC02_80175454_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175454 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175624.c
                ${MUSASHI_GENERATED_DIR}/80175624_sc02_0031_words.inc --expected-words 17
        RESULT_VARIABLE MUSASHI_SC02_80175624_RESULT)
    if(NOT MUSASHI_SC02_80175624_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175624 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80175668.c
                ${MUSASHI_GENERATED_DIR}/80175668_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80175668_RESULT)
    if(NOT MUSASHI_SC02_80175668_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80175668 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801757e0.c
                ${MUSASHI_GENERATED_DIR}/801757e0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801757E0_RESULT)
    if(NOT MUSASHI_SC02_801757E0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801757e0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801787d4.c
                ${MUSASHI_GENERATED_DIR}/801787d4_sc02_0031_words.inc --expected-words 27
        RESULT_VARIABLE MUSASHI_SC02_801787D4_RESULT)
    if(NOT MUSASHI_SC02_801787D4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801787d4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80178bb8.c
                ${MUSASHI_GENERATED_DIR}/80178bb8_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_80178BB8_RESULT)
    if(NOT MUSASHI_SC02_80178BB8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80178bb8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179b28.c
                ${MUSASHI_GENERATED_DIR}/80179b28_sc02_0031_words.inc --expected-words 19
        RESULT_VARIABLE MUSASHI_SC02_80179B28_RESULT)
    if(NOT MUSASHI_SC02_80179B28_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179b28 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179d30.c
                ${MUSASHI_GENERATED_DIR}/80179d30_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80179D30_RESULT)
    if(NOT MUSASHI_SC02_80179D30_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179d30 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179d78.c
                ${MUSASHI_GENERATED_DIR}/80179d78_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80179D78_RESULT)
    if(NOT MUSASHI_SC02_80179D78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179d78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179dcc.c
                ${MUSASHI_GENERATED_DIR}/80179dcc_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80179DCC_RESULT)
    if(NOT MUSASHI_SC02_80179DCC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179dcc words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179df8.c
                ${MUSASHI_GENERATED_DIR}/80179df8_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80179DF8_RESULT)
    if(NOT MUSASHI_SC02_80179DF8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179df8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179e1c.c
                ${MUSASHI_GENERATED_DIR}/80179e1c_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80179E1C_RESULT)
    if(NOT MUSASHI_SC02_80179E1C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179e1c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179e48.c
                ${MUSASHI_GENERATED_DIR}/80179e48_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80179E48_RESULT)
    if(NOT MUSASHI_SC02_80179E48_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179e48 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179e74.c
                ${MUSASHI_GENERATED_DIR}/80179e74_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80179E74_RESULT)
    if(NOT MUSASHI_SC02_80179E74_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179e74 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179ea0.c
                ${MUSASHI_GENERATED_DIR}/80179ea0_sc02_0031_words.inc --expected-words 18
        RESULT_VARIABLE MUSASHI_SC02_80179EA0_RESULT)
    if(NOT MUSASHI_SC02_80179EA0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179ea0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179ee8.c
                ${MUSASHI_GENERATED_DIR}/80179ee8_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80179EE8_RESULT)
    if(NOT MUSASHI_SC02_80179EE8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179ee8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179f14.c
                ${MUSASHI_GENERATED_DIR}/80179f14_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_80179F14_RESULT)
    if(NOT MUSASHI_SC02_80179F14_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179f14 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179f44.c
                ${MUSASHI_GENERATED_DIR}/80179f44_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_80179F44_RESULT)
    if(NOT MUSASHI_SC02_80179F44_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179f44 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179f6c.c
                ${MUSASHI_GENERATED_DIR}/80179f6c_sc02_0031_words.inc --expected-words 11
        RESULT_VARIABLE MUSASHI_SC02_80179F6C_RESULT)
    if(NOT MUSASHI_SC02_80179F6C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179f6c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179f98.c
                ${MUSASHI_GENERATED_DIR}/80179f98_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80179F98_RESULT)
    if(NOT MUSASHI_SC02_80179F98_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179f98 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80179fec.c
                ${MUSASHI_GENERATED_DIR}/80179fec_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_80179FEC_RESULT)
    if(NOT MUSASHI_SC02_80179FEC_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80179fec words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a040.c
                ${MUSASHI_GENERATED_DIR}/8017a040_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8017A040_RESULT)
    if(NOT MUSASHI_SC02_8017A040_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a040 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a0f4.c
                ${MUSASHI_GENERATED_DIR}/8017a0f4_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A0F4_RESULT)
    if(NOT MUSASHI_SC02_8017A0F4_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a0f4 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a11c.c
                ${MUSASHI_GENERATED_DIR}/8017a11c_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A11C_RESULT)
    if(NOT MUSASHI_SC02_8017A11C_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a11c words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a180.c
                ${MUSASHI_GENERATED_DIR}/8017a180_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A180_RESULT)
    if(NOT MUSASHI_SC02_8017A180_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a180 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a1a8.c
                ${MUSASHI_GENERATED_DIR}/8017a1a8_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A1A8_RESULT)
    if(NOT MUSASHI_SC02_8017A1A8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a1a8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a1d0.c
                ${MUSASHI_GENERATED_DIR}/8017a1d0_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A1D0_RESULT)
    if(NOT MUSASHI_SC02_8017A1D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a1d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a1f8.c
                ${MUSASHI_GENERATED_DIR}/8017a1f8_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A1F8_RESULT)
    if(NOT MUSASHI_SC02_8017A1F8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a1f8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a220.c
                ${MUSASHI_GENERATED_DIR}/8017a220_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A220_RESULT)
    if(NOT MUSASHI_SC02_8017A220_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a220 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a248.c
                ${MUSASHI_GENERATED_DIR}/8017a248_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A248_RESULT)
    if(NOT MUSASHI_SC02_8017A248_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a248 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a270.c
                ${MUSASHI_GENERATED_DIR}/8017a270_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A270_RESULT)
    if(NOT MUSASHI_SC02_8017A270_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a270 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a298.c
                ${MUSASHI_GENERATED_DIR}/8017a298_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A298_RESULT)
    if(NOT MUSASHI_SC02_8017A298_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a298 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a2c0.c
                ${MUSASHI_GENERATED_DIR}/8017a2c0_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A2C0_RESULT)
    if(NOT MUSASHI_SC02_8017A2C0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a2c0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a2e8.c
                ${MUSASHI_GENERATED_DIR}/8017a2e8_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A2E8_RESULT)
    if(NOT MUSASHI_SC02_8017A2E8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a2e8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a310.c
                ${MUSASHI_GENERATED_DIR}/8017a310_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A310_RESULT)
    if(NOT MUSASHI_SC02_8017A310_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a310 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a338.c
                ${MUSASHI_GENERATED_DIR}/8017a338_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A338_RESULT)
    if(NOT MUSASHI_SC02_8017A338_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a338 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a360.c
                ${MUSASHI_GENERATED_DIR}/8017a360_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A360_RESULT)
    if(NOT MUSASHI_SC02_8017A360_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a360 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017a388.c
                ${MUSASHI_GENERATED_DIR}/8017a388_sc02_0031_words.inc --expected-words 10
        RESULT_VARIABLE MUSASHI_SC02_8017A388_RESULT)
    if(NOT MUSASHI_SC02_8017A388_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017a388 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017ade8.c
                ${MUSASHI_GENERATED_DIR}/8017ade8_sc02_0031_words.inc --expected-words 8
        RESULT_VARIABLE MUSASHI_SC02_8017ADE8_RESULT)
    if(NOT MUSASHI_SC02_8017ADE8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017ade8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8017ae08.c
                ${MUSASHI_GENERATED_DIR}/8017ae08_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_8017AE08_RESULT)
    if(NOT MUSASHI_SC02_8017AE08_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8017ae08 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016ee40.c
                ${MUSASHI_GENERATED_DIR}/8016ee40_sc02_0031_words.inc --expected-words 21
        RESULT_VARIABLE MUSASHI_SC02_8016EE40_RESULT)
    if(NOT MUSASHI_SC02_8016EE40_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016ee40 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016ef78.c
                ${MUSASHI_GENERATED_DIR}/8016ef78_sc02_0031_words.inc --expected-words 12
        RESULT_VARIABLE MUSASHI_SC02_8016EF78_RESULT)
    if(NOT MUSASHI_SC02_8016EF78_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016ef78 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/8016efc8.c
                ${MUSASHI_GENERATED_DIR}/8016efc8_sc02_0031_words.inc --expected-words 51
        RESULT_VARIABLE MUSASHI_SC02_8016EFC8_RESULT)
    if(NOT MUSASHI_SC02_8016EFC8_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 8016efc8 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/801726d0.c
                ${MUSASHI_GENERATED_DIR}/801726d0_sc02_0031_words.inc --expected-words 16
        RESULT_VARIABLE MUSASHI_SC02_801726D0_RESULT)
    if(NOT MUSASHI_SC02_801726D0_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 801726d0 words")
    endif()
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_asm_words.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/overlays/sc02_0031/80174650.c
                ${MUSASHI_GENERATED_DIR}/80174650_sc02_0031_words.inc --expected-words 9
        RESULT_VARIABLE MUSASHI_SC02_80174650_RESULT)
    if(NOT MUSASHI_SC02_80174650_RESULT EQUAL 0)
        message(FATAL_ERROR "Cannot extract SC02 80174650 words")
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
