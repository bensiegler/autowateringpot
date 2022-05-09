#pragma once
#include "Trigger.h"

typedef void (*interruptBehaviorPtr)();

//careful here! might have to test interaction between pause and interrupt functionality

namespace Timing {
class InterruptableTrigger: public Trigger {
    private:
        void (*interruptBehavior)();
        bool interrupted = false;
    protected:
        virtual void goOff() override{
            if(!interrupted) {
                Trigger::goOff();
            }
        }
    public:
        InterruptableTrigger
            (
                unsigned long timerLength, 
                void (*endBehavior)(), 
                void (*interruptBehavior)()): Trigger(timerLength, endBehavior) {
                this->interruptBehavior = interruptBehavior;
        };
        InterruptableTrigger
            (
                unsigned long timerLength, 
                void (*endBehavior)(), 
                void (*interruptBehavior)(),
                String name): Trigger(timerLength, endBehavior, name) {
                this->interruptBehavior = interruptBehavior;
        };
        InterruptableTrigger
            (
                unsigned long timerLength, 
                void (*endBehavior)(), 
                void (*interruptBehavior)(),
                String name,
                String msg ): Trigger(timerLength, endBehavior, name, msg) {
                this->interruptBehavior = interruptBehavior;
        };

        bool isInterrupted() {
            return interrupted;
        }

        interruptBehaviorPtr getInterruptBehavior() {
            return interruptBehavior;
        }

        void interrupt() {
            interrupted = true;
            interruptBehavior();
        }

};
};