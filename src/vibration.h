#include "imports.h"

class VibrationSensor {
    private:
    uint16 pin;
    int NO_MOVEMENT = 1024;

    public:

    VibrationSensor(uint16 pin) {
        this->pin = pin;
    }

    int getVibrationValue() {
        return analogRead(this->pin);
    }

    bool isMoving() {
        return getVibrationValue() != this->NO_MOVEMENT;
    }
};