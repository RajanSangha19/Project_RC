#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Bluepad32.h>


// Before using this code it is important that you have installed the Bluepad32 libraries - there are many easy to follow guides online


// Create an object for the controller "mycontroller"
ControllerPtr myController = nullptr;

// Notice these lines of code are not called in this sketch.
// They are used to tell the ESP32 what to do if the controller connects or disconnects
void onConnectedController(ControllerPtr ctl) {
    myController = ctl;
    Serial.println("Controller connected!");
}

void onDisconnectedController(ControllerPtr ctl) {
    myController = nullptr;
    Serial.println("Controller disconnected!");
}
/////////////////////

RF24 radio(4, 5); // CE, CSN - set these pins yourself - keep these if using the pcb on the gitub page

const byte address[6] = "00001"; // make sure that this address is this same on your reciever code 

// puts multiple values in one packet using structs
// sending information to   

struct transmitter_packet {
  int transmitter_throttle; 
  int transmitter_steering;
};

// sending information back - - NOTHING IS BEING SENT BACK YET BUT INCLUDED THIS FEATURE WILL BE VERY USEFUL IN THE FUTURE - -  
struct reciever_packet {
  int reciever_variable1;
  int reciever_variable2;
};

void beginradio(){
  radio.begin(); // initialise the radio hardware
  radio.openWritingPipe(address); // this is telling the transmitter where it is sending the packets to 
  // Enable ACK payloads so we can send data
  radio.enableAckPayload(); // allows for the data to be sent 
  radio.enableDynamicPayloads();

  radio.setPALevel(RF24_PA_HIGH); // set for maximum range
  radio.setDataRate(RF24_250KBPS); 
  radio.stopListening();
}

void setup() {
  Serial.begin(115200);
  // Start searching for bluetooth controllers
  BP32.setup(&onConnectedController,
             &onDisconnectedController);
  Serial.println("Waiting for controller...");
  
  beginradio();
}     


class throttlecontrol{
  int leftY; // this variable reprsents the y axis of the left joy stick
  int throttlevalue;
  public:
    int update(){
      if (myController && myController->isConnected()){
        leftY = myController->axisY();
        leftY = leftY * -1; // My controller seemed to invert the y axis - - CHECK YOURS!
        throttlevalue = map(leftY,-512,512,1000,2000); // These are the minimum and maximum throttle values for my esc, use the test_motor code to find yours
        return throttlevalue;
      }
      else{
        return 1500;
      }
    }   
};


class steeringcontrol{
  int rightX;
  int steeringvalue;
  public:
    int update(){
      if (myController && myController->isConnected()){
        rightX = myController->axisRX();
        steeringvalue = map(rightX,-512,512,40,70); // 40 and 70 are the maximum steering angles for my servo, use the test_servo code to find yours 
        return steeringvalue;
      }
      else{
        return 50;
      }
    }
};


throttlecontrol throttle;
steeringcontrol steering;

void loop() {
  BP32.update();


  transmitter_packet trs;
  trs.transmitter_throttle =throttle.update();
  trs.transmitter_steering =steering.update();

  bool success = radio.write(&trs, sizeof(trs)); // sends the struct packet to the reciever 
  // if sent --->
  if (success) {
    // line bellow checks if the reciever is sending anything back 
    //- - NOTHING IS BEING SENT BACK YET BUT INCLUDED THIS FEATURE WILL BE VERY USEFUL IN THE FUTURE - - 
    if (radio.isAckPayloadAvailable()) {
      reciever_packet rcv;
      radio.read(&rcv, sizeof(rcv));
    }
  }
  delay(1);  
}
