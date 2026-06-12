/*
 * TP1 - Exercise 3 - Question 6
 * Unified serial control: Servo + Stepper motor
 * 
 * Servo commands:
 *   S0   → position 0°
 *   S90  → position 90°
 *   S180 → position 180°
 * 
 * Stepper commands:
 *   MFORWARD  → rotate forward
 *   MBACK     → rotate backward
 *   MFAST     → high speed
 *   MSLOW     → low speed
 */

#include <Servo.h>
#include <Stepper.h>

// Servo setup
Servo myServo;
#define SERVO_PIN 6

// Stepper setup
#define STEPS_PER_REV 64
Stepper myStepper(STEPS_PER_REV, 8, 10, 9, 11);

String inputString = "";
int stepperSpeed = 10;  // default speed

void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);
  myServo.write(0);  // start at 0°
  myStepper.setSpeed(10);
  Serial.println("=== Servo + Stepper Control ===");
  Serial.println("Servo:   S0 / S90 / S180");
  Serial.println("Stepper: MFORWARD / MBACK / MFAST / MSLOW");
}

void handleCommand(String cmd) {
  cmd.trim();

  // Servo commands
  if (cmd == "S0") {
    myServo.write(0);
    Serial.println("Servo → 0°");
  } else if (cmd == "S90") {
    myServo.write(90);
    Serial.println("Servo → 90°");
  } else if (cmd == "S180") {
    myServo.write(180);
    Serial.println("Servo → 180°");
  }

  // Stepper commands
  else if (cmd == "MFORWARD") {
    Serial.println("Stepper → Forward");
    myStepper.step(STEPS_PER_REV);
  } else if (cmd == "MBACK") {
    Serial.println("Stepper → Backward");
    myStepper.step(-STEPS_PER_REV);
  } else if (cmd == "MFAST") {
    stepperSpeed = 20;
    myStepper.setSpeed(stepperSpeed);
    Serial.println("Stepper speed → FAST");
  } else if (cmd == "MSLOW") {
    stepperSpeed = 5;
    myStepper.setSpeed(stepperSpeed);
    Serial.println("Stepper speed → SLOW");
  }

  else {
    Serial.println("Unknown command!");
    Serial.println("Servo: S0/S90/S180 | Stepper: MFORWARD/MBACK/MFAST/MSLOW");
  }
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      handleCommand(inputString);
      inputString = "";
    } else {
      inputString += c;
    }
  }
}