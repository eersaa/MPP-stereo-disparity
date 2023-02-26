#include "runtimer.h"
#include <chrono>

int ChronoClock::now()
{
    return std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();
}


StopWatch::StopWatch(IClock& clock) 
    : mClock{clock}
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


ProgramStopWatch::ProgramStopWatch(IClock& clock) 
    : StopWatch{clock}
    , mClock{clock}
{
    ;
}

int ProgramStopWatch::runProgram(IProgram& program)
{
    saveStartPoint();
    int result = program.run();
    saveEndPoint();
    return result;
}
