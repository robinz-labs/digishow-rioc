/*

	DigiShow RIOC
	Optional Settings

	NOTE: Please edit file RiocOptional.h for more option settings.

	Before you decide to enable optional components, 
	make sure that the necessary libraries are installed.

*/

#pragma once

// library Adafruit_NeoPixel is required to enable option RGBLED
// http://github.com/adafruit/Adafruit_NeoPixel

// #define OPT_ENABLE_RGBLED


// library DHT is required to enable option THERMOMETER
// http://arduino.cc/playground/Main/DHTLib

// #define OPT_ENABLE_THERMOMETER


#if not defined(__SAM3X8E__) 

// library Arduino-IRremote is required to enable option IR_TRANSMITTER and IR_RECEIVER
// http://z3t0.github.io/Arduino-IRremote/

// #define OPT_ENABLE_IR_TRANSMITTER
// #define OPT_ENABLE_IR_RECEIVER

#endif


// use software tone playing 

#if defined(OPT_ENABLE_IR_TRANSMITTER) || defined(OPT_ENABLE_IR_RECEIVER) || defined(__SAM3X8E__) 
	#define OPT_SOFTWARE_TONE
#endif


// need enable the option if the board uses an USB virtual serial port for RIOC messaging,
// such as Arduino Leonardo, Micro or Raspberry Pi Pico, etc.

#if defined(__AVR_ATmega32U4__) || defined(ARDUINO_ARCH_RP2040) 
	#define OPT_USB_VIRTUAL_SERIAL
#endif


// need enable the option if your arduino is an aladdin 2560 user device

// #define OPT_UD_ALADDIN


// need enable the option if your custom code requires more available program storage space on the arduino
// once uses LITE option, RIOC only supports basic IO and user channels. 

// #define OPT_RIOC_LITE
