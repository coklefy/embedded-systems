#include "Potenziometro.h"
#include "Arduino.h"

/* Constructor of button */
Potenziometro::Potenziometro(int pinNr): pin(pinNr) {
    pinMode(pinNr, INPUT);
}

/* Return the value sets from the Potenziometro */
int Potenziometro::getValue(){
    return analogRead(this->pin);
}
