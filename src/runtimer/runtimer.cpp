#include "runtimer.h"

RunTimer::RunTimer(){}

void RunTimer::start()
{
    running = true;
}

bool RunTimer::isRunning()
{
    return running;
}