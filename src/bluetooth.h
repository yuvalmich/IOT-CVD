#include "imports.h"

class BluetoothSensor {
    private:
    SoftwareSerial* serial_connection;
    bool isConnected;
    
    public:
    
    BluetoothSensor(int rx, int tx) {
        this->serial_connection = new SoftwareSerial(rx, tx);
        this->serial_connection->begin(9600);
        this->isConnected = false;
    }

    bool isParking() {
        return !this->isConnected;
    }

    void setConnection(bool isConnected) {
        this->isConnected = isConnected;
    }
    
};

