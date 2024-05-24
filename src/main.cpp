#include "Common.h"
#include "Scanner.h"
#include "MasterI2C.h"

MasterI2C Master;

void setup() {
  Serial.begin(9600);
  while(!Serial)
  {
    delay(1000);
  }
  Serial.println("Initialized Serial");
  Serial.println("Initializing I2C");
  Master.begin();
  Serial.println("Initialized I2C");


}

void loop() {
  scan();
  Serial.println("Scanning for I2C devices...");
  Master.scanForSlaves();
  Master.assignSlaveAddresses();
  Master.communicateWithSlaves();
  delay(5000); // Wait 5 seconds before next scan
}