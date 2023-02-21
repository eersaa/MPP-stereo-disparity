#ifndef RUNTIMER_HPP
#define RUNTIMER_HPP

struct ITimer
{
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void getElapsedTime() = 0;
};

#endif // RUNTIMER_HPP