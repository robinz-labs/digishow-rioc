/*

  DigiShow RIOC
  User Channels for XIAO ESP32S3 Sense

  Copyright 2016-2025 Robin Zhang & Labs
  https://github.com/robinz-labs/digishow-rioc

  version 0.50
  compatible with digishow 1.6

  This program works with a XIAO ESP32S3 Sense AI camera kit.

  In this program, demonstrates how to add custom code and use the user channels to 
  transmit AI inference scores to a remote DigiShow app.

*/


// UNIT_ID can be set to a number between 1 and 254
// If UNIT_ID is set to 0 here, the unit ID can also be reconfigured later via remote messages

#define UNIT_ID 1
#define CHANNEL_COUNT 10

#include "RiocDevice.h"
#include "ROUserChannel.h"


// requires SSCMACore library to support XIAO ESP32S3 Sense
// see https://github.com/Seeed-Studio/Seeed_Arduino_SSCMACore

#include <SSCMA_Micro_Core.h>

#include <Arduino.h>
#include <esp_camera.h>

SET_LOOP_TASK_STACK_SIZE(40 * 1024);

SSCMAMicroCore instance;
SSCMAMicroCore::VideoCapture capture;

void setup()
{   
  Serial.begin(115200);
  initRioc(UNIT_ID, CHANNEL_COUNT);

  // init video capture
  MA_RETURN_IF_UNEXPECTED(capture.begin(SSCMAMicroCore::VideoCapture::DefaultCameraConfigXIAOS3));

  // init SSCMA Micro Core
  MA_RETURN_IF_UNEXPECTED(instance.begin(SSCMAMicroCore::Config::DefaultConfig));
}

void loop()
{
  processRioc();

  // transmit AI inference scores to the user channels
  auto frame = capture.getManagedFrame();
  MA_RETURN_IF_UNEXPECTED(instance.invoke(frame));

  // clear channels
  for (int i = 0; i < CHANNEL_COUNT; i++) {
    ROUserChannel* channel = userChannel(i);
    if (channel != NULL) channel->write(0);
  }

  // object detection scores
  for (const auto& box : instance.getBoxes()) {
    ROUserChannel* channel = userChannel(box.target);
    if (channel != NULL) channel->write(box.score*100);  
  }

  // classification scores
  for (const auto& cls : instance.getClasses()) {
    ROUserChannel* channel = userChannel(cls.target);
    if (channel != NULL) channel->write(cls.score*100);
  }
}