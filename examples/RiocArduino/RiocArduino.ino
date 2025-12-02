/*

  DigiShow RIOC
  Remote IO Control for Arduino

  Copyright 2016-2025 Robin Zhang & Labs
  https://github.com/robinz-labs/digishow-rioc

  version 0.53
  compatible with digishow 1.7.5 or later

  This program has been tested with Arduino UNO, Nano, MEGA, Leonardo and Micro. 
  This version is also partially compatible with some other types of boards, 
  such as ESP32 and RP2040.

  Normally you don't need to edit this file, and you just upload this sketch program 
  to your Arduino. Then through the USB serial port, the DigiShow app can remotely 
  control the sensors and actuators connected to the IO pins on the Arduino board.

*/


// UNIT_ID can be set to a number between 1 and 254
// If UNIT_ID is set to 0 here, the unit ID can also be reconfigured later via remote messages

#define UNIT_ID 1

#include "RiocDevice.h"

void setup()
{
  Serial.begin(115200);
  initRioc(UNIT_ID);

  // TODO: Add your custom code here
}

void loop()
{
  processRioc();

  // TODO: Add your custom code here
}
