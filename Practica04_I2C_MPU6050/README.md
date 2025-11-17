# Comunicación I²C con MPU6050 y Arduino UNO

Proyecto de **Sistemas Embebidos I (IMT-222)** donde se implementa la comunicación digital **I²C** entre un **Arduino UNO (maestro)** y el sensor **MPU6050 (esclavo)** para obtener en tiempo real los ángulos de orientación **Roll, Pitch y Yaw** usando un **filtro complementario** y código modular (.ino + .h + .cpp).

---

## 🎯 Objetivo general

- Configurar el bus **I²C** entre Arduino UNO y el MPU6050.  
- Leer el paquete de **14 bytes** (acelerómetro, temperatura y giroscopio).  
- Procesar los datos crudos para calcular **Roll, Pitch y Yaw**.  
- Mostrar la orientación en el **Monitor Serial**.  
- Organizar el proyecto con una **arquitectura de código modular**.

---

## 🛠️ Hardware

- Arduino UNO  
- Módulo MPU6050 (GY-521 o similar)  
- Cables Dupont

### Conexiones

| Arduino | MPU6050 |
|--------|---------|
| 5V     | VCC     |
| GND    | GND     |
| A4     | SDA     |
| A5     | SCL     |

> En el módulo GY-521 las resistencias **pull-up** para SDA y SCL suelen venir integradas.

---

## 💻 Software

- IDE de Arduino  
- Librería `Wire.h` (incluida por defecto)

---

## 📁 Estructura del proyecto

```text
/Proyecto_MPU6050_I2C
├── Proyecto_MPU6050_I2C.ino   // Programa principal
├── MPU6050.h                  // Definición de la clase MPU6050
└── MPU6050.cpp                // Implementación de la clase MPU6050
