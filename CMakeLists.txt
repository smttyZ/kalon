cmake_minimum_required(VERSION 3.20)

project(kalon VERSION 0.1 LANGUAGES CXX)

option(KALON_BUILD_TESTS "Build Kalon tests" ON)

add_library(kalon INTERFACE)
target_include_directories(
    kalon
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

file(
    GLOB_RECURSE KALON_HEADERS
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)
target_sources(kalon INTERFACE ${KALON_HEADERS})

target_compile_features(kalon INTERFACE cxx_std_20)

if(KALON_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
