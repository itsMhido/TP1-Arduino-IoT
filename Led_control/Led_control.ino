/*
 * TP1 - Exercise 1 (TP1-3)
 * LED Control via Serial
 */

int led = 9; 
char octet_rx = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT); // Added this so Pin 9 can actually power the LED
}

void loop() {
  if (Serial.available() > 0) {
    octet_rx = Serial.read();
    
    if (octet_rx == 'a') { /* 'a' comme allumer */
      digitalWrite(led, HIGH);
      Serial.println("LED allumee");
    }
    
    if (octet_rx == 'e') { /* 'e' comme eteindre */
      digitalWrite(led, LOW);
      Serial.println("LED eteinte");
    }
  }
}