/*
 * TP1 - Exercise 3
 * Basic DC Motor control with AFMotor library
 */

#include <AFMotor.h>

AF_DCMotor motor(4);

void setup() {
  Serial.begin(9600);
  // Vitesse initiale
  motor.setSpeed(200);
  motor.run(RELEASE);
}

void loop() {
  uint8_t i;

  // Allumer - Forward
  Serial.println("Forward - Accelerating...");
  motor.run(FORWARD);
  for (i=0; i<255; i++) {
    motor.setSpeed(i);
    delay(10);
  }

  // Decelerer
  Serial.println("Forward - Decelerating...");
  for (i=255; i!=0; i--) {
    motor.setSpeed(i);
    delay(10);
  }

  // Changer direction
  Serial.println("Backward - Accelerating...");
  motor.run(BACKWARD);
  for (i=0; i<255; i++) {
    motor.setSpeed(i);
    delay(10);
  }

  // Decelerer
  Serial.println("Backward - Decelerating...");
  for (i=255; i!=0; i--) {
    motor.setSpeed(i);
    delay(10);
  }

  // Eteindre
  Serial.println("Stopping...");
  motor.run(RELEASE);
  delay(1000);
}