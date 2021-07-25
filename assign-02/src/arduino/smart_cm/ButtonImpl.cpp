#include "ButtonImpl.h"
#include "Arduino.h"

/* Constructor of button */
ButtonImpl::ButtonImpl(int pinNr): pin(pinNr) {
    pinMode(pinNr, INPUT);
}

/* Return button state, true if HIGH, false if LOW */
bool ButtonImpl::isPressed(){
    return digitalRead(this->pin) == HIGH;
}
