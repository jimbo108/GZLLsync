#include <RFduinoGZLL.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "I2Cdev.h"

device_t role = HOST;

File sanityFile;
File timestampFile;

int printIter = 0;

int SCLpin = 0;
int SDApin = 1;
int SDpin = 6;

int timestampOne;
int timestampTwo;
int timestampThree;

bool hasStartSignal = false;

void sanityPrint()
{
  sanityFile = SD.open("sanity.txt", FILE_WRITE);
  sanityFile.print("Print successful.");
  sanityFile.close();
}

void timestampPrint(int timestamp)
{
  timestampFile = SD.open("tshost.txt", FILE_WRITE);
  timestampFile.print(printIter);
  timestampFile.print(" TIMESTAMP: ");
  timestampFile.print(timestamp);
  timestampFile.print("\n");
  timestampFile.close();
  printIter++;
}

void setup() 
{
  
  RFduinoGZLL.begin(role);
  Wire.beginOnPins(SCLpin, SDApin);
  SD.begin(SDpin);
  delay(1000);
  sanityPrint();
}

void loop() 
{
}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  if (device == DEVICE0) {
    timestampOne = micros();
    RFduinoGZLL.sendToDevice(device, "OK");
    hasStartSignal = true;
    timestampPrint(timestampOne);
  } else if (hasStartSignal && device == DEVICE1) {
    timestampTwo = micros();
    RFduinoGZLL.sendToDevice(device, "OK");
    timestampPrint(timestampTwo);
  } else if (hasStartSignal && device == DEVICE2) {
    timestampThree = micros();
    RFduinoGZLL.sendToDevice(device, "OK");
    timestampPrint(timestampThree);
  }

  
}
