#ifndef RUNTIMER_HPP
#define RUNTIMER_HPP

struct IClock
{
    virtual int now() = 0;
};

struct IProgram
{

};

struct IStopWatch
{
    virtual int saveStartPoint() = 0;
};

class StopWatch : public IStopWatch
{
    public:
    StopWatch(IClock& clock);

    int saveStartPoint() override;

    private:
    IClock& mClock;
};

class RunTimer
{
    public:
    RunTimer(IProgram& program, IStopWatch& stopWatch);

    int timeProgram();

    private:
    IProgram& mProgram;
    IStopWatch& mStopWatch;
};


#endif // RUNTIMER_HPP