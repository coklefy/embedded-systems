#ifndef _MOTIONSENSOR_
#define _MOTIONSENSOR_

/* Root class for all kinds of movement sensor */
class MotionSensor {
    public:
        virtual bool motionDetected() = 0;
};

#endif

