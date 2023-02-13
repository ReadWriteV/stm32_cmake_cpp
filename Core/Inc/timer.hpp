#ifndef __TIMER_H
#define __TIMER_H

class Timer
{
public:
    Timer();
    void handle();
    int get_count();

private:
    int count;
};

#endif
