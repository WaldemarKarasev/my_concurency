// gtest
#include <gtest/gtest.h>

// STL
#include <iostream>

// concurrency
#include <concurrency/exe/manual.hpp>
#include <concurrency/exe/submit.hpp>

using ManualExecutor = concurrency::exe::ManualExecutor;

using namespace concurrency;

TEST(ManualExecutor, JustWorks) {
    ManualExecutor manual;

    size_t step = 0;

    ASSERT_TRUE(manual.IsEmpty());
    ASSERT_FALSE(manual.NonEmpty());

    ASSERT_FALSE(manual.RunNext());
    ASSERT_EQ(manual.RunAtMost(99), 0);

    exe::Submit(manual, [&] {
        step = 1;
    });

    ASSERT_FALSE(manual.IsEmpty());
    ASSERT_TRUE(manual.NonEmpty());
    ASSERT_EQ(manual.TaskCount(), 1);

    ASSERT_EQ(step, 0);

    exe::Submit(manual, [&] {
        step = 2;
    });

    ASSERT_EQ(manual.TaskCount(), 2);

    ASSERT_EQ(step, 0);

    ASSERT_TRUE(manual.RunNext());

    ASSERT_EQ(step, 1);

    ASSERT_FALSE(manual.IsEmpty());
    ASSERT_TRUE(manual.NonEmpty());
    ASSERT_EQ(manual.TaskCount(), 1);

    exe::Submit(manual, [&] {
        step = 3;
    });

    ASSERT_EQ(manual.TaskCount(), 2);

    ASSERT_EQ(manual.RunAtMost(99), 2);
    ASSERT_EQ(step, 3);

    ASSERT_TRUE(manual.IsEmpty());
    ASSERT_FALSE(manual.NonEmpty());
    ASSERT_FALSE(manual.RunNext());
}

class Looper {
public:
    explicit Looper(exe::IExecutor& e, size_t iters)
    : executor_(e)
    , iters_left_(iters) {
    }

    void Start() {
        Submit();
    }

    void Iter() {
        --iters_left_;
        if (iters_left_ > 0) {
            Submit();
        }
    }

private:
    void Submit() {
        exe::Submit(executor_, [this] {
            Iter();
        });
    }

private:
    exe::IExecutor& executor_;
    size_t iters_left_;
};

TEST(ManualExecutor, RunAtMost) {
    ManualExecutor manual;

    Looper looper{manual, 256};
    looper.Start();

    size_t tasks = 0;
    do {
        tasks += manual.RunAtMost(7);
    } while (manual.NonEmpty());

    ASSERT_EQ(tasks, 256);
}

TEST(ManualExecutor, Drain) {
    ManualExecutor manual;

    Looper looper{manual, 117};
    looper.Start();

    ASSERT_EQ(manual.Drain(), 117);
}



int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}