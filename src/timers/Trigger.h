#pragma once
#include <string>
#include "PausableTimer.h"

typedef void (*behaviorPtr)();
namespace Timing
{
    class Trigger : public PausableTimer
    {
    private:
        void (*endBehavior)();

    protected:
        virtual void goOff() override
        {
            PausableTimer::goOff();
            endBehavior();
        };

    public:
        Trigger(unsigned long timerLength, void (*endBehavior)()) : PausableTimer(timerLength)
        {
            this->endBehavior = endBehavior;
        };
        Trigger(unsigned long timerLength, void (*endBehavior)(), String name) : PausableTimer(timerLength, name)
        {
            this->endBehavior = endBehavior;
        };
        Trigger(unsigned long timerLength, void (*endBehavior)(), String name, String msg) : PausableTimer(timerLength, name, msg)
        {
            this->endBehavior = endBehavior;
        };

        behaviorPtr getEndBehavior()
        {
            return endBehavior;
        };

        void setEndBehavior(void (*endBehavior)())
        {
            this->endBehavior = endBehavior;
        };
    };
};