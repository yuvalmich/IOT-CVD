#include "imports.h"

class VibrationSensor {
    private:
    uint16 pin;
    int NO_MOVEMENT_FLAG = 1000;

    public:

    VibrationSensor(uint16 pin) {
        this->pin = pin;
    }

    int getVibrationValue() {
        return analogRead(this->pin);
    }

    bool isMoving() {
        int v = getVibrationValue();
        bool a = v < this->NO_MOVEMENT_FLAG;
        if(a) {
            Serial.println(v);
        }
        return a;

        // return getVibrationValue() < this->NO_MOVEMENT_FLAG;
    }
};