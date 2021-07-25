#ifndef _DETECTMOTION_
#define _DETECTMOTION_

/* Root class for all kinds of movement sensor */
class DetectMotion {
    public:
        virtual bool motionDetected() = 0;
};

#endif
