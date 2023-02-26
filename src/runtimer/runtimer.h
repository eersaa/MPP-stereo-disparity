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

class ChronoClock : public IClock
{
    public:
    int now() override;
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

class ProgramStopWatch : public StopWatch
{
    public:
    ProgramStopWatch(IClock& clock);

    int runProgram(IProgram& program);

    private:
    IClock& mClock;
};


#endif // RUNTIMER_HPP
