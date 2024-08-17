add_executable(atomic atomic.cpp)
target_link_libraries(atomic 
        concurrency
        #   GTest::gtest_main
        gtest
)

add_executable(spinlock spinlock.cpp)
target_link_libraries(spinlock 
        concurrency
        #   GTest::gtest_main
        gtest
)
gtest_discover_tests(atomic)
gtest_discover_tests(spinlock)
