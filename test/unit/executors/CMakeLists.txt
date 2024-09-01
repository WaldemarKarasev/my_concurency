add_executable(manual manual.cpp)
target_link_libraries(manual
        # ${TEST_LIBS}
        concurrency
        #   GTest::gtest_main
        gtest
)

gtest_discover_tests(manual)
