/*

  DigiShow RIOC
  User Channels for LIS3DHTR Accelerometer

  Copyright 2016-2025 Robin Zhang & Labs
  https://github.com/robinz-labs/digishow-rioc

  version 0.50
  compatible with digishow 1.6

  This program works with a LIS3DHTR accelerometer connected to the I2C port on an 
  Arduino board.

  In this program, demonstrates how to add custom code and use the user channels to 
  transmit 3-axis acceleration values to a remote DigiShow app.

*/


// UNIT_ID can be set to a number between 1 and 254
// If UNIT_ID is set to 0 here, the unit ID can also be reconfigured later via remote messages

#define UNIT_ID 1
#define CHANNEL_COUNT 3

#include "RiocDevice.h"
#include "ROUserChannel.h"

// requires the LIS3DHTR library
// see https://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR

#include "LIS3DHTR.h"
#include <Wire.h>
LIS3DHTR<TwoWire> LIS;

uint32_t _t = 0;

void setup()
{   
  Serial.begin(115200);
  initRioc(UNIT_ID, CHANNEL_COUNT);

  // initialize user channels 
  ROUserChannel* channel0 = createUserChannel(0); // x
  ROUserChannel* channel1 = createUserChannel(1); // y
  ROUserChannel* channel2 = createUserChannel(2); // z
  
  // init LIS3DHTR
  LIS.begin(Wire, 0x19); //use IIC
  delay(100);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  while (!LIS) delay(100);
}

void loop()
{
  processRioc();

  // read the accelerometer every few milliseconds
  // output x-y-z values to user channels
  uint32_t t = millis() / 50;
  if (t != _t) {
    _t = t;

    // value range: -10.0G ~ +10.0G
    float fx = LIS.getAccelerationX(); 
    float fy = LIS.getAccelerationY(); 
    float fz = LIS.getAccelerationZ();

    // value range: 0 ~ 20000
    int x = constrain(fx*1000, -10000, 10000) + 10000;
    int y = constrain(fy*1000, -10000, 10000) + 10000;
    int z = constrain(fz*1000, -10000, 10000) + 10000;
    
    userChannel(0)->write(x);
    userChannel(1)->write(y);
    userChannel(2)->write(z);
  }
}
