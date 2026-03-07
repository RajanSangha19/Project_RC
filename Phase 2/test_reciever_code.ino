#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



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


int x = 0;


RF24 radio(4, 5); // CE, CSN - set these yourself

const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);  
  radio.begin();
  radio.openReadingPipe(1, address);

  // Enable ACK payloads so we can send telemetry
  radio.enableAckPayload();
  radio.enableDynamicPayloads();

  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();



}

void loop() {
  if (radio.available()) {
    transmitter_packet trs;
    radio.read(&trs, sizeof(trs));

    // Prepare telemetry
    reciever_packet rcv;
    rcv.reciever_variable1 = x;
    rcv.reciever_variable2 = 10000-x;
    rcv.reciever_variable3 = x*2;

    // Attach telemetry to next ACK packet
    radio.writeAckPayload(1, &rcv, sizeof(rcv));
  }
  x ++;
  delay(5);
  }


