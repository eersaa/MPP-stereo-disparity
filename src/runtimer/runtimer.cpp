#include "runtimer.h"

RunTimer::RunTimer(IProgram& program, IClock& clock)
    : mProgram(program), mClock(clock)
{
    ;
}

int RunTimer::timeProgram()
{
    mClock.start();
    mClock.stop();
    return mClock.elapsedMillis();
}
