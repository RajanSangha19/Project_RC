#include <Servo.h>

int value = 0;
String input = "";

// Enter servo values to find the working range and values for your servo
// Ensure that the steering is not attached to prevent breaking anything
// Make sure that you stervo has a serperate power supply but shares a common ground with the ESP32


void setup() {
  Serial.begin(115200);
  servo.attach(#####); // Attach this to your servo pin
}

void loop() {
  if (Serial.available()){
    input = Serial.readStringUntil('\n');
    value = input.toInt();
    Serial.println(value);
  }
  Serial.println("");
  servo.write(value);
  millis(5);
}

// Make sure to note down the values, including a value that sets your servo to make the wheel straight