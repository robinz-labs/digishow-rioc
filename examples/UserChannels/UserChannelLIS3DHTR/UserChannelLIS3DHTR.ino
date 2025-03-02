/*

  DigiShow RIOC
  User Channels for LIS3DHTR Accelerometer

  https://github.com/robinz-labs/digishow-rioc


  This program works with a LIS3DHTR accelerometer connected to the I2C port on an Arduino 
  board.

  In this program, demonstrates how to add custom code and use the user channels to transmit 
  3-axis acceleration values to a remote DigiShow app.

  Upload this sketch to your Arduino, also find a DigiShow project file enclosed in the path
  <your documents directory>/Arduino/libraries/DigiShow_RIOC/examples/UserChannels/UserChannelLIS3DHTR
  open and start it in the DigiShow LINK app to work with your Arduino.

*/

#define UNIT_ID       1 // RIOC unit ID
#define CHANNEL_COUNT 3 // number of user channels

#include "RiocDevice.h"

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
  createUserChannel(0); // x
  createUserChannel(1); // y
  createUserChannel(2); // z
  
  // initialize accelerometer
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
    
    // write user channels
    writeUserChannel(0, x);
    writeUserChannel(1, y);
    writeUserChannel(2, z);
  }
}
