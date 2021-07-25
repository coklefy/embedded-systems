#ifndef ___LED__
#define ___LED__

#include "Light.h"
/* Led implements Light interface */
class Led: public Light{
  
    public:
        Led(int);
        void switchOn();
        void switchOff();
        
    private:
        int pin;
};

#endif
