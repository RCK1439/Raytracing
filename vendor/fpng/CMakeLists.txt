cmake_minimum_required(VERSION 3.12)
project(fpng)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/fpng.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/fpng.hpp)

add_library(fpng STATIC ${SOURCES} ${HEADERS})

if(WIN32)
    if(MSVC)
        target_compile_options(fpng PRIVATE /W4 /WX)
        target_compile_definitions(fpng PRIVATE _CRT_SECURE_NO_WARNINGS)
    else()
        target_compile_options(fpng PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Werror
            -fno-exceptions
            -msse4.1
            -mpclmul
            -std=c++23
            -fopenmp
        )
    endif()
else()
    target_compile_options(fpng PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -fno-exceptions
        -msse4.1
        -mpclmul
        -std=c++23
        -fopenmp
    )
endif()

target_include_directories(fpng PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(fpng PROPERTIES
    OUTPUT_NAME "fpng"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)