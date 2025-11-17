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
  Wire.write(REG_PWR_MGMT_1);  // Registro PWR_MGMT_1
  Wire.write(VALOR_WAKE_UP);   // Despertar el MPU6050
  Wire.endTransmission(true);
  
  Serial.begin(BAUDRATE_SERIAL);
  Serial.println("    MPU6050 INICIALIZADO CORRECTAMENTE");
  delay(2000);
}

// Leer datos crudos del sensor
void MPU6050::leerDatos() {
  Wire.beginTransmission(direccion);
  Wire.write(REG_ACCEL_XOUT_H);  // Registro inicial de datos
  Wire.endTransmission(false);
  Wire.requestFrom(direccion, NUM_BYTES_LECTURA, true);
  
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
  float gyroX = giroscopioX / SENS_GYRO_250DPS;
  float gyroY = giroscopioY / SENS_GYRO_250DPS;
  float gyroZ = giroscopioZ / SENS_GYRO_250DPS;
  
  // Calcular angulos desde giroscopio
  anguloGyX = anguloGyX + gyroX * tiempo;
  anguloGyY = anguloGyY + gyroY * tiempo;
  yaw = yaw + gyroZ * tiempo; 
  // Filtro complementario (96% giroscopio + 4% acelerometro)
  roll = ALFA_GYRO * anguloGyX + ALFA_ACEL * anguloAcX;
  pitch = ALFA_GYRO * anguloGyY + ALFA_ACEL * anguloAcY;
  
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