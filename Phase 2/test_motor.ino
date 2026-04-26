#include <ESP32Servo.h>

// This code is so you can figure out how to use your esc to control the motor
// The ESP32 will have to talk to the ESC by sending a PWM signal
// Unfortunately most ESC manufacturers do not publish what signals to send 
// to get the motor moving
// Always refer to your ESC manual first but you can use this code to do
// a series of test to see what PWM signals can be used to move the motor

// Connect the data wire and the ground from the ESC to your ESP32

Servo esc;

String input = "";
int value = 0;

void setup() {
  esc.attach(13); // Attach this to your ESC pin, we will treat it like a servo
  //#########################################################
  // We need to initialise the motor. This is usually done by sending a PWM signal
  // for a certain amount of time
  // For my Rocket RC ESC I needed to send a 1500 signal for 3 seconds
  // You might need to use trial and error to figure this out 
  esc.writeMicroseconds(1500); 
  delay(3000);
  //#########################################################
  Serial.begin(115200);
}

void loop() {
  // Enter PWM values (such as: 1660) to see how your motor responds
  if (Serial.available()){
    input = Serial.readStringUntil('\n');
    value = input.toInt();
    Serial.println(value);
  }
  Serial.println("");
  esc.writeMicroseconds(value);
  delay(500);
}

// Be careful when doing this
// Inputing certain PWM values could mean your motor will go full speed instantly
// and then the only way to stop it is to remove your motor's battery or 
// input a lower signal 
// Always test your ESC with gradual changes in PWM and make sure 
// that your RC car won't drive away


