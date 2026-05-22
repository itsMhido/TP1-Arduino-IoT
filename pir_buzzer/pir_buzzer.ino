int pinPIR = 2;
int pinLED = 9;
int pinBUZZER = 8;

int etatPir = LOW;
int val = 0;
bool armed = true;

unsigned long buzzerStartTime = 0;
bool buzzerOn = false;
const unsigned long BUZZER_DURATION = 3000; // buzzer stops after 3 seconds

void setup() {
  pinMode(pinPIR, INPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(pinBUZZER, OUTPUT);
  Serial.begin(9600);
  Serial.println("Systeme pret. A=armer, D=desarmer");
}

void loop() {

  // check serial commands
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 'A') {
      armed = true;
      Serial.println("Systeme ARME");
    } else if (cmd == 'D') {
      armed = false;
      digitalWrite(pinLED, LOW);
      digitalWrite(pinBUZZER, LOW);
      buzzerOn = false;
      Serial.println("Systeme DESARME");
    }
  }

  // auto stop buzzer after N seconds
  if (buzzerOn && (millis() - buzzerStartTime >= BUZZER_DURATION)) {
    digitalWrite(pinBUZZER, LOW);
    buzzerOn = false;
    Serial.println("Buzzer arrete");
  }

  // read PIR
  val = digitalRead(pinPIR);

  if (val == HIGH) {
    if (etatPir == LOW) {
      etatPir = HIGH;
      if (armed) {
        Serial.println("Mouvement detecte!");
        digitalWrite(pinLED, HIGH);
        digitalWrite(pinBUZZER, HIGH);
        buzzerOn = true;
        buzzerStartTime = millis();
      }
    }
  } else {
    if (etatPir == HIGH) {
      etatPir = LOW;
      if (armed) {
        Serial.println("Mouvement termine!");
        digitalWrite(pinLED, LOW);
      }
    }
  }
}