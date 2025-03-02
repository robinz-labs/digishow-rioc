/*

  DigiShow RIOC
  User Channels for Grove Vision AI

  https://github.com/robinz-labs/digishow-rioc


  This program works with a Grove Vision AI V2 camera sensor module mounted on
  a Seeed Studio XIAO ESP32C3 (or any other ESP32 board).

  In this program, demonstrates how to add custom code and use the user channels 
  to transmit AI inference scores to a remote DigiShow app.

*/

#define UNIT_ID       1  // RIOC unit ID
#define CHANNEL_COUNT 10 // number of user channels

#include "RiocDevice.h"

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
      writeUserChannel(i, 0);
    }
    
    // object detection scores
    for (int i = 0; i < AI.boxes().size(); i++) {
    
      int target = AI.boxes()[i].target;
      int score = AI.boxes()[i].score;

      writeUserChannel(target, score); // value range of scores: 0 ~ 100
    }

    // classification scores
    for (int i = 0; i < AI.classes().size(); i++) {
    
      int target = AI.classes()[i].target;
      int score = AI.classes()[i].score;

      writeUserChannel(target, score); // value range of scores: 0 ~ 100
    }
  }

}
