cmake_minimum_required(VERSION 3.9)
project(rtimeout_test
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION
        "Cross Platform Lib for Count Timeout")

add_library(rtimeout STATIC
        rtimeout.c
        rtimeout.h
        )


add_executable(rtimeout_test
        test/runit/src/runit.c
        rtimeout.c
        test/test.c)

set(FILES_FOR_FORMATTING
        rtimeout.h
        rtimeout.c
        test/test.c
        )

if (MSVC OR MSYS OR MINGW)
    target_compile_definitions(rtimeout PUBLIC -DRTIMEOUT_FOR_WINDOWS)
endif ()

if (APPLE)
    target_compile_definitions(rtimeout PUBLIC -DRTIMEOUT_FOR_APPLE)
endif ()

if (UNIX AND NOT APPLE)
    target_compile_definitions(rtimeout PUBLIC -DRTIMEOUT_FOR_UNIX)
endif ()


# clang-format
find_program(clang_format NAMES clang-format)
if (NOT clang_format)
    message(STATUS "Could not locate clang-format")
else ()
    file(GLOB format_files ${FILES_FOR_FORMATTING})
    message(STATUS "Using clang-format: ${clang_format}; files: ${format_files}")
    add_custom_target(rtimeout_format COMMAND ${clang_format} -i -fallback-style=none -style=file --verbose ${format_files})
endif ()


enable_testing()
add_test(NAME rtimeout_test COMMAND rtimeout_test)