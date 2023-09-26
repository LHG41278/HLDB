enable_testing()
add_executable(
    file_test
    file_test.cpp
)

target_link_libraries(
    file_test
    GTest::gtest_main
    hldb
)

add_executable(
  skiplist_test
  skiplist_test.cpp
)

target_link_libraries(
    skiplist_test
    GTest::gtest_main
    hldb
)

include(GoogleTest)
gtest_discover_tests(file_test)
gtest_discover_tests(skiplist_test)
