Phase 2 was getting the basic electronics for the RC car to work.

The electronics at phase 2 consist of console controller connecting to an ESP32 using bluetooth. The ESP32 (transmitter) then sends the information to another ESP32 (reciever) where the inputs for the controller are converted into outputs (the servo and motor).

The reciever (ESP32) is powered from the 11.1V lipo battery. The voltage is stepped down (using the ESC) to 7.2V to power the servo, 5V to power the ESP32 and 3.3V for the wireless modules.