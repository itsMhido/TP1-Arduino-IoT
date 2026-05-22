int pinPIR = 2;
int pinLED = 9;
int etatPir = LOW;
int val = 0;

unsigned long lastTriggerTime = 0;
const unsigned long DEBOUNCE_MS = 200;      // ignore signals shorter than 200ms
const unsigned long VALIDATION_MS = 500;    // motion must persist 500ms to be valid

unsigned long motionStartTime = 0;
bool motionPending = false;

void setup() {
  pinMode(pinPIR, INPUT);
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(pinPIR);
  unsigned long now = millis();

  if (val == HIGH) {
    if (!motionPending) {
      motionPending = true;
      motionStartTime = now;
    }
    // only validate if motion persists long enough
    if (motionPending && (now - motionStartTime >= VALIDATION_MS)) {
      if (etatPir == LOW && (now - lastTriggerTime >= DEBOUNCE_MS)) {
        Serial.print("["); Serial.print(now); Serial.println(" ms] Mouvement valide!");
        etatPir = HIGH;
        lastTriggerTime = now;
      }
      digitalWrite(pinLED, HIGH);
    }
  } else {
    motionPending = false;
    if (etatPir == HIGH) {
      Serial.print("["); Serial.print(now); Serial.println(" ms] Mouvement termine!");
      etatPir = LOW;
    }
    digitalWrite(pinLED, LOW);
  }
}