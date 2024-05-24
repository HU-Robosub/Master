#include "MasterI2C.h"

MasterI2C::MasterI2C() : slaveCount(0) {}

void MasterI2C::begin() {
    Wire.begin(); // Join I2C bus as master
}

void MasterI2C::scanForSlaves() {
    Serial.println("Scanning for I2C devices...");
    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();
        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            Serial.println(address, HEX);
            if (slaveCount < MAX_SLAVES) {
                slaveAddresses[slaveCount++] = address;
            }
        }
    }
    Serial.print("Number of I2C devices found: ");
    Serial.println(slaveCount);
}

void MasterI2C::assignSlaveAddresses() {
    for (int i = 0; i < slaveCount; i++) {
        int address = slaveAddresses[i];
        Wire.beginTransmission(address);
        Wire.write(i + 1); // New address (1 to MAX_SLAVES)
        Wire.endTransmission();

        slaveAddresses[i] = i + 1; // Update to the new address
    }
}

void MasterI2C::communicateWithSlaves() {
    for (int i = 0; i < slaveCount; i++) {
        int address = slaveAddresses[i];
        communicateWithSlave(address);
        delay(1000); // Wait for a second before the next communication
    }
}

void MasterI2C::communicateWithSlave(int address) {
    Wire.beginTransmission(address);
    Wire.write("Hello Slave");
    Wire.endTransmission();

    Wire.requestFrom(address, 13);
    while (Wire.available()) {
        char c = Wire.read();
        Serial.print(c);
    }
    Serial.println();
}
