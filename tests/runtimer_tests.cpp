#include "runtimer.h"
#include <gtest/gtest.h>
#include <chrono>

using namespace ::testing;

class FakeClock : public IClock
{
    public:
        FakeClock(int startTime, int endTime) 
            : mStartTime(startTime)
            , mEndTime(endTime){}
        
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
        FakeProgram(int retVal) 
            : mRetVal(retVal){}

        int run() override
        {
            return mRetVal;
        }

    private:
        int mRetVal;

};

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

TEST_F(StopWatchTest, ShouldAlwaysReturnPositiveElapsedTime)
{
    stopWatch->saveEndPoint();
    stopWatch->saveStartPoint();
    ASSERT_GE(stopWatch->getElapsedTime(), 0);
}


TEST(RunTimerTest, ShouldReturnZeroAfterSuccessfulRun)
{
    FakeProgram fakeProgram(0);
    FakeClock fakeClock(1, 3);
    StopWatch stopWatch(fakeClock);
    RunTimer runTimer(fakeProgram, stopWatch);
    ASSERT_EQ(runTimer.timeProgram(), 0);
}

TEST(RunTimerTest, ShouldReturnValueOfProgramAfterRun)
{
    FakeProgram fakeProgram(1);
    FakeClock fakeClock(1, 3);
    StopWatch stopWatch(fakeClock);
    RunTimer runTimer(fakeProgram, stopWatch);
    ASSERT_EQ(runTimer.timeProgram(), 1);
}