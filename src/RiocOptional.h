/*

	DigiShow RIOC
	Optional Settings

	NOTE: 
	Please edit the file RiocOptional.h to customize your build with more compilation options to fit 
	the program storage and dynamic memory space on your Arduino.
	
	Before you decide to enable some options, make sure that the necessary libraries are installed.

	library Adafruit_NeoPixel is required for option OPT_ENABLE_RGBLED
	http://github.com/adafruit/Adafruit_NeoPixel

	library DHT is required for option OPT_ENABLE_THERMOMETER
	http://arduino.cc/playground/Main/DHTLib
	
	library Arduino-IRremote is required for options OPT_ENABLE_IR_TRANSMITTER and OPT_ENABLE_IR_RECEIVER
	http://z3t0.github.io/Arduino-IRremote/
*/

#pragma once

#define OPT_RIOC_STANDARD

#if defined(OPT_RIOC_FULL)

	#define OPT_ENABLE_AOUT
	#define OPT_ENABLE_UART
	#define OPT_ENABLE_MULTI_DIN
	#define OPT_ENABLE_MULTI_DOUT
	#define OPT_ENABLE_MOTOR
	#define OPT_ENABLE_STEPPER
	#define OPT_ENABLE_RUDDER
	#define OPT_ENABLE_ENCODER
	#define OPT_ENABLE_ULTRASONIC
//	#define OPT_ENABLE_THERMOMETER
	#define OPT_ENABLE_TONE
//	#define OPT_ENABLE_RGBLED
//	#define OPT_ENABLE_IR_TRANSMITTER
//	#define OPT_ENABLE_IR_RECEIVER

#elif defined(OPT_RIOC_STANDARD)

//	#define OPT_ENABLE_AOUT
//	#define OPT_ENABLE_UART
//	#define OPT_ENABLE_MULTI_DIN
//	#define OPT_ENABLE_MULTI_DOUT
//	#define OPT_ENABLE_MOTOR
	#define OPT_ENABLE_STEPPER
	#define OPT_ENABLE_RUDDER
	#define OPT_ENABLE_ENCODER
//	#define OPT_ENABLE_ULTRASONIC
//	#define OPT_ENABLE_THERMOMETER
	#define OPT_ENABLE_TONE
//	#define OPT_ENABLE_RGBLED
//	#define OPT_ENABLE_IR_TRANSMITTER
//	#define OPT_ENABLE_IR_RECEIVER

#elif defined(OPT_RIOC_LITE)

//	#define OPT_ENABLE_AOUT
//	#define OPT_ENABLE_UART
//	#define OPT_ENABLE_MULTI_DIN
//	#define OPT_ENABLE_MULTI_DOUT
//	#define OPT_ENABLE_MOTOR
//	#define OPT_ENABLE_STEPPER
	#define OPT_ENABLE_RUDDER
//	#define OPT_ENABLE_ENCODER
//	#define OPT_ENABLE_ULTRASONIC
//	#define OPT_ENABLE_THERMOMETER
	#define OPT_ENABLE_TONE
//	#define OPT_ENABLE_RGBLED
//	#define OPT_ENABLE_IR_TRANSMITTER
//	#define OPT_ENABLE_IR_RECEIVER

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
