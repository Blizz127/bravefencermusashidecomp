cmake_minimum_required(VERSION 3.16)

# CXX is required by PsyCross, whose renderer and GTE are C++.
project(brave_fencer_musashi_decomp LANGUAGES C CXX)

option(MUSASHI_BUILD_PC_PORT "Build the platform-neutral PC port smoke target" ON)
option(MUSASHI_WITH_PSYCROSS "Link the PC port against the PsyCross Psy-Q reimplementation" ON)

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
    set_source_files_properties(${MUSASHI_PSYCROSS_SOURCES_C} PROPERTIES LANGUAGE C)
    add_library(psycross_static STATIC
        ${MUSASHI_PSYCROSS_SOURCES_C}
        ${MUSASHI_PSYCROSS_SOURCES_CXX}
    )
    set_target_properties(psycross_static PROPERTIES OUTPUT_NAME "psycross")
    target_include_directories(psycross_static
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
    add_library(musashi_shared STATIC
        src/shared/runtime_api.c
    )
    target_include_directories(musashi_shared
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/src/shared
    )
    target_compile_features(musashi_shared PUBLIC c_std_99)

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
        ${MUSASHI_PLATFORM_SOURCE}
    )
    target_include_directories(musashi_pc_port
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/pc_port/include
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/pc_port
    )
    target_compile_features(musashi_pc_port PUBLIC c_std_99)
    target_link_libraries(musashi_pc_port PUBLIC musashi_shared)
    if(MUSASHI_WITH_PSYCROSS)
        target_sources(musashi_pc_port PRIVATE pc_port/psyq_probe.c)
        target_link_libraries(musashi_pc_port PUBLIC psycross_static)
        target_compile_definitions(musashi_pc_port PUBLIC MUSASHI_WITH_PSYCROSS=1)
    endif()

    add_executable(musashi_pc_smoke pc_port/main.c)
    target_compile_features(musashi_pc_smoke PRIVATE c_std_99)
    target_link_libraries(musashi_pc_smoke PRIVATE musashi_pc_port)

    enable_testing()
    add_test(NAME musashi_pc_smoke COMMAND musashi_pc_smoke)

    if(MUSASHI_WITH_PSYCROSS)
        # Draws one quad through the Psy-Q layer and reports sampled pixels.
        # The verdict is made by tools/render_check.py so the comparison stays
        # unit-tested; the smoke test above stays display-free on purpose.
        add_executable(musashi_render_quad pc_port/render_quad.c)
        target_compile_features(musashi_render_quad PRIVATE c_std_99)
        target_link_libraries(musashi_render_quad PRIVATE musashi_pc_port)

        find_package(Python3 COMPONENTS Interpreter REQUIRED)
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
