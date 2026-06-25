#define RAW_BUFFER_LENGTH 750

#include <IRremote.hpp>

#define RECEIVE_PIN 2

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Listo. Apunta el control y apreta un boton.");
}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRResultRawFormatted(&Serial, true); // true = en microsegundos
    IrReceiver.resume();
  }
}