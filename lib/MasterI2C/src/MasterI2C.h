#ifndef MASTERI2C_H
#define MASTERI2C_H

#include <Arduino.h>
#include <Wire.h>

const int MAX_SLAVES = 10;

class MasterI2C {
public:
    MasterI2C();
    void begin();
    void scanForSlaves();
    void assignSlaveAddresses();
    void communicateWithSlaves();

private:
    int slaveAddresses[MAX_SLAVES];
    int slaveCount;

    void communicateWithSlave(int address);
};

#endif