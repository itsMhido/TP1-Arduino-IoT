/*
 * TP1 - Exercise 3
 * Fan state machine: OFF/ECO/NORMAL/TURBO
 * via serial port
 */

#include <AFMotor.h>

AF_DCMotor motor(4);
String inputString = "";

// State definitions
#define OFF    0
#define ECO    1
#define NORMAL 2
#define TURBO  3

int currentState = OFF;

void applyState(int state) {
  switch(state) {
    case OFF:
      motor.setSpeed(0);
      motor.run(RELEASE);
      Serial.println("Mode: OFF");
      break;
    case ECO:
      motor.setSpeed(120);
      motor.run(FORWARD);
      Serial.println("Mode: ECO (speed=80)");
      break;
    case NORMAL:
      motor.setSpeed(160);
      motor.run(FORWARD);
      Serial.println("Mode: NORMAL (speed=160)");
      break;
    case TURBO:
      motor.setSpeed(255);
      motor.run(FORWARD);
      Serial.println("Mode: TURBO (speed=255)");
      break;
  }
}

void setup() {
  Serial.begin(9600);
  motor.run(RELEASE);
  Serial.println("Commands: OFF / ECO / NORMAL / TURBO");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      inputString.trim();
      if (inputString == "OFF")         { currentState = OFF;    applyState(currentState); }
      else if (inputString == "ECO")    { currentState = ECO;    applyState(currentState); }
      else if (inputString == "NORMAL") { currentState = NORMAL; applyState(currentState); }
      else if (inputString == "TURBO")  { currentState = TURBO;  applyState(currentState); }
      else { Serial.println("Unknown command! Use: OFF/ECO/NORMAL/TURBO"); }
      inputString = "";
    } else {
      inputString += c;
    }
  }
}