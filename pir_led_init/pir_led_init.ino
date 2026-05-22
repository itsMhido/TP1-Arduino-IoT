int pinPIR = 2;
int pinLED = 9;
int etatPir = LOW;
int val = 0;

void setup() {
  pinMode(pinPIR, INPUT);
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(pinPIR);

  if (val == HIGH) {
    if (etatPir == LOW) {
      Serial.println("Mouvement detecte!");
      etatPir = HIGH;
    }
    digitalWrite(pinLED, HIGH);
  } else {
    if (etatPir == HIGH) {
      Serial.println("Mouvement termine!");
      etatPir = LOW;
    }
    digitalWrite(pinLED, LOW);
  }
}