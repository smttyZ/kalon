# GoogleTest is downloaded and built as part of the project, so every machine
# (macOS, Windows, Linux) gets the same version with nothing to install first.
# Needs network access the first time CMake configures; cached afterwards.
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# Keep GoogleTest out of `cmake --install` for kalon.
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
# MSVC only: use the same C runtime as our tests. No effect on GCC/Clang.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(kalon_tests
    RealTests.cpp
    Vector3Tests.cpp
    QuaternionTests.cpp
)
target_link_libraries(kalon_tests PRIVATE kalon::kalon GTest::gtest_main)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(kalon_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(GoogleTest)
gtest_discover_tests(kalon_tests)
