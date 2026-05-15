/*
 * TP1 - Exercise 1 (TP1-5)
 * Dual LED Control (Non-Blocking / millis)
 */

int led1 = 9;
int led2 = 10;

// Variables to store the blinking periods (in milliseconds)
long period1 = 1000; 
long period2 = 1000;

// Variables to track the last time each LED toggled
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;

// Variables to track the current state of each LED
bool state1 = LOW;
bool state2 = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.println("Systeme pret. Tapez '1:500' pour LED1 a 500ms, ou '2:1000' pour LED2.");
}

void loop() {
  // --- 1. NON-BLOCKING LED TOGGLE LOGIC ---
  unsigned long currentMillis = millis();

  // Check if it's time to toggle LED 1
  if (currentMillis - previousMillis1 >= period1) {
    previousMillis1 = currentMillis; 
    state1 = !state1; 
    digitalWrite(led1, state1);
  }

  // Check if it's time to toggle LED 2
  if (currentMillis - previousMillis2 >= period2) {
    previousMillis2 = currentMillis; 
    state2 = !state2; 
    digitalWrite(led2, state2);
  }

  // --- 2. ROBUST SERIAL READING ---
  if (Serial.available() > 0) {
    char targetLed = Serial.read(); // Read the first character ('1' or '2')
    
    if (targetLed == '1') {
      long newPeriod = Serial.parseInt(); // Extracts the number that comes after
      if (newPeriod > 0) {
        period1 = newPeriod;
        Serial.print("Nouvelle periode pour LED 1: ");
        Serial.println(period1);
      }
    } 
    else if (targetLed == '2') {
      long newPeriod = Serial.parseInt();
      if (newPeriod > 0) {
        period2 = newPeriod;
        Serial.print("Nouvelle periode pour LED 2: ");
        Serial.println(period2);
      }
    }
  }
}