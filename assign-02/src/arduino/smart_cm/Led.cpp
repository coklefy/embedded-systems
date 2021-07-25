#include "Led.h"
#include "Arduino.h"

/* Implement Led methods */
Led::Led(int pinNr): pin(pinNr) {
    pinMode(pinNr, OUTPUT);
}

void Led::switchOn(){
    Light::switchOn();
    digitalWrite(this->pin, HIGH);
}

void Led::switchOff(){
    Light::switchOff();
    digitalWrite(this->pin, LOW);
}
