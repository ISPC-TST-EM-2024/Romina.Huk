#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ROMIX"; // Red Wi-Fi
const char* password = "QDMMDZNXUWMY"; // contraseña

// Crea una instancia del servidor en el puerto 80
WebServer server(80);

// Pin donde está conectado el LED integrado (GPIO 2)
const int ledPin = 2;

// Declaraciones de funciones
void handleRoot();
void handleTurnOn();
void handleTurnOff();
void handleStatus();

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW); // LED apagado al inicio

    // Conecta a la red Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a Wi-Fi...");
    }
    Serial.println("Conectado a Wi-Fi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());

    // Configura las rutas
    server.on("/", handleRoot);
    server.on("/on", handleTurnOn);
    server.on("/off", handleTurnOff);
    server.on("/status", handleStatus);

    server.begin();
    Serial.println("Servidor iniciado");
}

void loop() {
    server.handleClient();
}

void handleRoot() {
    String html = "<html>";
    html += "<head>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>";
    html += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; text-align: center; padding: 20px; }";
    html += "h1 { color: #333; }";
    html += ".button { padding: 15px 30px; margin: 10px; font-size: 16px; color: white; background-color: #28a745; border: none; border-radius: 5px; cursor: pointer; transition: background-color 0.3s; }";
    html += ".button:hover { background-color: #218838; }";
    html += ".status { font-size: 20px; margin-top: 20px; }";
    html += ".image { display: none; margin-top: 20px; }"; // Oculta la imagen por defecto
    html += "</style>";
    html += "</head>";
    html += "<body>";
    html += "<h1>Control de LED Integrado</h1>";
    html += "<button class='button' onclick=\"turnOn()\">Encender LED</button>";
    html += "<button class='button' onclick=\"turnOff()\">Apagar LED</button>";
    html += "<div class='status'>Estado: <span id='ledStatus'>Desconocido</span></div>";
    html += "<img id='ledImage' class='image' src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAUA\nAAAAABCAQAAAABgP2jAAAAFElEQVR42mL8//8/wcAAwAB/6MY9bsAAAAAElFTkSuQmCC' width='100'>"; // Reemplaza con la imagen que desees
    html += "<script>";
    html += "function updateStatus(isOn) { document.getElementById('ledStatus').innerText = isOn ? 'Encendido' : 'Apagado'; }";
    html += "function turnOn() { fetch('/on').then(() => { updateStatus(true); document.getElementById('ledImage').style.display = 'block'; }); }";
    html += "function turnOff() { fetch('/off').then(() => { updateStatus(false); document.getElementById('ledImage').style.display = 'none'; }); }";
    html += "setInterval(function() { fetch('/status').then(response => response.text()).then(status => updateStatus(status === '1')); }, 1000);";
    html += "</script>";
    html += "</body>";
    html += "</html>";

    server.send(200, "text/html", html);
}

void handleTurnOn() {
    digitalWrite(ledPin, HIGH);
    // No enviar respuesta, se maneja en AJAX
}

void handleTurnOff() {
    digitalWrite(ledPin, LOW);
    // No enviar respuesta, se maneja en AJAX
}

void handleStatus() {
    int state = digitalRead(ledPin);
    server.send(200, "text/plain", String(state));
}
