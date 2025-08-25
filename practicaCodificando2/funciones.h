#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <Arduino.h>

#define DELAY 1000
#define LED1 2
#define LED2 4
#define LED3 5
#define LED4 16
#define BTN 18
#define BAUDRATE 9600

extern bool flag; 

void configuracion();
void espera();
void secuencia();

#endif
