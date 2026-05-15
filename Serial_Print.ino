/*
 * TP1 - Exercise 1
 * Serial Print: sending messages from Arduino to PC
 */

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Salam alaykoum");
  Serial.println("Azul Fellawn");
  Serial.println("Bonjour à tous");
  delay(1000);
}