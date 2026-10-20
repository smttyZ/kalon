cmake_minimum_required(VERSION 3.23)

project(kalon VERSION 0.1.0 LANGUAGES CXX)

# Tests build by default only when kalon is the top-level project, so
# consumers that pull kalon in via add_subdirectory don't need GoogleTest.
option(KALON_BUILD_TESTS "Build Kalon tests" ${PROJECT_IS_TOP_LEVEL})

add_library(kalon INTERFACE)
add_library(kalon::kalon ALIAS kalon)

# Header-only: declare headers as a file set so they install correctly and
# show up in IDEs, without leaking absolute source paths into the export.
target_sources(kalon
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
            include/kalon/Constants.hpp
            include/kalon/Matrix3.hpp
            include/kalon/Matrix4.hpp
            include/kalon/Quaternion.hpp
            include/kalon/Real.hpp
            include/kalon/Transform.hpp
            include/kalon/Vector2.hpp
            include/kalon/Vector3.hpp
            include/kalon/Vector4.hpp
)

target_compile_features(kalon INTERFACE cxx_std_20)

# install rules
install(
    TARGETS kalon
    EXPORT kalonTargets
    FILE_SET HEADERS
)

install(
    EXPORT kalonTargets
    FILE kalonConfig.cmake
    NAMESPACE kalon::
    DESTINATION lib/cmake/kalon
)

if(KALON_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
