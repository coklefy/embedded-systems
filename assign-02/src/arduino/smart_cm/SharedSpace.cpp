#include "SharedSpace.h"
#include "Config.h"

SharedSpace::SharedSpace(unsigned int led1pin, unsigned int led2pin, unsigned int led3pin, unsigned int proxyEchoPin, unsigned int proxyTrigPin, unsigned int potPin,  unsigned int pirPin, unsigned int buttonPin ): led1pin(led1pin), led2pin(led2pin), led3pin(led3pin), proxyEchoPin(proxyEchoPin), proxyTrigPin(proxyTrigPin), potPin(potPin), pirPin(pirPin), buttonPin(buttonPin) {}

void SharedSpace::init() {
    L1 = new Led(led1pin);
    L1->switchOff();
    L2 = new Led(led2pin);
    L2->switchOff();
    L3 = new Led(led3pin);
    L3->switchOff();

   button = new ButtonImpl(buttonPin);

	  proxy = new Sonar(proxyEchoPin, proxyTrigPin);
	  mov = false;
	  pres = false;
	  acceptCommands = false;
	  turnOnLeds = false;
	  takeCoffee = false;
	  coffeeFinished = false;
	  zuccheroQ = 0;
	  totCoffee = MAX_COFFEE;
}


int SharedSpace::getTotCoffee(){
	return totCoffee;
}

void SharedSpace::setTotCoffee(int val){
	totCoffee = val;
}

bool SharedSpace::thereIsCoffee(){
	return totCoffee > 0;
}

int SharedSpace::getZucchero(){
	return zuccheroQ;
}

void SharedSpace::setZucchero(int val){
	zuccheroQ = val;
}

bool SharedSpace::isTakeCoffee(){
	return takeCoffee;
}

void SharedSpace::setTakeCoffee(bool val){
	takeCoffee = val;
}


bool SharedSpace::isCoffeeFinished(){
	return coffeeFinished;
}

void SharedSpace::setCoffeeFinished(bool val){
	coffeeFinished = val;
}

bool SharedSpace::isTurnOnLeds(){
	return turnOnLeds;
}

void SharedSpace::setTurnOnLeds(bool val){
	turnOnLeds = val;
}


bool SharedSpace::isAcceptCommands(){
	return acceptCommands;
}

void SharedSpace::setAcceptCommands(bool val){
	acceptCommands = val;
}

bool SharedSpace::isMov() {
    return mov;
}

void SharedSpace::setMov(bool val) {
    mov = val;
}

bool SharedSpace::isPres() {
    return pres;
}

void SharedSpace::setPres(bool val) {
    pres = val;
}

Light* SharedSpace::getL1(){
		return L1;
}

Light* SharedSpace::getL2(){
		return L2;
}

Light* SharedSpace::getL3(){
		return L3;
}

Button* SharedSpace::getButton(){
  return button;
}

ProximitySensor* SharedSpace::getProxy(){
	return proxy;
}
