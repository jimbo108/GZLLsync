#include <RFduinoGZLL.h>
#include <SD.h>
#include <Wire.h>

device_t role = DEVICE2;

File sanityFile;
File timestampFile;

int SCLpin = 0;
int SDApin = 1;
int SDpin = 6;

int timestampBegin;
int timestampEnd;

bool hasResponse = false;

void sanityPrint()
{
  sanityFile = SD.open("sanity.txt", FILE_WRITE);
  sanityFile.print("Print successful.");
  sanityFile.close();
}

void timestampPrint()
{
  timestampFile = SD.open("tsfile.txt", FILE_WRITE);
  timestampFile.print("TIMESTAMP BEGIN: ");
  timestampFile.print(timestampBegin);
  timestampFile.print("\n");
  timestampFile.print("TIMESTAMP END: ");
  timestampFile.print(timestampEnd);
  timestampFile.close();
}

void startRoundtrip()
{
  timestampBegin = micros();
  // Data is irrelevant
  RFduinoGZLL.sendToHost(1);
  
}


void setup() 
{
  RFduinoGZLL.begin(role);
  Wire.beginOnPins(SCLpin, SDApin);
  SD.begin(SDpin);
  sanityPrint();
  delay(10000);
  startRoundtrip();
}

void loop() 
{
 // while (!hasResponse) {
 //   delay(5000);
 //   startRoundtrip();
 // }
}
void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
//  if (len != 0) {
  timestampEnd = micros();
//  hasResponse = true;
 timestampPrint();
//  }
}
