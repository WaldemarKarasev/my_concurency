add_executable(atomic atomic.cpp)
target_link_libraries(atomic 
        # ${TEST_LIBS}
        concurrency
        #   GTest::gtest_main
        gtest
)

add_executable(spinlock spinlock.cpp)
target_link_libraries(spinlock 
        # ${TEST_LIBS}
        concurrency
        #   GTest::gtest_main
        gtest
)

add_executable(mutex mutex.cpp)
target_link_libraries(mutex 
        # ${TEST_LIBS}
        concurrency
        #   GTest::gtest_main
        gtest
)

add_executable(wait_group wait_group.cpp)
target_link_libraries(wait_group 
        concurrency
        gtest
)


gtest_discover_tests(atomic)
gtest_discover_tests(spinlock)
gtest_discover_tests(mutex)
gtest_discover_tests(wait_group)