#include "runtimer.h"

RunTimer::RunTimer(IProgram* program, IClock* clock)
    : mProgram(program), mClock(clock)
{
    ;
}

int RunTimer::getElapsedTime()
{
    return 1;
}