#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_Bluetooth");
    Serial.println("El dispositivo Bluetooth está listo para emparejarse.");
}

void loop() {
    if (SerialBT.available()) {
        String mensaje = SerialBT.readString();
        Serial.println("Recibido: " + mensaje);
        SerialBT.println("Eco: " + mensaje);
    }
    if (Serial.available()) {
        String mensaje = Serial.readString();
        SerialBT.println(mensaje);
        Serial.println("Enviado: " + mensaje);
    }

}