/*

  DigiShow RIOC
  User Channel Demonstration

  https://github.com/robinz-labs/digishow-rioc


  This program has been tested with Arduino UNO, Nano, MEGA and ESP32 boards.

  In this program, demonstrates how to add custom code and use (read and write) user channels to 
  exchange variables with a remote DigiShow app. 

  Usually custom code can contain some logic and drivers to support specific complex IO components, 
  and use user channels to output sensor values or input actuator parameters.

  Upload this sketch to your Arduino, also find an DigiShow project file enclosed in the path
  <your documents directory>/Arduino/libraries/DigiShow_RIOC/examples/UserChannels/UserChannelDemo
  open and start it in the DigiShow LINK app to work with your Arduino.

*/

#define UNIT_ID       1 // RIOC unit ID
#define CHANNEL_COUNT 3 // number of user channels

#include "RiocDevice.h"

void setup()
{   
  Serial.begin(115200);
  initRioc(UNIT_ID, CHANNEL_COUNT);

  // initialize user channels 
  // the values of the channels created here can be read or written later
  // by both this Arduino or a remote DigiShow app 
  createUserChannel(0);
  createUserChannel(1);
  createUserChannel(2);
  
  // write user channels
  writeUserChannel(0, 100000);
  writeUserChannel(1, 200000);
  writeUserChannel(2, 300000);
}

void loop()
{
  processRioc();

  // execute every 50 milliseconds
  static uint32_t _t = 0;
  uint32_t t = millis() / 50;
  if (t != _t) {
    _t = t;

    for (int n=0 ; n<3 ; n++) {

      // read the user channel value
      uint32_t value = readUserChannel(n);

      // update the dummy value
      value += random(5000);
      if (value > 1000000) value = 0;

      // write the value to the user channel
      writeUserChannel(n, value);
    }
  }
}
