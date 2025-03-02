/*

  DigiShow RIOC
  User Channels for XIAO ESP32S3 Sense

  https://github.com/robinz-labs/digishow-rioc


  This program works with a XIAO ESP32S3 Sense AI camera kit.

  In this program, demonstrates how to add custom code and use the user channels to 
  transmit AI inference scores to a remote DigiShow app.

*/

#define UNIT_ID       1  // RIOC unit ID
#define CHANNEL_COUNT 10 // number of user channels

#include "RiocDevice.h"

// requires SSCMACore library to support XIAO ESP32S3 Sense
// see https://github.com/Seeed-Studio/Seeed_Arduino_SSCMACore

#include <SSCMA_Micro_Core.h>
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
    writeUserChannel(i, 0);
  }

  // object detection scores
  for (const auto& box : instance.getBoxes()) {
    writeUserChannel(box.target, box.score*100); // value range of scores: 0 ~ 100
  }

  // classification scores
  for (const auto& cls : instance.getClasses()) {
    writeUserChannel(cls.target, cls.score*100); // value range of scores: 0 ~ 100
  }
}