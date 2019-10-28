#include "IOTManager.h"

WiFiClientSecure IOTManager::client;

void IOTManager::setupClient() {
  if (!WiFiManager::connected) return;

  client.setCACert(GOOGLE_CERT);

  if (!client.connect(GOOGLE_HOST, 443)) {
    Serial.println("Conexão falhou");
    return;
  }

  Serial.println("Conexão ao Google OK!");
  delay(50);

  String jwt_token = (jwt.length() > 0) ? jwt : getJwt();
  std::string token(jwt_token.c_str());
  std::string authHeader = "Authorization: Bearer " + token;
  String data = "{\"binary_data\": \"dGVzdGUgZGEgRVNQMzI=\"}";

  client.println("POST https://cloudiotdevice.googleapis.com/v1/projects/pinga-256611/locations/europe-west1/registries/pinga-registry/devices/pinga:publishEvent HTTP/1.1");
  client.println(authHeader.c_str());
  client.println("Host: " + String(GOOGLE_HOST));
  client.println("Accept: */*");
  client.println("Content-Type: application/json");
  client.println("Connection: close");

  client.print("Content-Length: ");
  client.println(data.length());

  client.println(data);
  delay(10);

  String response = client.readString();
  Serial.printf("Resposta: %s\n", response);

  while (client.connected()) {
    String line = client.readStringUntil('\n');

    if (line == "\r") {
      Serial.println("Headers recebidas!");
      break;
    }
  }

  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  client.stop();
}


CloudIoTCoreDevice* IOTManager::device;
CloudIoTCoreMqtt* IOTManager::mqtt;
WiFiClientSecure* IOTManager::netClient;
MQTTClient* IOTManager::mqttClient;
unsigned long IOTManager::iss = 0;
String IOTManager::jwt;


// Foward to class-declarations from global handler
extern String getJwt() {
  IOTManager::iss = time(nullptr);

  if (!IOTManager::device) {
    Serial.println("Sem device setado");
    return ".";
  }

  IOTManager::jwt = IOTManager::device->createJWT(IOTManager::iss, jwt_exp_secs);
  return IOTManager::jwt;
}

extern void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if (payload == "ledon") {
    digitalWrite(2, HIGH);
  }
}

void IOTManager::setup(void) {
  Serial.println("Setting up IOT");
  configTime(0, 0, ntp_primary, ntp_secondary);

  Serial.println("Waiting on time sync...");
  while (time(nullptr) < 1510644967) {
    delay(10);
  }
  Serial.println("Synced!");

  device = new CloudIoTCoreDevice(
    project_id, location, registry_id, device_id,
    private_key_str
  );
  netClient = new WiFiClientSecure(); // WiFiManager::http
  mqttClient = new MQTTClient(700);
  mqttClient->setOptions(32, true, 14500); // keepAlive, cleanSession, timeout
  mqtt = new CloudIoTCoreMqtt(mqttClient, netClient, device);
  mqtt->setUseLts(true);
  mqtt->startMQTT();

  Serial.println("IOTManager Setup finished! Connecting...");
  connect();
}

void IOTManager::connect(void) {
  Serial.println("Conectando MQTT");
  mqtt->mqttConnect();
  String status = (mqttClient->connected()) ? "SIM" : "NÃO";
  Serial.println("MQTT Conectado: " + status);
}

String IOTManager::getDefaultSensor() {
  return  "Wifi: " + String(WiFi.RSSI()) + "db";
}

bool IOTManager::ready() {
  return WiFiManager::connected && mqttClient && mqttClient->connected();
}

void IOTManager::getReady() {
  if (!WiFiManager::connected) return;
  if (!mqttClient) setup();
  if (mqttClient) connect();
}

void IOTManager::publishNetworkData() {
  NetworkData data = NetworkManager::getCurrentData();
  std::string connected = (data.connected) ? "true" : "false";
  std::stringstream ss;
  ss << connected << "||" << data.ssid << "||" << data.connected << std::endl;

  String telemetry = ss.str().c_str();

  Serial.printf("Enviando: %s de tamanho %u\n", telemetry.c_str(), sizeof(telemetry));
  mqtt->publishTelemetry(telemetry.c_str());
  delay(10);
}