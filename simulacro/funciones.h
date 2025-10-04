#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <Arduino.h>
#include <stdint.h>
#include <EEPROM.h>


#define PIN_BOTON_ARRIBA    2
#define PIN_BOTON_ABAJO     3
#define PIN_BOTON_MODO      4
#define PIN_BOTON_GUARDAR   5
#define PIN_LED_MINUTOS     8
#define PIN_LED_SEGUNDOS    9
//constantes
#define DIRECCION_MINUTOS   0
#define DIRECCION_SEGUNDOS  1
#define VELOCIDAD_SERIAL    9600
#define VALOR_MINIMO        0
#define VALOR_MAXIMO        59
#define RETRASO_BOTONES     150

// globales
extern uint8_t minutos;
extern uint8_t segundos;
extern bool modoMinutos;

// Estados de botones
extern bool estadoBotonArriba;
extern bool estadoBotonAbajo;
extern bool estadoBotonModo;
extern bool estadoBotonGuardar;

// Banderas 
extern volatile bool banderaBotonArriba;
extern volatile bool banderaBotonAbajo;

void configurar();
void subir();
void bajar();
void cambiarModo();
void actualizarLEDs();
void guardar();

// Interrupciones
void ISR_botonArriba();
void ISR_botonAbajo();

#endif  