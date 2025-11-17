/*
  MPU6050.h - Libreria para manejo del sensor MPU6050
  Comunicacion I2C con Arduino UNO
*/

#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>
#include <Wire.h>

// Direccion I2C del MPU6050 cuando AD0 esta en GND
static const uint8_t MPU6050_ADDR = 0x68;

// Registros del MPU6050
static const uint8_t REG_PWR_MGMT_1    = 0x6B;
static const uint8_t REG_ACCEL_XOUT_H  = 0x3B;

// Constantes de configuracion
static const uint8_t NUM_BYTES_LECTURA = 14;
static const uint8_t VALOR_WAKE_UP     = 0x00;

// Sensibilidad del giroscopio en modo ±250°/s
static const float SENS_GYRO_250DPS = 131.0;

// Coeficientes del filtro complementario
static const float ALFA_GYRO = 0.96;
static const float ALFA_ACEL = 0.04;

// Configuracion de comunicacion serial
static const unsigned long BAUDRATE_SERIAL = 115200;

class MPU6050 {
  private:
    const uint8_t direccion = MPU6050_ADDR;
    
    // Variables crudas del sensor
    int16_t acelerometroX, acelerometroY, acelerometroZ;
    int16_t giroscopioX, giroscopioY, giroscopioZ;
    int16_t temperatura;
    
    // Variables de angulos
    float anguloAcX, anguloAcY;
    float anguloGyX, anguloGyY, anguloGyZ;
    
    // Variables de tiempo
    unsigned long tiempoActual, tiempoAnterior;
    float tiempo;
    
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