/*

  DigiShow RIOC
  User Channel Demonstration

  Copyright 2016-2025 Robin Zhang & Labs
  https://github.com/robinz-labs/digishow-rioc

  version 0.50
  compatible with digishow 1.6

  This program has been tested with Arduino UNO, Duemilanove, Nano, MEGA and DUE. 
  This version is also partially compatible with some other types of boards, 
  such as ESP32 and RP2040.

  In this program, demonstrates how to add custom code and use (read and write) 
  user channels to exchange variables with a remote DigiShow app. 
  Usually custom code can contain some logic and drivers to support specific complex 
  IO components.

*/


// UNIT_ID can be set to a number between 1 and 254
// If UNIT_ID is set to 0 here, the unit ID can also be reconfigured later via remote messages

#define UNIT_ID 1
#define CHANNEL_COUNT 3

#include "RiocDevice.h"
#include "ROUserChannel.h"

uint32_t _t = 0;

void setup()
{   
  Serial.begin(115200);
  initRioc(UNIT_ID, CHANNEL_COUNT);

  // initialize user channels 
  ROUserChannel* channel0 = createUserChannel(0);
  ROUserChannel* channel1 = createUserChannel(1);
  ROUserChannel* channel2 = createUserChannel(2);
  channel0->write(100000);
  channel1->write(200000);
  channel2->write(300000);
}

void loop()
{
  processRioc();

  // process user channels
  // every few milliseconds
  uint32_t t = millis() / 50;
  if (t != _t) {
    _t = t;

    for (int n=0 ; n<3 ; n++) {
      ROUserChannel* channel = userChannel(n);
      if (channel != NULL) {
        uint32_t value = channel->read();
        value += random(5000);
        if (value > 1000000) value = 0;
        channel->write(value);
      }
    }
  }

}
