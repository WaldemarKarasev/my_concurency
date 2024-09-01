message(AAAAAAAAAAAAAAAAAAAAA ${TEST_LIBS})
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


add_executable(MPMCQueue MPMCQueue.cpp)
target_link_libraries(MPMCQueue 
        # ${TEST_LIBS}
        concurrency
        #   GTest::gtest_main
        gtest
)

add_executable(thread_pool thread_pool.cpp)
target_link_libraries(thread_pool 
        # ${TEST_LIBS}
        concurrency
        #   GTest::gtest_main
        gtest
)

add_executable(coroutine coroutine.cpp)
target_link_libraries(coroutine 
        # ${TEST_LIBS}
        concurrency
        #   GTest::gtest_main
        gtest
)

add_executable(fiber fiber.cpp)
target_link_libraries(fiber 
        # ${TEST_LIBS}
        concurrency
        #   GTest::gtest_main
        gtest
)

add_executable(stdlike_future stdlike_future.cpp)
target_link_libraries(stdlike_future
        # ${TEST_LIBS}
        concurrency
        #   GTest::gtest_main
        gtest
)

gtest_discover_tests(atomic)
gtest_discover_tests(spinlock)
gtest_discover_tests(mutex)
gtest_discover_tests(MPMCQueue)
gtest_discover_tests(thread_pool)
gtest_discover_tests(coroutine)
gtest_discover_tests(fiber)
gtest_discover_tests(stdlike_future)

add_subdirectory(executors)