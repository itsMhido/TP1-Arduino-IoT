/*
 * TP1 - Exercise 3
 * Fan speed control via serial (0-255)
 */

#include <AFMotor.h>

AF_DCMotor motor(4);
String inputString = "";

void setup() {
  Serial.begin(9600);
  motor.run(RELEASE);
  Serial.println("Enter speed (0-255):");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      int speed = inputString.toInt();
      if (speed >= 0 && speed <= 255) {
        motor.setSpeed(speed);
        if (speed == 0) {
          motor.run(RELEASE);
          Serial.println("Motor stopped");
        } else {
          motor.run(FORWARD);
          Serial.print("Speed set to: ");
          Serial.println(speed);
        }
      } else {
        Serial.println("Invalid! Enter 0-255");
      }
      inputString = "";
    } else {
      inputString += c;
    }
  }
}