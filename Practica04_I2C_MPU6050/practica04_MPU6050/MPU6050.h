/*
  MPU6050.h - Libreria para manejo del sensor MPU6050
  Comunicacion I2C con Arduino UNO
*/

#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>
#include <Wire.h>

class MPU6050 {
  private:
    const int direccion = 0x68;
    
    // Variables crudas del sensor
    int16_t acelerometroX, acelerometroY, acelerometroZ;
    int16_t giroscopioX, giroscopioY, giroscopioZ;
    int16_t temperatura;
    
    // Variables de angulos
    float anguloAcX, anguloAcY;
    float anguloGyX, anguloGyY, anguloGyZ;
    
    // Variables de tiempo
    float tiempo, tiempoActual, tiempoAnterior;
    
  public:
    // Variables publicas de salida
    float roll, pitch, yaw;
    
    // Metodos publicos
    MPU6050();
    void inicializar();
    void leerDatos();
    void calcularAngulos();
    void mostrarDatos();
};

#endif