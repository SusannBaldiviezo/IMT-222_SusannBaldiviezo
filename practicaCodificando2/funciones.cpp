#include "funciones.h"

bool flag = false;

void configuracion() {
    Serial.begin(BAUDRATE);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(BTN, INPUT_PULLUP); // Botón con resistencia interna

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
} 

void espera() {
    if (digitalRead(BTN) == LOW) { 
        flag = true;
    } else {
        flag = false;
    }
}

void secuencia() {
    digitalWrite(LED1, HIGH);
    delay(DELAY);
    digitalWrite(LED1, LOW);

    digitalWrite(LED2, HIGH);
    delay(DELAY);
    digitalWrite(LED2, LOW);

    digitalWrite(LED3, HIGH);
    delay(DELAY);
    digitalWrite(LED3, LOW);

    digitalWrite(LED4, HIGH);
    delay(DELAY);
    digitalWrite(LED4, LOW);
}
