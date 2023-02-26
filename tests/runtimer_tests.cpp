#include "runtimer.h"
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


class StopWatchTest : public ::testing::Test
{
    protected:
        StopWatch* stopWatch;
        FakeClock* fakeClock;

        void SetUp() override
        {
            fakeClock = new FakeClock(1, 3);
            stopWatch = new StopWatch(*fakeClock);
        }

        void TearDown() override
        {
            delete stopWatch;
            delete fakeClock;
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


class ProgramStopWatchTest : public ::testing::Test
{
    protected:
        ProgramStopWatch* programStopWatch;
        FakeClock* fakeClock;

        void SetUp() override
        {
            fakeClock = new FakeClock(1, 3);
            programStopWatch = new ProgramStopWatch(*fakeClock);
        }

        void TearDown() override
        {
            delete programStopWatch;
            delete fakeClock;
        }
};

TEST_F(ProgramStopWatchTest, ShouldReturnZeroAfterSuccessfulRun)
{
    FakeProgram fakeProgram(0);
    ASSERT_EQ(programStopWatch->runProgram(fakeProgram), 0);
}

TEST_F(ProgramStopWatchTest, ShouldReturnValueOfProgramAfterRun)
{
    FakeProgram fakeProgram(1);
    ASSERT_EQ(programStopWatch->runProgram(fakeProgram), 1);
}

TEST_F(ProgramStopWatchTest, ShouldReturnElapsedTimeAfterRun)
{
    FakeProgram fakeProgram(0);
    programStopWatch->runProgram(fakeProgram);
    ASSERT_EQ(programStopWatch->getElapsedTime(), 2);
}
