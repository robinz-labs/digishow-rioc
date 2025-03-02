# DigiShow RIOC
 
DigiShow RIOC (Remote IO Control) is an Arduino library that enables Arduino GPIO to be reconfigured and controlled by a remote DigiShow app. 
 
Using DigiShow on your computer, it's easy to control sensors and actuators through an Arduino connected to your computer USB port. You don't need to program on the Arduino to control the IO, just upload the pre-prepared RIOC sketch to your Arduino board (or Arduino PLC). 
 
Enjoys, 
 
 
## How to make a RIOC Arduino ?
 
1. Need an Arduino MEGA, UNO, Nano or a ESP32 board. 

2. Open Library Manager in the Arduino IDE, find and install the library named DigiShow RIOC . 
 
3. Open the RIOC sketch from the Arduino IDE: File > Examples > DigiShow RIOC > RiocArduino. 
 
4. Upload the sketch to your Arduino board. 


## Add custom code and use user channels
 
You can open more examples named with the UserChannel prefix to learn how to add custom code and use user channels to exchange variables with a remote DigiShow app.  
 
Usually custom code can contain some logic and drivers to support specific complex IO components (such as AI cameras, accelerometers and NeoPixel LEDs), and use user channels to output sensor values or input actuator parameters. 
