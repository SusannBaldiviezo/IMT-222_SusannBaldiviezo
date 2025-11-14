/*
  Practica 04 - Comunicacion I2C con MPU6050
  Universidad Catolica Boliviana "San Pablo"
  IMT-222 Sistemas Embebidos I
  
  Hardware:
  - Arduino UNO
  - Sensor MPU6050 (I2C)
  
  Conexiones:
  MPU6050 VCC -> Arduino 5V
  MPU6050 GND -> Arduino GND
  MPU6050 SCL -> Arduino A5
  MPU6050 SDA -> Arduino A4
*/

#include "MPU6050.h"

// Crear objeto del sensor
MPU6050 sensor;

void setup() {
  // Inicializar sensor MPU6050
  sensor.inicializar();
}

void loop() {
  // Leer datos del sensor
  sensor.leerDatos();
  
  // Calcular angulos Roll, Pitch, Yaw
  sensor.calcularAngulos();
  
  // Mostrar resultados
  sensor.mostrarDatos();
  
  // Esperar 100ms antes de siguiente lectura
  delay(100);
}