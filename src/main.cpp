#include "Common.h"
#include "Scanner.h"

// define all slaves here with their addresses
int MOTOR_SLAVE = 5;
int SENSOR_SLAVE = 6;
int SCREEN_SLAVE = 10;

struct MotorData {
  int pwmChannel;
  int dutyCycle;
} motorData;

float sensorData[8];

void changeMotorData(int pwmChannel, int procent) {
  motorData.pwmChannel = pwmChannel;
  // -100 to 100 remapped to 0 to 65535
  int dutyCycle = map(procent, -100, 100, 0, 65535);
  motorData.dutyCycle = dutyCycle;
}
void sendMotorData(int slave) {
  // Send a register byte to the slave
  Wire.beginTransmission(slave);
  Wire.write((byte *)&motorData, sizeof(motorData));
  Wire.endTransmission();
}

union {
  byte b[4];
  float f;
} u;

void requestSensorData(int slave, int length) {
  // Request data from the slave
  Wire.requestFrom(slave, length);
  int i = 0;
  while (Wire.available()) {    // While there are bytes available to read
    u.b[i++ % 4] = Wire.read();  // Read a byte and store it in the union
    if (i % 4 == 0) {  // If 4 bytes have been read
      sensorData[i / 4 - 1] = u.f;  // Interpret the 4 bytes as a float and store it in the array
    }
  }
  for (float x : sensorData) {  // Loop over each float in the array
    Serial.print(x);  // Print the float value
    Serial.print(", ");   // Add a space between values for readability
  }
}


// define functions above this line

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial)
  {
    delay(3000);
  }
}

void loop() {
  requestSensorData(SENSOR_SLAVE, 32);
  delay(1000);

  changeMotorData(0, 100);
  sendMotorData(MOTOR_SLAVE);
  delay(1000);

}