# DigiShow RIOC
 
RIOC just means Remote IO Control. DigiShow RIOC is an Arduino library that enables Arduino GPIO to be reconfigured and controlled by a remote DigiShow LINK app. 
 
Using DigiShow on your computer, it's easy to control sensors and actuators through an Arduino connected to your computer USB port, you don't need to program on the Arduino to control the IO, just upload the pre-prepared RIOC sketch to your Arduino board (or Arduino PLC). 
 
Enjoys, 
 
 
## How to make an Arduino with RIOC ?
 
1. Need an Arduino MEGA, UNO, Nano or a ESP32 board.
 
2. Download the latest version of the DigiShow RIOC library from GitHub or find it in the Extra folder of the DigiShow installation package. 
 
3. Add the library to your Arduino IDE by selecting Sketch > Include Library > Add .ZIP Library and choosing the downloaded file. 
 
4. Open the RIOC sketch from the Arduino IDE: File > Examples > DigiShow RIOC > RiocArduino. 
 
5. Upload the sketch to your Arduino board. 


## Add custom code and use user channels
 
You can open more examples named with the UserChannel prefix to learn how to add custom code and use user channels to exchange variables with a remote DigiShow app.  
 
Usually custom code can contain some logic and drivers to support specific complex IO components. 
