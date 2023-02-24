#include "runtimer.h"

RunTimer::RunTimer(IProgram& program, IStopWatch& stopWatch)
    : mProgram(program)
    , mStopWatch(stopWatch)
{
    ;
}

int RunTimer::timeProgram()
{
    mStopWatch.saveStartPoint();
    int result = mProgram.run();
    mStopWatch.saveEndPoint();
    return result;
}

StopWatch::StopWatch(IClock& clock) 
    : mClock(clock)
{
    ;
}

int StopWatch::saveStartPoint()
{
    return mStartTime = mClock.now();
}

int StopWatch::saveEndPoint()
{
    return mEndTime = mClock.now();
}

int StopWatch::getElapsedTime()
{
    if (mStartTime < mEndTime)
    {
        return mEndTime - mStartTime;
    }
    else
    {
        return 0;
    }
}
