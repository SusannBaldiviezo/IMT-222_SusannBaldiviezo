#include "funciones.h"

void setup() {
  configurar();
}

void loop() {
  subir();
  bajar();
  cambiarModo();
  actualizarLEDs();
  guardar();
}