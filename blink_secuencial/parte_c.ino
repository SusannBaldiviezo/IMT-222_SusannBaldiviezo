// PARTE C

//MACROS
#define NUM_LEDS         15     // Cantidad de LEDs 
#define DELAY_TIME_MS    500    // Tiempo entre LEDs 0.5 seG
#define FIRST_PIN        2      // Pin inicial 

void setup() {
  // Configurar todos los pines como salida
  for(int i = FIRST_PIN; i < FIRST_PIN + NUM_LEDS; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW); //Todos empiezan apagados
  }
}
void loop() {
  for(int i = FIRST_PIN; i < FIRST_PIN + NUM_LEDS; i++) {
    digitalWrite(i, HIGH);   // Enciende LED actual
    delay(DELAY_TIME_MS);    // Esperar
    digitalWrite(i, LOW);    // Apagar LED actual
  }
  
  // pequeña pausa antes de repetir la secuencia
  // delay(100);
}