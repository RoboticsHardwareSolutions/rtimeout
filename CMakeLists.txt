cmake_minimum_required(VERSION 3.9)
project(rtimeout
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION
        "Cross Platform Lib for Count Timeout")

add_library(${PROJECT_NAME} STATIC
        rtimeout.c
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})


if (MSVC OR MSYS OR MINGW)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DRTIMEOUT_FOR_WINDOWS)
endif ()

if (APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DRTIMEOUT_FOR_APPLE)
endif ()

if (UNIX AND NOT APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DRTIMEOUT_FOR_UNIX)
endif ()


if (NOT ${CMAKE_SYSTEM_NAME} MATCHES Generic)
    add_executable(${PROJECT_NAME}_test
            test/runit/src/runit.c
            rtimeout.c
            test/test.c)

    if (MSVC OR MSYS OR MINGW)
        target_compile_definitions(${PROJECT_NAME}_test PUBLIC -DRTIMEOUT_FOR_WINDOWS)
    endif ()

    if (APPLE)
        target_compile_definitions(${PROJECT_NAME}_test PUBLIC -DRTIMEOUT_FOR_APPLE)
    endif ()

    if (UNIX AND NOT APPLE)
        target_compile_definitions(${PROJECT_NAME}_test PUBLIC -DRTIMEOUT_FOR_UNIX)
    endif ()
endif ()


set(FILES_FOR_FORMATTING
        rtimeout.h
        rtimeout.c
        rtimeout_def.h
        test/test.c
)

# clang-format
find_program(clang_format NAMES clang-format)
if (NOT clang_format)
    message(STATUS "Could not locate clang-format")
else ()
    file(GLOB format_files ${FILES_FOR_FORMATTING})
    add_custom_target(rtimeout_format COMMAND ${clang_format} -i -fallback-style=none -style=file --verbose ${format_files})
endif ()


enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
