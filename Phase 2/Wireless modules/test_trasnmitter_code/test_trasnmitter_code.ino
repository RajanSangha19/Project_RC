#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


int y  = 0;
//const int pin = 34;

RF24 radio(4, 5); // CE, CSN - set these pins yourself 

const byte address[6] = "00001"; // make sure that this address is this same on your reciever code 


// puts multiple values in one packet using structs
// sending information to
struct transmitter_packet {
  int transmitter_variable1; 
  int transmitter_variable2;
};

// sending information back 
struct reciever_packet {
  float reciever_variable1;
  float reciever_variable2;
  float reciever_variable3;
};



void setup() {
  Serial.begin(115200);
  radio.begin(); // initialise the radio hardware
  radio.openWritingPipe(address); // this is telling the transmitter where it is sending the packets to 
  // Enable ACK payloads so we can send telemetry
  radio.enableAckPayload(); // allows for the data to be sent 
  radio.enableDynamicPayloads();

  radio.setPALevel(RF24_PA_HIGH); // set for maximum range
  radio.setDataRate(RF24_250KBPS); 
  radio.stopListening();



}

void loop() {
  transmitter_packet trs; // creating packet variable
  trs.transmitter_variable1 = y;
  trs.transmitter_variable2 = 10000 - y;
  y ++;
  if (y==10000){
    y = 0;
  }
  bool success = radio.write(&trs, sizeof(trs)); // sends the struct packet to the reciever 
  // if sent --->
  if (success) {
    // line bellow checks if the reciever is sending anything back 
    if (radio.isAckPayloadAvailable()) {
      reciever_packet rcv; // creating packet
      radio.read(&rcv, sizeof(rcv)); // reading the information sent back to the transmitter

      Serial.print("Reciever Variable 1: "); Serial.println(rcv.reciever_variable1);
      Serial.print("Reciever Variable 2: "); Serial.println(rcv.reciever_variable2);
      Serial.print("Reciever Variable 3: "); Serial.println(rcv.reciever_variable3);
    }
  }

  delay(10);  // (100 packets/sec) 


}



