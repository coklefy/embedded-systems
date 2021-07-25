#ifndef _PROXIMITY_SENSOR_
#define _PROXIMITY_SENSOR_

/* Root class for all kinds of proximity sensor */
class ProximitySensor {

    public:
        virtual float getDistance() = 0;
};

#endif // _PROXIMITY_SENSOR_
