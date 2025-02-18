/*

  DigiShow RIOC
  User Channels for Grove Vision AI

  Copyright 2016-2025 Robin Zhang & Labs
  https://github.com/robinz-labs/digishow-rioc

  version 0.50
  compatible with digishow 1.6

  This program works with a Grove Vision AI V2 camera sensor module mounted on
  a Seeed Studio XIAO ESP32C3 (or any other ESP32 board).

  In this program, demonstrates how to add custom code and use the user channels to 
  transmit AI inference scores to a remote DigiShow app.

*/


// UNIT_ID can be set to a number between 1 and 254
// If UNIT_ID is set to 0 here, the unit ID can also be reconfigured later via remote messages

#define UNIT_ID 1
#define CHANNEL_COUNT 10

#include "RiocDevice.h"
#include "ROUserChannel.h"


// requires SSCMA library to support Grove Vision AI V2
// see https://github.com/Seeed-Studio/Seeed_Arduino_SSCMA

#include <Seeed_Arduino_SSCMA.h>

SSCMA AI;

void setup()
{   
  Serial.begin(115200);
  initRioc(UNIT_ID, CHANNEL_COUNT);

  // initialize Vision AI module
  AI.begin();
}

void loop()
{
  processRioc();

  // transmit AI inference scores to the user channels
  if (!AI.invoke()) {
    
    // clear channels
    for (int i = 0; i < CHANNEL_COUNT; i++) {
        ROUserChannel* channel = userChannel(i);
        if (channel != NULL) channel->write(0);
    }

    // object detection scores
    for (int i = 0; i < AI.boxes().size(); i++) {
    
      int target = AI.boxes()[i].target;
      int score = AI.boxes()[i].score;

      ROUserChannel* channel = userChannel(target);
      if (channel != NULL) channel->write(score);
    }

    // classification scores
    for (int i = 0; i < AI.classes().size(); i++) {
    
        int target = AI.classes()[i].target;
        int score = AI.classes()[i].score;

        ROUserChannel* channel = userChannel(target);
        if (channel != NULL) channel->write(score);
    }
  }

}
