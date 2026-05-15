/*
 * TP1 - Exercise 1 (TP1-4)
 * Extended LED Control via Serial
 */

int led = 9;
char octet_rx = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    octet_rx = Serial.read();

    // ROBUSTNESS: Ignore invisible newline or carriage return characters
    if (octet_rx == '\n' || octet_rx == '\r') {
      return; 
    }

    if (octet_rx == 'a') { /* allumer */
      digitalWrite(led, HIGH);
      Serial.println("LED allumee");
    } 
    else if (octet_rx == 'e') { /* eteindre */
      digitalWrite(led, LOW);
      Serial.println("LED eteinte");
    } 
    else if (octet_rx == 'i') { /* inverser / toggle */
      // Read the current state of the pin and set it to the opposite (!)
      bool etatActuel = digitalRead(led);
      digitalWrite(led, !etatActuel);
      Serial.println("LED inversee");
    } 
    else if (octet_rx == 'c') { /* clignoter / blink */
      Serial.println("LED clignote 3 fois");
      // Loop to blink 3 times
      for (int i = 0; i < 3; i++) {
        digitalWrite(led, HIGH);
        delay(300);
        digitalWrite(led, LOW);
        delay(300);
      }
    } 
    else {
      // Handle random keys the user might press
      Serial.println("Commande invalide. Utilisez a, e, i, ou c.");
    }
  }
}