find_package(GTest REQUIRED)

add_executable(kalon_tests
    test_real.cpp
    test_vector3.cpp
    test_quaternion.cpp
)
target_link_libraries(kalon_tests PRIVATE kalon::kalon GTest::gtest_main)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(kalon_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(GoogleTest)
gtest_discover_tests(kalon_tests)
