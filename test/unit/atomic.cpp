// STL
#include <iostream>
#include <chrono>
#include <thread>

// Testing
#include <gtest/gtest.h>

// Concurrency
#include <concurrency/sync/atomic/atomic.hpp>


TEST(Atomic, Load) {
    concurrency::atomic cell_0{0};
    concurrency::atomic cell_1{42};

    EXPECT_EQ(cell_0.load(), 0);
    EXPECT_EQ(cell_1.load(), 42);
}

TEST(Atomic, Store) {
    concurrency::atomic cell{0};

    EXPECT_EQ(cell.load(), 0);
    cell.store(42);
    EXPECT_EQ(cell.load(), 42);
}

TEST(Atomic, Exchange)
{
    concurrency::atomic cell{0};

    EXPECT_EQ(cell.exchange(7), 0);
    EXPECT_EQ(cell.load(), 7);
    cell.store(42);
    EXPECT_EQ(cell.exchange(10), 42);
    EXPECT_EQ(cell.load(), 10);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*

SIMPLE_TEST(LoadStore) {

  }

  SIMPLE_TEST(Exchange) {

  }
*/
