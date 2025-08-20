//PARTE B

void setup() {
  for(int i = 2; i <= 16; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  for(int i = 2; i <= 16; i++) {
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i, LOW);
  }
}