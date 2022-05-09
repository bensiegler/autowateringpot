#pragma once
#include "Trigger.h"

namespace Timing {
    class RepeatableTrigger : public Trigger {
        private:
            bool repeat = true;

        protected:
            virtual void goOff() override{
                Serial.println(name + " going off");
                Trigger::goOff();
                if(repeat) {
                    Timer::reset();
                }
            }

        public:
            RepeatableTrigger(unsigned long timerLength, void (*endBehavior)()) : Trigger(timerLength, endBehavior){};
            RepeatableTrigger(unsigned long timerLength, void (*endBehavior)(), String name) : Trigger(timerLength, endBehavior, name){};
            RepeatableTrigger(unsigned long timerLength, void (*endBehavior)(), String name, String msg) : Trigger(timerLength, endBehavior, name, msg){};
            RepeatableTrigger(unsigned long timerLength, void (*endBehavior)(), bool repeat) : Trigger(timerLength, endBehavior){
                this->repeat = repeat;
            };
            RepeatableTrigger(unsigned long timerLength, void (*endBehavior)(), bool repeat, String name) : Trigger(timerLength, endBehavior, name){
                this->repeat = repeat;
            };
            RepeatableTrigger(unsigned long timerLength, void (*endBehavior)(), bool repeat, String name, String msg) : Trigger(timerLength, endBehavior, name, msg){
                this->repeat = repeat;
            };

            void setRepeat(bool repeat) {
                this->repeat = repeat;
            }

            bool isRepeating() {
                return repeat;
            }
    };
};