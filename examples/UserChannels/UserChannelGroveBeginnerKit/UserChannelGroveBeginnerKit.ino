/*

  DigiShow RIOC
  User Channels for Grove Beginner Kit

  https://github.com/robinz-labs/digishow-rioc


  This program works with Grove Beginner Kit for Arduino.
  see https://wiki.seeedstudio.com/Grove-Beginner-Kit-For-Arduino/

  In this program, demonstrates how to add custom code and use the user channels to transmit 
  values of LIS3DHTR accelerometer, BMP280 barometer and DHT20 temperature & humidity sensor 
  to a remote DigiShow app.

  Upload this sketch to your Arduino, also find a DigiShow project file enclosed in the path
  <your documents directory>/Arduino/libraries/DigiShow_RIOC/examples/UserChannels/UserChannelGroveBeginnerKit
  open and start it in the DigiShow LINK app to work with your Arduino.

*/

#define UNIT_ID       1 // RIOC unit ID
#define CHANNEL_COUNT 8 // number of user channels

#include "RiocDevice.h"

// requires the LIS3DHTR accelerometer library
// see https://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR

#include "LIS3DHTR.h"
#include <Wire.h>
LIS3DHTR<TwoWire> LIS;

// requires the BMP280 barometer library
// see https://github.com/Seeed-Studio/Grove_BMP280

#include "Seeed_BMP280.h"
BMP280 bmp280;

// requires the DHT temperature & humidity sensor library
// see https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor

#include "DHT.h"
DHT dht(DHT20);  

// requires the U8g2 display library
// see https://github.com/olikraus/u8g2

// #define OPT_ENABLE_DISPLAY

#ifdef OPT_ENABLE_DISPLAY
#include <U8x8lib.h>
#include "Wire.h"
U8X8_SSD1306_128X64_NONAME_HW_I2C display(/* reset=*/ U8X8_PIN_NONE);
uint32_t _dispValueA = 0;
uint32_t _dispValueB = 0;
#endif

uint32_t _t = 0;

void setup()
{   
  Serial.begin(115200);
  initRioc(UNIT_ID, CHANNEL_COUNT);

  // initialize user channels 
  createUserChannel(0);  // accelerometer - X
  createUserChannel(1);  // accelerometer - Y
  createUserChannel(2);  // accelerometer - Z
  createUserChannel(3);  // barometer - pressure
  createUserChannel(4);  // dht sensor - temperature
  createUserChannel(5);  // dht sensor - humidity
  createUserChannel(6);  // display - value A
  createUserChannel(7);  // display - value B

  // initialize accelerometer
  LIS.begin(Wire, 0x19); //use IIC
  delay(100);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  while (!LIS) delay(100);

  // initialize barometer
  bmp280.init();

  // initialize display
  #ifdef OPT_ENABLE_DISPLAY
  display.begin();
  display.setPowerSave(0);  
  display.setFlipMode(1);
  display.setFont(u8x8_font_chroma48medium8_r);
  #endif
}

void loop()
{
  processRioc();

  // read sensor values every few milliseconds
  uint32_t t = millis() / 50;
  if (t != _t) {
    _t = t;

    if (_t % 1  == 0) processAccelerometer();
    if (_t % 10 == 0) processBarometer();
    if (_t % 20 == 0) processDHTSensor();
    if (_t % 2  == 0) processDisplay();
  }
}

// read the accelerometer and
// output x-y-z values to user channels
void processAccelerometer() {

  // value range: -10.0G ~ +10.0G
  float fx = LIS.getAccelerationX(); 
  float fy = LIS.getAccelerationY(); 
  float fz = LIS.getAccelerationZ();

  // value range: 0 ~ 20000
  int x = constrain(fx*1000, -10000, 10000) + 10000;
  int y = constrain(fy*1000, -10000, 10000) + 10000;
  int z = constrain(fz*1000, -10000, 10000) + 10000;
  
  writeUserChannel(0, x);
  writeUserChannel(1, y);
  writeUserChannel(2, z);
}

// read the barometer and
// output air pressure value to user channel
void processBarometer() {

  // float temperature = bmp280.getTemperature();    // Celsius
  // uint32_t pressure = bmp280.getPressure();       // hPa
  // float altitude = bmp280.calcAltitude(pressure); // meter
  writeUserChannel(3, bmp280.getPressure());
}

// read the dht sensor and
// output temperature and humidity values to user channels
void processDHTSensor() {
    
  float humidity = dht.readHumidity();    // %
  float temperaC = dht.readTemperature(); // C
  float temperaK = temperaC + 273.15;     // K
  
  writeUserChannel(4, temperaK*100); 
  writeUserChannel(5, humidity*100);
}

// read user channels and update display
void processDisplay() {

  uint32_t dispValueA = readUserChannel(6);
  uint32_t dispValueB = readUserChannel(7);
  
  #ifdef OPT_ENABLE_DISPLAY
  if (dispValueA != _dispValueA || dispValueB != _dispValueB) {

    _dispValueA = dispValueA;
    _dispValueB = dispValueB;

    display.clearDisplay();

    display.setCursor(2,2);
    display.print("A: ");
    display.print(_dispValueA);

    display.setCursor(2,4);
    display.print("B: ");
    display.print(_dispValueB);

    display.refreshDisplay();
  }
  #endif
}
