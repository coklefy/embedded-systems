#ifndef _SONAR_
#define _SONAR_

#include "ProximitySensor.h"

class Sonar: public ProximitySensor {

    public:
        Sonar(int echoPin, int trigPin);
        float getDistance();

    private:
        const float vs = 331.5 + 0.6 * 20;
        int echoPin, trigPin;
};

#endif

