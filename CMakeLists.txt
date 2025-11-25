cmake_minimum_required(VERSION 3.10)

include_guard(GLOBAL)

project(wdtranslator)

set(DEBUG_BUILD ON)

set(CMAKE_C_STANDARD 23)
set(CMAKE_COMPILE_WARNING_AS_ERROR true)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(BUILD_WDANALYSIS false)

set(MYCLIB_DIR "${PROJECT_SOURCE_DIR}/myclib")

add_subdirectory("${MYCLIB_DIR}")

#set(DCMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler Arguments
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -mtune=native -Wall")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-qual -Wconversion -Wextra")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wfloat-equal -Wformat=2 -Winit-self")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Winline -Wlogical-op -Wpedantic")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpointer-arith -Wredundant-decls")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wshadow -Wstrict-overflow=5")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wstrict-aliasing=2 -Wswitch-default")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wunreachable-code")

    if(DEBUG_BUILD)
        set(CMAKE_C_FLAGS "-fno-omit-frame-pointer -fsanitize=address,undefined")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
    else()
        set(CMAKE_C_FLAGS "-D_FORTIFY_SOURCE=2 -O2")
    endif()
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -mtune=native")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Weverything -Wno-c23-compat")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-cast-align -Wno-switch-enum")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-padded")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unsafe-buffer-usage")

    if(DEBUG_BUILD)
        set(CMAKE_C_FLAGS "-fno-omit-frame-pointer -fsanitize=address,undefined")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
    else()
        set(CMAKE_C_FLAGS "-D_FORTIFY_SOURCE=2 -O2")
    endif()
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_C_FLAGS "/analyze /guard:cf /Gw /MP /Ox /Wall /WL")
endif()

function(build_wdtranslator)
    set(TRANSLATOR_DIR "${PROJECT_SOURCE_DIR}/wdtranslator")
    add_executable(wdtranslator)
    target_sources(wdtranslator
        PUBLIC "${TRANSLATOR_DIR}/wdtranslator.h"
        PRIVATE
        "${TRANSLATOR_DIR}/wdtranslator.c"
        "main.c")
    target_link_libraries(wdtranslator myclib)
    add_dependencies(wdtranslator myclib)
endfunction()

function(build_wdanalysis)
    set(ANALYSIS_DIR "${PROJECT_SOURCE_DIR}/wdanalysis")
    add_library(wdanalysis)
    target_sources(wdanalysis
        PUBLIC "${ANALYSIS_DIR}/wdanalysis.h"
        PRIVATE "${ANALYSIS_DIR}/wdanalysis.c")
endfunction()

build_wdtranslator()
if(${BUILD_WDANALYSIS})
    build_wdanalysis()
endif()
