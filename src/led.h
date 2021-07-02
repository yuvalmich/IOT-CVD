#include "imports.h"

class LedActuator {
    private:
    int pin;

    public:
    
    LedActuator(int pin) {
        this->pin = pin;
        pinMode(pin, OUTPUT);
    }

    void turnOn() {
        digitalWrite(this->pin, HIGH);
    }

    void turnOff() {
        digitalWrite(this->pin, LOW);
    }
};

