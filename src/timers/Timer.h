#pragma once
#include <string>

/*
 * Description: The Timer class behaves simply as a timer. When it is created
 * Author:
 * Date:
 */

namespace Timing
{
    class Timer
    {
    protected:
        unsigned long setAtTime;
        unsigned long timerLength;
        bool complete;
        String name;
        String msg;

        virtual void goOff()
        {
            String output = "";
            if (name != NULL)
            {
                output += name + " has gone off with message: { \n";
                if (msg != NULL)
                {
                    output += msg + "\n }";
                }
            }
            complete = true;
        };

    public:
        ~Timer()
        {
            Serial.println("destorying Timer " + name);
        }
        Timer(unsigned long setAtTime, unsigned long timerLength)
        {
            this->timerLength = timerLength;
            this->setAtTime = setAtTime;
        };
        Timer(unsigned long setAtTime, unsigned long timerLength, String name)
        {
            this->timerLength = timerLength;
            this->name = name;
            this->setAtTime = setAtTime;
        };
        Timer(unsigned long setAtTime, unsigned long timerLength, String name, String msg)
        {
            this->timerLength = timerLength;
            this->name = name;
            this->msg = msg;
            this->setAtTime = setAtTime;
        };

        String getMessage()
        {
            return msg;
        };
        String getName()
        {
            return name;
        };
        unsigned long getTimerLength()
        {
            return timerLength;
        };
        bool isComplete()
        {
            return complete;
        };

        void check()
        {
            Serial.println("Timer check was used!");
            if ((millis() - setAtTime) >= timerLength && !complete)
            {
                goOff();
            }
        };

        void reset()
        {
            complete = false;
            setAtTime = millis();
        }
    };
};
