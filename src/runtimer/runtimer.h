#ifndef RUNTIMER_HPP
#define RUNTIMER_HPP

struct ITimer
{
    virtual void start() = 0;

    virtual bool isRunning() = 0;
};

class RunTimer : public ITimer
{
public:
    RunTimer();

    void start() override;

    bool isRunning() override;

    private:
        bool running;
};


#endif // RUNTIMER_HPP