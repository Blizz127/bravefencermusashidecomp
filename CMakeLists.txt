cmake_minimum_required(VERSION 3.16)

project(brave_fencer_musashi_decomp LANGUAGES C)

option(MUSASHI_BUILD_PC_PORT "Build the platform-neutral PC port smoke target" ON)

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

    add_executable(musashi_pc_smoke pc_port/main.c)
    target_compile_features(musashi_pc_smoke PRIVATE c_std_99)
    target_link_libraries(musashi_pc_smoke PRIVATE musashi_pc_port)

    enable_testing()
    add_test(NAME musashi_pc_smoke COMMAND musashi_pc_smoke)
endif()
