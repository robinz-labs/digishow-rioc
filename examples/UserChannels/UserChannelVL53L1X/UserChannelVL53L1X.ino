/*

  DigiShow RIOC
  User Channels for VL53L1X (also known as TOF400C) Time-of-flight Distance Sensor

  https://github.com/robinz-labs/digishow-rioc


  This program works with a VL53L1X sensor connected to the I2C port on an Arduino board.

  In this program, demonstrates how to add custom code and use the user channel to transmit 
  distance values to a remote DigiShow app.

  Upload this sketch to your Arduino, also find a DigiShow project file enclosed in the path
  <your documents directory>/Arduino/libraries/DigiShow_RIOC/examples/UserChannels/UserChannelVL53L1X
  open and start it in the DigiShow LINK app to work with your Arduino.

*/

#define UNIT_ID       1 // RIOC unit ID
#define CHANNEL_COUNT 1 // number of user channels

#include "RiocDevice.h"

// requires the VL53L1X library
// see https://github.com/pololu/vl53l1x-arduino

#include <Wire.h>
#include <VL53L1X.h>
VL53L1X sensor;

uint32_t _t = 0;

void setup()
{   
  Serial.begin(115200);
  initRioc(UNIT_ID, CHANNEL_COUNT);

  // initialize user channels 
  createUserChannel(0); // distance in mm
  
  // initialize sensor
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  sensor.setTimeout(500);
  if (sensor.init()) {
    
    // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
    // You can change these settings to adjust the performance of the sensor, but
    // the minimum timing budget is 20 ms for short distance mode and 33 ms for
    // medium and long distance modes. See the VL53L1X datasheet for more
    // information on range and timing limits.
    sensor.setDistanceMode(VL53L1X::Long);
    sensor.setMeasurementTimingBudget(50000);

    // Start continuous readings at a rate of one measurement every 50 ms (the
    // inter-measurement period). This period should be at least as long as the
    // timing budget.
    sensor.startContinuous(50);
  }
}

void loop()
{
  processRioc();

  // read the accelerometer every few milliseconds
  // output distance values to the user channel
  uint32_t t = millis() / 50;
  if (t != _t) {
    _t = t;

    // distance value in mm
    sensor.read();
    int distance = sensor.ranging_data.range_mm; 

    // write user channels
    writeUserChannel(0, distance);
  }
}
