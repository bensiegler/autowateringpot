#pragma once
#include "Timer.h"

namespace Timing {
    class PausableTimer: public Timer {
        private:
            bool paused;
            unsigned long pauseStartedAt;    

        protected:

            //want to get rid of this method but cant bcs Trigger cant seem to access Timer::goOff
            virtual void goOff() override{
                if(!paused) {
                    Timer::goOff();
                }
            };

        public:
            PausableTimer(unsigned long timerLength) : Timer(millis(), timerLength){};
            PausableTimer(unsigned long timerLength, String name) : Timer(millis(), timerLength, name){};
            PausableTimer(unsigned long timerLength, String name, String msg) : Timer(millis(), timerLength, name, msg){};
        
            virtual void check() {
                Serial.println("PausableTimer check was used!");
                if(!paused) {
                    Timer::check();
                }
            };
            void pause() {
                pauseStartedAt = millis();
                paused = true;
            };
            void resume() {
                Timer::timerLength += millis() - pauseStartedAt;
                paused = false;
            };
    };
};