/*
 * TP1 - Exercise 3
 * Progressive speed ramp - smooth acceleration/deceleration
 * Commands: OFF / ECO / NORMAL / TURBO
 */

#include <AFMotor.h>

AF_DCMotor motor(4);
String inputString = "";

#define OFF    0
#define ECO    1
#define NORMAL 2
#define TURBO  3

int currentSpeed = 0;
int targetSpeed = 0;
int currentState = OFF;

// Ramp step: increase/decrease speed by 1 every RAMP_DELAY ms
#define RAMP_DELAY 10

void setup() {
  Serial.begin(9600);
  motor.run(RELEASE);
  Serial.println("Commands: OFF / ECO / NORMAL / TURBO");
}

void updateRamp() {
  if (currentSpeed < targetSpeed) {
    currentSpeed++;
    motor.run(FORWARD);
    motor.setSpeed(currentSpeed);
    delay(RAMP_DELAY);
  } else if (currentSpeed > targetSpeed) {
    currentSpeed--;
    if (currentSpeed == 0) {
      motor.run(RELEASE);
    } else {
      motor.setSpeed(currentSpeed);
    }
    delay(RAMP_DELAY);
  }
}

void handleCommand(String cmd) {
  cmd.trim();
  if (cmd == "OFF") {
    targetSpeed = 0;
    currentState = OFF;
    Serial.println("Mode: OFF (ramping down)");
  } else if (cmd == "ECO") {
    targetSpeed = 80;
    currentState = ECO;
    Serial.println("Mode: ECO (ramping to 80)");
  } else if (cmd == "NORMAL") {
    targetSpeed = 160;
    currentState = NORMAL;
    Serial.println("Mode: NORMAL (ramping to 160)");
  } else if (cmd == "TURBO") {
    targetSpeed = 255;
    currentState = TURBO;
    Serial.println("Mode: TURBO (ramping to 255)");
  } else {
    Serial.println("Unknown command! Use: OFF/ECO/NORMAL/TURBO");
  }
}

void loop() {
  // Handle serial input
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      handleCommand(inputString);
      inputString = "";
    } else {
      inputString += c;
    }
  }
  // Always update ramp
  updateRamp();
}