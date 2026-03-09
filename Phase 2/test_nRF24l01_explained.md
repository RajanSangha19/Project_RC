There are two files, test_reciever_code and test_transmitter_code.

Upload each of the codes to two different ESP32 boards. I used a custom PCB (files linked bellow) reducing interference. This isn't needed but it will help.

Ensure that there is a 1000uF capacitor between the positive and negative inputs of the wireless modules.

It is important to also have an external 3.3V power supply. The standard 3.3V on the ESP32 will not do. Also make sure that the ESP32 and the wireless modules share a common ground. The PCB does not include this.


PCB design --->

I designed the gerber file in easyEDA and I manufactured the board using PCBways PCB services. 

The PCB is desgined for the generic esp32 (ESP32 dev module as known on the arduino IDE).

I also soldered on female header pins to make adding and testing more components in the future easier.

Some pins on the female header pins will not work as they do not do anything because the ESP32 is using those pins for the wireless module. You can see on the board that there are pins that do not have anthing leading from it. This was kept in for simplicity.
