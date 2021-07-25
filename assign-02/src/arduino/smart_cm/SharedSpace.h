#ifndef _SHARED_SPACE_
#define _SHARED_SPACE_

#include "Led.h"
#include "Sonar.h"
#include "ButtonImpl.h"

/* Class which contains all variables and objects with concurrent tasks */
class SharedSpace {
    public:
        SharedSpace(unsigned int led1pin, unsigned int led2pin, unsigned int led3pin, unsigned int proxyEchoPin, unsigned int proxyTrigPin, unsigned int potPin, unsigned int pirPin, unsigned int buttonPin );
        void init();

        bool isMov();
        bool isPres();
        bool isAcceptCommands();
		    bool isTurnOnLeds();
	      bool isCoffeeFinished();
	      bool isTakeCoffee();
	      bool thereIsCoffee();
		
		    void setMov(bool);
        void setPres(bool);
		    void setAcceptCommands(bool);
		    void setTurnOnLeds(bool);
		    void setCoffeeFinished(bool);
		    void setTakeCoffee(bool);
		    void setTotCoffee(int);
		    void setZucchero(int);
		    int  getTotCoffee();
		    int  getZucchero();


        Light* getL1();
        Light* getL2();
        Light* getL3();
        Button* getButton();
        ProximitySensor* getProxy();

    private:
        bool mov, pres, acceptCommands, turnOnLeds, coffeeFinished, takeCoffee;
		    int led1pin, led2pin, led3pin, proxyEchoPin, proxyTrigPin, potPin, buttonPin;
		    int  zuccheroQ, totCoffee, pirPin; 
        
		    Light* L1;
        Light* L2;
        Light* L3;
        Button* button;
        ProximitySensor* proxy;

};

#endif
