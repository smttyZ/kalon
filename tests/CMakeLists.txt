find_package(GTest REQUIRED)

add_executable(kalon_tests test_basic.cpp)
target_link_libraries(kalon_tests PRIVATE kalon GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(kalon_tests)
