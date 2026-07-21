The remote will control the RC car.

At the moment 2 lion 3.3V batteries are powering an ESP32 (connected to the wireless modules explained in phase 2), which is connected in parallel to a switch (to turn it on and off). 

I could design an entirely new remote but that would involve hours of CAD design. So instead I decided to use a console controller (in my case a nintendo switch controller) that would send inputs to an esp32 that would process the information and send it to the reciever (for longer distance usage).

To do this I used the Bluepad32 library which allows an ESP32 to connect to the controller. Any controller that uses bluetooth can be used as the Bluepad32 library has a wide support for devices.