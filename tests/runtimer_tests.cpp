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
        FakeClock(int startTime, int endTime) 
            : mStartTime(startTime)
            , mEndTime(endTime)
            {

            }
        
        int now() override
        {
            if (!mIsRunning)
            {
                mIsRunning = true;
                return mStartTime;
            }
            else
            {
                mIsRunning = false;
                return mEndTime;
            }            
        }

    private:
        int mStartTime;
        int mEndTime;
        bool mIsRunning = false;
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

// class RunTimerTestFixture : public ::testing::Test
// {
//     protected:
//         RunTimer* runTimer;
//         FakeProgram fakeProgram;
//         StopWatch* stopWatch;

//         void SetUp() override
//         {
//         }

//         void TearDown() override
//         {
//             delete runTimer;
//             delete stopWatch;
//         }
// };

// TEST_F(RunTimerTestFixture, ShouldReturnZeroElapsedTime)
// {
//     FakeClock fakeClock(0, 0);
//     stopWatch = new StopWatch(fakeClock);
//     runTimer = new RunTimer(fakeProgram, *stopWatch);
//     ASSERT_EQ(runTimer->timeProgram(), 0);
// }

// TEST_F(RunTimerTestFixture, ShouldReturnElapsedTimeOfTwo)
// {
//     FakeClock fakeClock(1, 3);
//     stopWatch = new StopWatch(fakeClock);
//     runTimer = new RunTimer(fakeProgram, *stopWatch);
//     ASSERT_EQ(runTimer->timeProgram(), 2);
// }

class StopWatchTest : public ::testing::Test
{
    protected:
        StopWatch* stopWatch;

        void SetUp() override
        {
            FakeClock fakeClock(1, 3);
            stopWatch = new StopWatch(fakeClock);
        }

        void TearDown() override
        {
            
        }
};

TEST_F(StopWatchTest, ShouldReturnStartTimePoint)
{
    ASSERT_EQ(stopWatch->saveStartPoint(), 1);
}

TEST_F(StopWatchTest, ShouldReturnEndTimePoint)
{
    stopWatch->saveStartPoint();
    ASSERT_EQ(stopWatch->saveEndPoint(), 3);
}

TEST_F(StopWatchTest, ShouldReturnElapsedTime)
{
    stopWatch->saveStartPoint();
    stopWatch->saveEndPoint();
    ASSERT_EQ(stopWatch->getElapsedTime(), 2);
}

// TEST(TimerTest, ShouldReturnElapsedTimeOfTwoTimePoints)
// {
//     Timer t(fakeClock);

// }

// TEST(ProgramRunnerTest, ShouldReturnZeroAfterSuccessfulProgramRun)
// {
//     ProgramRunner pr;
//     ASSERT_EQ(pr.run(), 0);
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
