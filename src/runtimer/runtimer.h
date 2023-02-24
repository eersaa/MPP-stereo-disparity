#ifndef RUNTIMER_HPP
#define RUNTIMER_HPP

struct IClock
{
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual int elapsedMillis() = 0;
};

struct IProgram
{
    
};

class RunTimer
{
    public:
    RunTimer(IProgram& program, IClock& clock);

    int timeProgram();

    private:
    IProgram& mProgram;
    IClock& mClock;
};



#endif // RUNTIMER_HPP