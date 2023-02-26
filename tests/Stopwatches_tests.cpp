#include "Stopwatches.h"
#include <gtest/gtest.h>

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


class StopwatchTest : public ::testing::Test
{
    protected:
        Stopwatch* stopwatch;
        FakeClock* fakeClock;

        void SetUp() override
        {
            fakeClock = new FakeClock(1, 3);
            stopwatch = new Stopwatch(*fakeClock);
        }

        void TearDown() override
        {
            delete stopwatch;
            delete fakeClock;
        }
};

TEST_F(StopwatchTest, ShouldReturnStartTimePoint)
{
    ASSERT_EQ(stopwatch->saveStartPoint(), 1);
}

TEST_F(StopwatchTest, ShouldReturnEndTimePoint)
{
    stopwatch->saveStartPoint();
    ASSERT_EQ(stopwatch->saveEndPoint(), 3);
}

TEST_F(StopwatchTest, ShouldReturnElapsedTime)
{
    stopwatch->saveStartPoint();
    stopwatch->saveEndPoint();
    ASSERT_EQ(stopwatch->getElapsedTime(), 2);
}

TEST_F(StopwatchTest, ShouldAlwaysReturnPositiveElapsedTime)
{
    stopwatch->saveEndPoint();
    stopwatch->saveStartPoint();
    ASSERT_GE(stopwatch->getElapsedTime(), 0);
}


class ProgramStopwatchTest : public ::testing::Test
{
    protected:
        ProgramStopwatch* programStopwatch;
        FakeClock* fakeClock;

        void SetUp() override
        {
            fakeClock = new FakeClock(1, 3);
            programStopwatch = new ProgramStopwatch(*fakeClock);
        }

        void TearDown() override
        {
            delete programStopwatch;
            delete fakeClock;
        }
};

TEST_F(ProgramStopwatchTest, ShouldReturnZeroAfterSuccessfulRun)
{
    FakeProgram fakeProgram(0);
    ASSERT_EQ(programStopwatch->runProgram(fakeProgram), 0);
}

TEST_F(ProgramStopwatchTest, ShouldReturnValueOfProgramAfterRun)
{
    FakeProgram fakeProgram(1);
    ASSERT_EQ(programStopwatch->runProgram(fakeProgram), 1);
}

TEST_F(ProgramStopwatchTest, ShouldReturnElapsedTimeAfterRun)
{
    FakeProgram fakeProgram(0);
    programStopwatch->runProgram(fakeProgram);
    ASSERT_EQ(programStopwatch->getElapsedTime(), 2);
}
