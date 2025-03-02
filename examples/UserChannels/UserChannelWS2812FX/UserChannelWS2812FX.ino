/*

  DigiShow RIOC
  User Channels for WS2812FX

  https://github.com/robinz-labs/digishow-rioc


  This program works with a WS2812 NeoPixel RGB LED strip connected to an Arduino MEGA or 
  a ESP32 board.

  In this program, demonstrates how to add custom code and use user channels to set various 
  blinking effects on the WS2812 (NeoPixel) LEDs.

  Upload this sketch to your Arduino, also find a DigiShow project file enclosed in the path
  <your documents directory>/Arduino/libraries/DigiShow_RIOC/examples/UserChannels/UserChannelWS2812FX
  open and start it in the DigiShow LINK app to work with your Arduino.

  No enough storage on Arduino UNO! If you want to compile this skech for an Arduino UNO 
  with a 32K program storage limit, please edit the file RiocOptional.h located in the path 
  <your documents directory>/Arduino/libraries/DigiShow_RIOC/src/
  and replace #define OPT_RIOC_STANDARD with #define OPT_RIOC_LITE for more free program 
  storage space to place the WS2812FX library.

*/

#define UNIT_ID       1 // RIOC unit ID
#define CHANNEL_COUNT 7 // number of user channels

#include "RiocDevice.h"

// requires the WS2812FX library by Harm Aldick
#include <WS2812FX.h>

#define LED_COUNT 10
#define LED_PIN 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// WS2812FX parameters
uint8_t  _fxBrightness = 30;
uint16_t _fxSpeed = 1000;
uint8_t  _fxColorR = 0x00;
uint8_t  _fxColorG = 0x7B;
uint8_t  _fxColorB = 0xFF;
uint8_t  _fxMode = FX_MODE_TWINKLEFOX; //FX_MODE_STATIC

void setup()
{   
  Serial.begin(115200);
  initRioc(UNIT_ID, CHANNEL_COUNT);

  // initialize user channels 
  createUserChannel(0);
  createUserChannel(1);
  createUserChannel(2);
  createUserChannel(3);
  createUserChannel(4);
  createUserChannel(5);
  createUserChannel(6);

  writeUserChannel(0, 0); // reserved
  writeUserChannel(1, _fxBrightness);
  writeUserChannel(2, _fxSpeed);
  writeUserChannel(3, _fxColorR);
  writeUserChannel(4, _fxColorG);
  writeUserChannel(5, _fxColorB);
  writeUserChannel(6, _fxMode);
  
  // initialize ws2812fx
  ws2812fx.init();
  ws2812fx.setBrightness(_fxBrightness);
  ws2812fx.setSpeed(_fxSpeed);
  ws2812fx.setColor(_fxColorR, _fxColorG, _fxColorB);
  ws2812fx.setMode(_fxMode);
  ws2812fx.start();
}

void loop()
{
  processRioc();

  // read user channels
  uint8_t  fxBrightness = readUserChannel(1);
  uint16_t fxSpeed      = readUserChannel(2);
  uint8_t  fxColorR     = readUserChannel(3);
  uint8_t  fxColorG     = readUserChannel(4);
  uint8_t  fxColorB     = readUserChannel(5);
  uint8_t  fxMode       = readUserChannel(6);

  // update ws2812fx parameters 
  if (_fxBrightness != fxBrightness) {
    _fxBrightness = fxBrightness;
    ws2812fx.setBrightness(_fxBrightness == 0 ? 1 : _fxBrightness); 
  }
  if (_fxSpeed != fxSpeed) {
    _fxSpeed = fxSpeed;
    ws2812fx.setSpeed(_fxSpeed); 
  }
  if (_fxColorR != fxColorR || _fxColorG != fxColorG || _fxColorB != fxColorB) {
    _fxColorR = fxColorR;
    _fxColorG = fxColorG;
    _fxColorB = fxColorB;
    ws2812fx.setColor(_fxColorR, _fxColorG, _fxColorB); 
  }
  if (_fxMode != fxMode) {
    _fxMode = fxMode;
    ws2812fx.setMode(_fxMode);
  }

  ws2812fx.service();
}
