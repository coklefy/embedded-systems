#ifndef _MOTIONDETECTORTASK_
#define _MOTIONDETECTORTASK_

#include "MotionSensor.h"
#include "ConcurrentTask.h"

/* Class which manages movement detection */
class MotionDetectorTask: public ConcurrentTask {

    public:
        MotionDetectorTask(int pin, SharedSpace* sp);
        void init(int period);
        void tick();

    protected:
        int pin;
        MotionSensor* pir;

    /*
        STATES INFO:

        MDT0: no moves detected
        MDT1: moves detected
    */
    enum { NO_MOVEMENT, MOVEMENT} state;

};

#endif
