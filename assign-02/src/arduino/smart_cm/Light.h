#ifndef ___LIGHT__
#define ___LIGHT__

/* Create the Light interface */
class Light {
    public:
        virtual void switchOn(){           /* Turn the light on */
            switchedOn = true;
        }
        
        virtual void switchOff(){          /* Turn the light Off */
            switchedOn = false;
        }
        
        bool isSwitchedOn(){
            return switchedOn;
        }
        
    private:
        bool switchedOn;                   /* Light state */
};

#endif
