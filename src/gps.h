#include "imports.h"

class GpsSensor {
    private:
    SoftwareSerial* serial_connection;
    TinyGPSPlus gps;

    public:
    
    GpsSensor(int rx, int tx) {
        this->serial_connection = new SoftwareSerial(rx, tx); // RX=pin 10, TX=pin 11
        serial_connection->begin(9600); //This opens up communications to the GPS   
    }

    double* getLongLat() {
        while(this->serial_connection->available())//While there are characters to come from the GPS
        {
            Serial.println("available");
            gps.encode(this->serial_connection->read());//This feeds the serial NMEA data into the library one char at a time
        }

        if (gps.location.isUpdated()) {
            return new double [2] {gps.location.lat(), gps.location.lng()};
        }

        return new double[2] {32.16177, 34.88502};
    }
};

