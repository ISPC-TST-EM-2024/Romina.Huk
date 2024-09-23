#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "sc-3028";
const char* password = "paMpa2023@";

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.println("Conectando a Wi-Fi ...");
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a la red Wi-Fi");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
}

void loop(){
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Conexion perdida, intentando reconectar...");
    WiFi.reconnect();
  } else{
    Serial.println("Conexion estable.");
  }
  delay(5000);
}
