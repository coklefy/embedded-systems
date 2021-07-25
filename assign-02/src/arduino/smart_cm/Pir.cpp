#include "Pir.h"
#include "Arduino.h"

/* Pir constructor implementation */
Pir::Pir(int pinPort): pin(pinPort) {
    pinMode(pinPort, INPUT);
}

/* Method implementation to return true for HIGH sensor state
   or false for LOW sensor state */
bool Pir::motionDetected() {
    return digitalRead(this->pin) == HIGH;
}
