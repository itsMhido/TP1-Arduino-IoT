/*
 * TP1 - Exercise 3
 * Fan control with security - aberrant input detection
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
#define RAMP_DELAY 10

// Security: track invalid attempts
int invalidCount = 0;
#define MAX_INVALID 3

void setup() {
  Serial.begin(9600);
  motor.run(RELEASE);
  Serial.println("=== Fan Control System ===");
  Serial.println("Commands: OFF / ECO / NORMAL / TURBO");
  Serial.println("Or enter speed directly: 0-255");
}

bool isValidNumber(String s) {
  s.trim();
  if (s.length() == 0) return false;
  for (int i = 0; i < s.length(); i++) {
    if (!isDigit(s[i])) return false;
  }
  int val = s.toInt();
  return (val >= 0 && val <= 255);
}

void updateRamp() {
  if (currentSpeed < targetSpeed) {
    currentSpeed++;
    motor.run(FORWARD);
    motor.setSpeed(currentSpeed);
    delay(RAMP_DELAY);
  } else if (currentSpeed > targetSpeed) {
    currentSpeed--;
    if (currentSpeed == 0) motor.run(RELEASE);
    else motor.setSpeed(currentSpeed);
    delay(RAMP_DELAY);
  }
}

void handleCommand(String cmd) {
  cmd.trim();
  if (cmd == "OFF")         { targetSpeed = 0;   currentState = OFF;    Serial.println("Mode: OFF");    invalidCount = 0; }
  else if (cmd == "ECO")    { targetSpeed = 80;  currentState = ECO;    Serial.println("Mode: ECO");    invalidCount = 0; }
  else if (cmd == "NORMAL") { targetSpeed = 160; currentState = NORMAL; Serial.println("Mode: NORMAL"); invalidCount = 0; }
  else if (cmd == "TURBO")  { targetSpeed = 255; currentState = TURBO;  Serial.println("Mode: TURBO");  invalidCount = 0; }
  else if (isValidNumber(cmd)) {
    targetSpeed = cmd.toInt();
    Serial.print("Speed set to: ");
    Serial.println(targetSpeed);
    invalidCount = 0;
  } else {
    invalidCount++;
    Serial.print("WARNING: Invalid input '");
    Serial.print(cmd);
    Serial.print("' (");
    Serial.print(invalidCount);
    Serial.print("/");
    Serial.print(MAX_INVALID);
    Serial.println(")");
    if (invalidCount >= MAX_INVALID) {
      targetSpeed = 0;
      currentState = OFF;
      Serial.println("SECURITY: Too many invalid inputs! Motor stopped.");
      invalidCount = 0;
    }
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
  updateRamp();
}