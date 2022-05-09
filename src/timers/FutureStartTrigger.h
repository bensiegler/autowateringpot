#pragma once
#include "Trigger.h"
// has both start behavior and end behavior

namespace Timing {
class FutureStartTrigger: public Trigger {
    private:
        bool started;
        unsigned long startIn;
        void (*startBehavior)();

    public:
        FutureStartTrigger
            (
                unsigned long timerLength, 
                unsigned long startIn, 
                void (*startBehavior)(), 
                void (*endBehavior)()) : Trigger(millis() + startIn, endBehavior) {
            this->startIn = startIn;
            this->startBehavior = startBehavior;
        };
        FutureStartTrigger
            (
                unsigned long timerLength, 
                unsigned long startIn, 
                void (*startBehavior)(), 
                void (*endBehavior)(),
                String name) : Trigger(millis() + startIn, endBehavior, name) {
            this->startIn = startIn;
            this->startBehavior = startBehavior;
        };
        FutureStartTrigger
            (
                unsigned long timerLength, 
                unsigned long startIn, 
                void (*startBehavior)(), 
                void (*endBehavior)(),
                String name,
                String msg) : Trigger(millis() + startIn, endBehavior, name, msg) {
            this->startIn = startIn;
            this->startBehavior = startBehavior;
        };

        virtual void check() override{
            if(started) {
                Timer::check();
            }else{
                if((millis() - Timer::setAtTime) >= startIn) {
                    started = true;
                    startBehavior();
                }
            }
        };
};
};