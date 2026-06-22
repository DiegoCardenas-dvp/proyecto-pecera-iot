#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ==========================================
// 1. MODIFICA ESTOS DATOS CON TU RED
// ==========================================
const char* ssid = "REDJSPY";             
const char* password = "d6686651cm";    
const char* mqtt_server = "192.168.1.175"; // Verifica si esta IP sigue siendo la de hoy

// --- Pines ---
const int PIN_RELE = 26;   
const int PIN_SERVO = 27;  
const int PIN_TEMP = 4;    // Pin D4 para el sensor DS18B20

// --- Objetos ---
WiFiClient espClient;
PubSubClient client(espClient);
Servo miServo;

// Objetos para el sensor de temperatura
OneWire oneWire(PIN_TEMP);
DallasTemperature sensorTemp(&oneWire);

// ==========================================
// 2. TÓPICOS
// ==========================================
const char* topico_bomba = "escom/iot/actuador/bomba";
const char* topico_comida = "escom/iot/actuador/comida";
const char* topico_temperatura = "escom/iot/sensor/temperatura"; // Nuevo tópico

// Variable para el temporizador de la temperatura
unsigned long tiempoAnterior = 0;

void setup_wifi() {
  delay(10);
  Serial.println("\nConectando a " + String(ssid));
  
  // -- AÑADE ESTAS DOS LÍNEAS --
  WiFi.mode(WIFI_STA); // Obliga al ESP32 a actuar solo como cliente
  WiFi.disconnect();   // Limpia conexiones pasadas atoradas
  delay(100);
  // ----------------------------

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado. IP: " + WiFi.localIP().toString());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String mensaje = "";
  for (int i = 0; i < length; i++) {
    mensaje += (char)payload[i];
  }
  
  // ACCIÓN DE LA BOMBA
  if (String(topic) == topico_bomba) {
    if (mensaje == "0") {
      digitalWrite(PIN_RELE, LOW);
      Serial.println("-> Bomba APAGADA");
    } else if (mensaje == "1") {
      digitalWrite(PIN_RELE, HIGH);
      Serial.println("-> Bomba ENCENDIDA");
    }
  }

  // ACCIÓN DE LA COMIDA
  if (String(topic) == topico_comida) {
    if (mensaje == "1") {
      Serial.println("-> Soltando ración de comida...");
      miServo.write(90);  
      delay(800);         
      miServo.write(0);   
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Buscando a Mosquitto...");
    if (client.connect("ESP32_Pecera")) {
      Serial.println(" ¡Conectado!");
      client.subscribe(topico_bomba);
      client.subscribe(topico_comida);
    } else {
      Serial.print(" Falló. Reintentando en 5s...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, HIGH);

  miServo.attach(PIN_SERVO, 500, 2400);
  miServo.write(0); 

  sensorTemp.begin(); // Inicia el sensor de temperatura

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // --- Lógica para leer y enviar la temperatura cada 5 segundos ---
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= 5000) {
    tiempoAnterior = tiempoActual;
    
    sensorTemp.requestTemperatures(); // Pide la lectura al sensor
    float temperatura = sensorTemp.getTempCByIndex(0); // Obtiene el valor en Celsius
    
    // Si la lectura es válida, la envía a Node-RED
    if (temperatura != DEVICE_DISCONNECTED_C) {
      Serial.print("Enviando temperatura: ");
      Serial.print(temperatura);
      Serial.println(" °C");
      
      // Convierte el número a texto y lo publica por MQTT
      client.publish(topico_temperatura, String(temperatura).c_str());
    } else {
      Serial.println("Error: No se detecta el sensor DS18B20. Revisa la resistencia.");
    }
  }
}