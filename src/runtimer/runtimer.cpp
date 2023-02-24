#include "runtimer.h"

RunTimer::RunTimer(IStopWatch& stopWatch)
    : mStopWatch(stopWatch)
{
    ;
}

int RunTimer::runProgram(IProgram& program)
{
    mStopWatch.saveStartPoint();
    int result = program.run();
    mStopWatch.saveEndPoint();
    return result;
}

int RunTimer::getElapsedTime()
{
    return mStopWatch.getElapsedTime();
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
