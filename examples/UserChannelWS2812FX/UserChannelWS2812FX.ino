/*

  DigiShow RIOC
  User Channels for WS2812FX

  Copyright 2016-2025 Robin Zhang & Labs
  https://github.com/robinz-labs/digishow-rioc

  version 0.50
  compatible with digishow 1.6

  This program works with a WS2812 (NeoPixel) RGB LED strip connected to an Arduino 
  Mega or a ESP32 board.

  In this program, demonstrates how to add custom code and use user channels to set 
  various blinking effects on the LEDs.

*/


// UNIT_ID can be set to a number between 1 and 254
// If UNIT_ID is set to 0 here, the unit ID can also be reconfigured later via remote messages

#define UNIT_ID 1
#define CHANNEL_COUNT 10

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
  ROUserChannel* channel1 = createUserChannel(1);
  ROUserChannel* channel2 = createUserChannel(2);
  ROUserChannel* channel3 = createUserChannel(3);
  ROUserChannel* channel4 = createUserChannel(4);
  ROUserChannel* channel5 = createUserChannel(5);
  ROUserChannel* channel6 = createUserChannel(6);
  channel1->write(_fxBrightness);
  channel2->write(_fxSpeed);
  channel3->write(_fxColorR);
  channel4->write(_fxColorG);
  channel5->write(_fxColorB);
  channel6->write(_fxMode);
  
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
  uint8_t  fxBrightness = userChannel(1)->read();
  uint16_t fxSpeed      = userChannel(2)->read();
  uint8_t  fxColorR     = userChannel(3)->read();
  uint8_t  fxColorG     = userChannel(4)->read();
  uint8_t  fxColorB     = userChannel(5)->read();
  uint8_t  fxMode       = userChannel(6)->read();

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
