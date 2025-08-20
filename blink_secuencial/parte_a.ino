//PARTE A

void setup() {
  for(int i = 2; i <= 11; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  for(int i = 2; i <= 11; i++) {
    digitalWrite(i, HIGH);
    delay(2000);
    digitalWrite(i, LOW);
  }
}