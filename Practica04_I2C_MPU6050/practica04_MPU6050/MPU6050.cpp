/*
  MPU6050.cpp - Implementacion de la libreria MPU6050
*/

#include "MPU6050.h"

// Constructor
MPU6050::MPU6050() {
  anguloGyX = 0;
  anguloGyY = 0;
  anguloGyZ = 0;
  roll = 0;
  pitch = 0;
  yaw = 0;
  tiempoAnterior = 0;
}

// Inicializar sensor MPU6050
void MPU6050::inicializar() {
  Wire.begin();
  Wire.beginTransmission(direccion);
  Wire.write(0x6B);  // Registro PWR_MGMT_1
  Wire.write(0);     // Despertar el MPU6050
  Wire.endTransmission(true);
  
  Serial.begin(115200);
  Serial.println("========================================");
  Serial.println("    MPU6050 INICIALIZADO CORRECTAMENTE");
  Serial.println("========================================");
  delay(2000);
}

// Leer datos crudos del sensor
void MPU6050::leerDatos() {
  Wire.beginTransmission(direccion);
  Wire.write(0x3B);  // Registro inicial de datos
  Wire.endTransmission(false);
  Wire.requestFrom(direccion, 14, true);
  
  // Leer acelerometro
  acelerometroX = Wire.read() << 8 | Wire.read();
  acelerometroY = Wire.read() << 8 | Wire.read();
  acelerometroZ = Wire.read() << 8 | Wire.read();
  
  // Leer temperatura (no se usa)
  temperatura = Wire.read() << 8 | Wire.read();
  
  // Leer giroscopio
  giroscopioX = Wire.read() << 8 | Wire.read();
  giroscopioY = Wire.read() << 8 | Wire.read();
  giroscopioZ = Wire.read() << 8 | Wire.read();
}

// Calcular angulos Roll, Pitch, Yaw
void MPU6050::calcularAngulos() {
  // Calcular tiempo transcurrido
  tiempoAnterior = tiempoActual;
  tiempoActual = millis();
  tiempo = (tiempoActual - tiempoAnterior) / 1000.0;
  
  // Calcular angulos desde acelerometro
  anguloAcX = (atan(acelerometroY / sqrt(pow(acelerometroX, 2) + pow(acelerometroZ, 2))) * 180 / PI);
  anguloAcY = (atan(-1 * acelerometroX / sqrt(pow(acelerometroY, 2) + pow(acelerometroZ, 2))) * 180 / PI);
  
  // Convertir giroscopio a grados/segundo
  float gyroX = giroscopioX / 131.0;
  float gyroY = giroscopioY / 131.0;
  float gyroZ = giroscopioZ / 131.0;
  
  // Calcular angulos desde giroscopio
  anguloGyX = anguloGyX + gyroX * tiempo;
  anguloGyY = anguloGyY + gyroY * tiempo;
  yaw = yaw + gyroZ * tiempo;
  
  // Filtro complementario (96% giroscopio + 4% acelerometro)
  roll = 0.96 * anguloGyX + 0.04 * anguloAcX;
  pitch = 0.96 * anguloGyY + 0.04 * anguloAcY;
  
  // Actualizar valores del giroscopio
  anguloGyX = roll;
  anguloGyY = pitch;
}

// Mostrar datos en monitor serial
void MPU6050::mostrarDatos() {
  Serial.print("Roll: ");
  Serial.print(roll, 2);
  Serial.print("°   Pitch: ");
  Serial.print(pitch, 2);
  Serial.print("°   Yaw: ");
  Serial.print(yaw, 2);
  Serial.println("°");
}