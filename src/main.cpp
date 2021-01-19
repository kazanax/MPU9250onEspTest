#include <Arduino.h>

#include "MPU9250.h"

#define AHRS false         // Set to false for basic data read

int intPin = 5;

#define I2Cclock 400000
#define I2Cport Wire
#define MPU9250_ADDRESS MPU9250_ADDRESS_AD0

MPU9250 myIMU(MPU9250_ADDRESS, I2Cport, I2Cclock);

void setup() 
{
  Wire.begin(SDA, SCL);
  Serial.begin(115200);
  while(!Serial){};

  pinMode(intPin, INPUT);
  digitalWrite(intPin, LOW);
  
  byte c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  Serial.print(F("MPU9250 I AM 0x"));
  Serial.print(c, HEX);
  Serial.print(F(" I should be 0x"));
  Serial.println(0x71, HEX);

  if (c == 0x71)
  {
    myIMU.MPU9250SelfTest(myIMU.selfTestFloat); 
    Serial.println("IMU Self-test values");
    Serial.print(myIMU.selfTest[0]); Serial.println(": X accel");
    Serial.print(myIMU.selfTest[1]); Serial.println(": Y accel");
    Serial.print(myIMU.selfTest[2]); Serial.println(": Z accel");
    Serial.print(myIMU.selfTest[3]); Serial.println(": X Gyro");
    Serial.print(myIMU.selfTest[4]); Serial.println(": Y Gyro");
    Serial.print(myIMU.selfTest[5]); Serial.println(": Z Gyro");
    Serial.println("");
    Serial.print(F("x-axis self test: acceleration trim within : "));
    Serial.print(myIMU.selfTest[0],1); Serial.println("% of factory value");
    Serial.print(F("y-axis self test: acceleration trim within : "));
    Serial.print(myIMU.selfTest[1],1); Serial.println("% of factory value");
    Serial.print(F("z-axis self test: acceleration trim within : "));
    Serial.print(myIMU.selfTest[2],1); Serial.println("% of factory value");
    Serial.print(F("x-axis self test: gyration trim within : "));
    Serial.print(myIMU.selfTest[3],1); Serial.println("% of factory value");
    Serial.print(F("y-axis self test: gyration trim within : "));
    Serial.print(myIMU.selfTest[4],1); Serial.println("% of factory value");
    Serial.print(F("z-axis self test: gyration trim within : "));
    Serial.print(myIMU.selfTest[5],1); Serial.println("% of factory value");
  }

  myIMU.initMPU9250();
  byte d = myIMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
    Serial.print("AK8963 ");
    Serial.print("I AM 0x");
    Serial.print(d, HEX);
    Serial.print(" I should be 0x");
    Serial.println(0x48, HEX);

  if (d == 0x48)
  {
    myIMU.AK8963GetSensivity();
    Serial.print("Magmetometer sensivity X: ");
    Serial.println(myIMU.magSensX);
    Serial.print("Magmetometer sensivity Y: ");
    Serial.println(myIMU.magSensY);
    Serial.print("Magmetometer sensivity Z: ");
    Serial.println(myIMU.magSensZ);
    Serial.print("AK8963 Self-Test pass: ");
    
    Serial.println(myIMU.AK8963SelfTest());
    Serial.print("AK8963 selftest X: ") ;
    Serial.println(myIMU.magSTX);
    Serial.print("AK8963 selftest Y: ") ;
    Serial.println(myIMU.magSTY);
    Serial.print("AK8963 selftest Z: ") ;
    Serial.println(myIMU.magSTZ);
  
  }
  

}

void loop()
{
 

}


