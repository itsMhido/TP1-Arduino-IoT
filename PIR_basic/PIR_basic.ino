/*
 * TP1 - Exercise 2
 * Basic PIR motion detection
 */

int pinEntree = 2;
int etatPir = LOW;
int val = 0;

void setup() {
  pinMode(pinEntree, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(pinEntree);
  
  if (val == HIGH) {
    if (etatPir == LOW) {
      Serial.println("Mouvement detecte!");
      etatPir = HIGH;
    }
  } else {
    if (etatPir == HIGH) {
      Serial.println("Mouvement termine!");
      etatPir = LOW;
    }
  }
}