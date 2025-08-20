# Práctica: Blink Secuencial - ESP32

Implementación de secuencia de LEDs usando Arduino Framework.

## 📋 Descripción

Programa que enciende una tira de LEDs de forma secuencial con un intervalo configurable entre cada LED.

## 📁 Estructura del proyecto

- `parte_a.ino` - Versión inicial (10 LEDs, 2 segundos)
- `parte_b.ino` - Versión modificada (15 LEDs, 0.5 segundos)
- `parte_c.ino` - Código principal (versión final)

## PARTE C  

### Eliminación de números mágicos

Se reemplazaron los valores literales por constantes `#define`:

- `NUM_LEDS`: Controla la cantidad de LEDs (15)
- `DELAY_TIME_MS`: Define el intervalo entre LEDs (500ms)
- `FIRST_PIN`: Especifica el pin inicial de la secuencia (2)
