add_executable(manual manual.cpp)
target_link_libraries(manual
        concurrency
        gtest
)

add_executable(strand strand.cpp)
target_link_libraries(strand
        concurrency
        gtest
)


gtest_discover_tests(manual)
gtest_discover_tests(strand)
