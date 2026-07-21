#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ESP32Servo.h>

Servo esc;
Servo servo;

int throttle;
int steering;

// sending information to
struct transmitter_packet {
  int transmitter_throttle; 
  int transmitter_steering;
};

// sending information back - - NOTHING IS BEING SENT BACK YET BUT INCLUDED THIS FEATURE WILL BE VERY USEFUL IN THE FUTURE - -  
struct receiver_packet {
  int reciever_variable1;
  int reciever_variable2;
};

RF24 radio(4, 5); // CE, CSN - set these yourself - keep these if using the pcb on the gitub page

const byte address[6] = "00001";


void setupmotor(){
  //This procedure will set up the motor
  esc.attach(#####); // Set this to a pin to control the esc
  esc.writeMicroseconds(1500); // This initialises my motor, you can test this using the test_motor code in phase 2
  delay(3000);
}

void setupsteering(){
  //This procedure will set up the steering
  servo.attach(####); // Set this to a pin to control the servo
  servo.write(50); // set the servo to a zero position
}

void setupradio(){
  radio.begin();
  radio.openReadingPipe(1, address);

  // Enable ACK payloads so we can send telemetry
  radio.enableAckPayload();
  radio.enableDynamicPayloads();

  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}


void setup() {
  Serial.begin(115200);  
  setupradio();
  setupmotor();
  setupsteering();
}

void loop() {
  if (radio.available()) {
    
    transmitter_packet trs;

    radio.read(&trs, sizeof(trs));

    esc.writeMicroseconds(trs.transmitter_throttle);
    // The if statement is to ensure that servo does not use an extreme angle and brake the steering
    if (trs.transmitter_steering<71 && trs.transmitter_steering>39){
      servo.write(trs.transmitter_steering);
    }

    // - - NOTHING IS BEING SENT BACK YET BUT INCLUDED THIS FEATURE WILL BE VERY USEFUL IN THE FUTURE - - 
    receiver_packet rcv;
    // Attach telemetry to next ACK packet
    radio.writeAckPayload(1, &rcv, sizeof(rcv));
  }
  delay(1);
}


