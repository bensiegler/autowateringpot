#pragma once
#include "PausableTimer.h"
// isn't included in factory update checks for efficiency on more long term check-ins
namespace Timing
{
    class PassiveTimer : public PausableTimer
    {
    public:
        PassiveTimer(unsigned long timerLength) : PausableTimer(timerLength){};
        PassiveTimer(unsigned long timerLength, String name) : PausableTimer(timerLength, name){};
        PassiveTimer(unsigned long timerLength, String name, String msg) : PausableTimer(timerLength, name, msg){};
    };
};