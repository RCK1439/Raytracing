cmake_minimum_required(VERSION 3.12)
project(rtk)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(rtk_VERSION_MAJOR 0)
set(rtk_VERSION_MINOR 1)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(src)
add_subdirectory(vendor)