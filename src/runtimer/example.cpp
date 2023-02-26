// Example code of measuring the time of execution of a program:
#include "runtimer.h"
#include <iostream>

class Program : public IProgram
{
    public:
    int run() override
    {
        int sum = 0;
        for (int i = 0; i < 1000000; ++i)
        {
            sum += i;
        }
        return sum;
    }
};

int main()
{

    ChronoClock clock;
    StopWatch stopWatch(clock);
    RunTimer runTimer(stopWatch);
    Program program;

    int result = runTimer.runProgram(program);

    std::cout << "Result: " << result << std::endl;
    std::cout << "Elapsed time: " << runTimer.getElapsedTime() << " us" << std::endl;
}
