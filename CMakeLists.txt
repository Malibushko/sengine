cmake_minimum_required(VERSION 3.17)
project(SEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)

set(ENGINE_CONAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/conan)

add_subdirectory(RenderEngine)

add_executable(SEngine main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(SEngine Core Threads::Threads)
