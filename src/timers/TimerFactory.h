#pragma once
#include <string>
#include <vector>
#include <typeinfo>
#include <optional>

#include "Timer.h"
#include "Trigger.h"
#include "InterruptableTrigger.h"
#include "PassiveTimer.h"
#include "RepeatableTrigger.h"

using namespace std;

namespace Timing
{
    class TimerFactory
    {
    private:
        vector<Timer> activeTimers;
        // would like to merge this into active timers and differentiate by object type
        // in the update method. This would be a lot more elegant, but I need help with
        // with typeid()
        vector<PassiveTimer> passiveTimers;

    protected:
        // optional<Timer> getTimerByName(String name)
        // {
        //     optional<Timer> optionalTimer;
        //     for (auto i = activeTimers.begin(); i != activeTimers.end(); ++i)
        //     {
        //         if ((*i).getName() == name)
        //         {
        //             optionalTimer.emplace(*i);
        //         }
        //     }

        //     // for (auto i = passiveTimers.begin(); i != passiveTimers.end(); ++i)
        //     // {
        //     //     if ((*i).getName() == name)
        //     //     {
        //     //         return *i;
        //     //     }
        //     // }

        //     return optionalTimer;

        // };

        vector<Timer> getActiveTimers()
        {
            return activeTimers;
        }

        vector<PassiveTimer> getPassiveTimers()
        {
            return passiveTimers;
        }

    public:
        void update()
        {
            WITH_LOCK(activeTimers)
            {
                for (auto i = activeTimers.begin(); i != activeTimers.end(); ++i)
                {
                    Timer t = *i;
                    Serial.println("checking timer " + t.getName());
                    t.check();
                    Serial.println("delaying 1000ms");
                    // delay(1000);
                    Serial.println("checking if timer is complete");
                    if (t.isComplete())
                    {
                        Serial.println("erasing if complete");
                        activeTimers.erase(i);
                    }
                }
            }
        }

        Timer createNewTimer(unsigned long timerLength, String name, String msg)
        {
            Timer t = Timer(millis(), timerLength, name, msg);
            activeTimers.push_back(t);
            return t;
        };

        Timer createNewTimer(unsigned long timerLength, String name)
        {
            Timer t = Timer(millis(), timerLength, name);
            activeTimers.push_back(t);
            return t;
        };

        Timer createNewTimer(unsigned long timerLength)
        {
            Timer t = Timer(millis(), timerLength);
            activeTimers.push_back(t);
            return t;
        };

        RepeatableTrigger createNewRepeatableTrigger(unsigned long timerLength, void (*endBehavior)())
        {
            Serial.println("creating timer");
            RepeatableTrigger t = RepeatableTrigger(timerLength, endBehavior);
            Serial.println("pushing back");
            delay(1000);
            activeTimers.push_back(t);
            return t;
        };
        RepeatableTrigger createNewRepeatableTrigger(unsigned long timerLength, void (*endBehavior)(), String name)
        {
            Serial.println("creating timer");
            RepeatableTrigger t = RepeatableTrigger(timerLength, endBehavior, name);
            Serial.println("pushing back");
            delay(1000);
            activeTimers.push_back(t);
            return t;
        };

        Trigger createNewTrigger(unsigned long timerLength, void (*endBehavior)())
        {
            Trigger t = Trigger(timerLength, endBehavior);
            activeTimers.push_back(t);
            return t;
        }
    };
};
