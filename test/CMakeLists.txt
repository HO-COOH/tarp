cmake_minimum_required(VERSION 3.15)

enable_testing()
include(GoogleTest)
add_executable(testing test/test.cpp ${sources})
target_link_libraries(testing PRIVATE GTest::gtest GTest::gtest_main)
gtest_discover_tests(testing)