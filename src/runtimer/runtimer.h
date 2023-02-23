#ifndef RUNTIMER_HPP
#define RUNTIMER_HPP

struct IClock
{
    
};

struct IProgram
{
    
};

class RunTimer
{
    public:
    RunTimer(IProgram* program, IClock* clock);

    int getElapsedTime();
    int runProgram();

    private:
    IProgram* mProgram;
    IClock* mClock;
};



#endif // RUNTIMER_HPP