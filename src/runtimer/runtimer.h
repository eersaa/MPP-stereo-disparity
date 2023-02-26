#ifndef RUNTIMER_HPP
#define RUNTIMER_HPP

struct IClock
{
    virtual ~IClock() = default;
    virtual int now() = 0;
};

struct IProgram
{
    virtual ~IProgram() = default;
    virtual int run() = 0;
};

struct IStopWatch
{
    virtual ~IStopWatch() = default;
    virtual int saveStartPoint() = 0;
    virtual int saveEndPoint() = 0;
    virtual int getElapsedTime() = 0;
};

class StopWatch : public IStopWatch
{
    public:
    StopWatch(IClock& clock);

    int saveStartPoint() override;
    int saveEndPoint() override;
    int getElapsedTime() override;

    private:
    IClock& mClock;
    int mStartTime = 0;
    int mEndTime = 0;
};

class RunTimer
{
    public:
    RunTimer(IStopWatch& stopWatch);

    int runProgram(IProgram& program);
    int getElapsedTime();

    private:
    IStopWatch& mStopWatch;
};


#endif // RUNTIMER_HPP
