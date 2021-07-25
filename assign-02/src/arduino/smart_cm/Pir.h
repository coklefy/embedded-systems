#ifndef _PIR_
#define _PIR_

#include "MotionSensor.h"

/* Create the Pir sensor class */
class Pir: public MotionSensor {   /* implement MotionSensor interface */
    public:
        Pir (int);                  /* constructor with integer parameter */
        bool motionDetected();

    private:
        int pin;
}  ;

#endif // _PIR_
