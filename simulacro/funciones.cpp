#include "funciones.h"

//globales
uint8_t minutos = 0;
uint8_t segundos = 0;
bool modoMinutos = true;

// estados
bool estadoBotonArriba = HIGH;
bool estadoBotonAbajo = HIGH;
bool estadoBotonModo = HIGH;
bool estadoBotonGuardar = HIGH;

// Banderas de interrupciones (VOLATILE para ISRs)
volatile bool banderaBotonArriba = false;
volatile bool banderaBotonAbajo = false;

// config
void configurar() {
  // pines de botones
  pinMode(PIN_BOTON_ARRIBA, INPUT_PULLUP);
  pinMode(PIN_BOTON_ABAJO, INPUT_PULLUP);
  pinMode(PIN_BOTON_MODO, INPUT_PULLUP);
  pinMode(PIN_BOTON_GUARDAR, INPUT_PULLUP);
  pinMode(PIN_LED_MINUTOS, OUTPUT);
  pinMode(PIN_LED_SEGUNDOS, OUTPUT);
  
  // comunicación serial
  Serial.begin(VELOCIDAD_SERIAL);

  // CONFIGURAR INTERRUPCIONES 
  attachInterrupt(digitalPinToInterrupt(PIN_BOTON_ARRIBA), ISR_botonArriba, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_BOTON_ABAJO), ISR_botonAbajo, FALLING);

  // Cargar valores desde EEPROM
  minutos = EEPROM.read(DIRECCION_MINUTOS);
  segundos = EEPROM.read(DIRECCION_SEGUNDOS);
  
  // Validar que los valores estén en rango
  if (minutos < VALOR_MINIMO) {
    minutos = 0;
  } 
  else if (minutos > VALOR_MAXIMO) {
    minutos = 0;
  }
  if (segundos < VALOR_MINIMO) {
    segundos = 0;
  }
  else if (segundos > VALOR_MAXIMO) {
    segundos = 0;
  }
  
  Serial.print("Minutos: ");
  Serial.println(minutos);
  Serial.print("Segundos: ");
  Serial.println(segundos);
  Serial.println("Modo: MINUTOS");
}

// interrupciones de banderas
void ISR_botonArriba() {
  banderaBotonArriba = true;
}

void ISR_botonAbajo() {
  banderaBotonAbajo = true;
}

void subir() {
  // Verificar si la interrupción activó la bandera
  if (banderaBotonArriba) {
    banderaBotonArriba = false;  // Resetear bandera
    
    if (modoMinutos) {
      // Modo minutos
      if (minutos < VALOR_MAXIMO) {
        minutos++;
      } else {
        minutos = VALOR_MINIMO;  // Rollover
      }
      Serial.print("Minutos: ");
      Serial.println(minutos);
    } else {
      // Modo segundos
      if (segundos < VALOR_MAXIMO) {
        segundos++;
      } else {
        segundos = VALOR_MINIMO;  // Rollover
      }
      Serial.print("Segundos: ");
      Serial.println(segundos);
    }
    delay(RETRASO_BOTONES);  // Anti-rebote
  }
}


void bajar() {
  // Verificar si la interrupción activó la bandera
  if (banderaBotonAbajo) {
    banderaBotonAbajo = false;  // Resetear bandera
    
    if (modoMinutos) {
      // Modo minutos
      if (minutos > VALOR_MINIMO) {
        minutos--;
      } else {
        minutos = VALOR_MAXIMO;  // Rollunder
      }
      Serial.print("Minutos: ");
      Serial.println(minutos);
    } else {
      // Modo segundos
      if (segundos > VALOR_MINIMO) {
        segundos--;
      } else {
        segundos = VALOR_MAXIMO;  // Rollunder
      }
      Serial.print("Segundos: ");
      Serial.println(segundos);
    }
    delay(RETRASO_BOTONES);  // Anti-rebote
  }
}

//cambiar MODO (por polling¡)
void cambiarModo() {
  estadoBotonModo = digitalRead(PIN_BOTON_MODO);
  
  if (estadoBotonModo == LOW) {
    modoMinutos = !modoMinutos;  // Cambia true--false
    
    if (modoMinutos) {
      Serial.println("Modo: MINUTOS");
    } else {
      Serial.println("Modo: SEGUNDOS");
    }
    delay(RETRASO_BOTONES);
  }
}

void actualizarLEDs() {
  if (modoMinutos) {
    // Modo minutos - LED minutos encendido
    digitalWrite(PIN_LED_MINUTOS, HIGH);
    digitalWrite(PIN_LED_SEGUNDOS, LOW);
  } else {
    // Modo segundos - LED segundos encendido
    digitalWrite(PIN_LED_SEGUNDOS, HIGH);
    digitalWrite(PIN_LED_MINUTOS, LOW);
  }
}


void guardar() {
  estadoBotonGuardar = digitalRead(PIN_BOTON_GUARDAR);
  
  if (estadoBotonGuardar == LOW) {
    EEPROM.update(DIRECCION_SEGUNDOS, segundos);
    EEPROM.update(DIRECCION_MINUTOS, minutos);
    
    Serial.println("Datos guardados en EEPROM");
    Serial.print("Minutos: ");
    Serial.println(minutos);
    Serial.print("Segundos: ");
    Serial.println(segundos);
    
    delay(RETRASO_BOTONES);
  }
}