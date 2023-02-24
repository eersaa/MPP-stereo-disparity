#include "runtimer.h"
#include <gtest/gtest.h>
#include <chrono>

using namespace ::testing;

// TEST(RunTimerTest, ShouldStartTimer)
// {
//     RunTimer rt;
//     rt.start();
//     ASSERT_TRUE(rt.isRunning());    
// }

class FakeClock : public IClock
{
    public:
        FakeClock(int time) : mTime(time) {}

    private:
        int mTime;
};

class FakeProgram : public IProgram
{
    public:
        FakeProgram() {}

};

// // Stub that always returns 0
// class FakeProgramStub : public IProgram
// {
//     public:
//         FakeProgramStub() {}

//         int run() override
//         {
//             return 0;
//         }
// };

// // Stub that always returns 1
// class FakeProgramStub2 : public IProgram
// {
//     public:
//         FakeProgramStub2() {}

//         int run() override
//         {
//             return 1;
//         }
// };

// // Stub that always returns negative value
// class FakeProgramStub3 : public IProgram
// {
//     public:
//         FakeProgramStub3() {}

//         int run() override
//         {
//             return -1;
//         }
// };

class RunTimerTestFixture : public ::testing::Test
{
    protected:
        RunTimer* rt;
        FakeProgram fakeProgram;

        void SetUp() override
        {
        }

        void TearDown() override
        {
            delete rt;
        }
};

TEST_F(RunTimerTestFixture, ShouldReturnZeroElapsedTime)
{
    FakeClock fakeClock(0);
    rt = new RunTimer(fakeProgram, fakeClock);
    ASSERT_EQ(rt->timeProgram(), 0);
}

// TEST_F(RunTimerTestFixture, ShouldReturnZeroAfterSuccessfulProgramRun)
// {
//     FakeClock fakeClock(0);
//     rt = new RunTimer(&fakeProgram, &fakeClock);
//     ASSERT_EQ(rt->runProgram(), 0);
// }

// TEST(ProgramRunnerTest, ShouldReturnNonZeroAfterFailingProgramRun)
// {
// }

// TEST_F(RunTimerTestFixture, ShouldReturnElapsedTime)
// {
//     rt.getElapsedTime();
//     ASSERT_EQ(rt.getElapsedTime(), 1s);
        
// }

// {
//     RunTimer rt;
//     rt.start();
//     ASSERT_TRUE(rt.isRunning());
//     rt.stop();
//     ASSERT_FALSE(rt.isRunning());
// }
