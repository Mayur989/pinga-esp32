#include "IOTManager.h"

WiFiClientSecure IOTManager::client;
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
  netClient = new WiFiClientSecure();
  mqttClient = new MQTTClient(700);
  mqttClient->setOptions(180, false, 25000); // keepAlive, cleanSession, timeout
  mqtt = new CloudIoTCoreMqtt(mqttClient, netClient, device);
  mqtt->setLogConnect(false);
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

bool IOTManager::ready() {
  return WiFiManager::connected && mqttClient && mqttClient->connected();
}

void IOTManager::getReady() {
  if (!WiFiManager::connected) return;
  if (!mqttClient) setup();
  if (mqttClient) connect();
}

String formatTelemetry(NetworkData data) {
  std::string connected = (data.connected) ? "true" : "false";
  std::stringstream ss;
  ss << connected << "||" << data.ssid << "||" << data.speed << std::endl;

  String telemetry = ss.str().c_str();
  return telemetry;
}

void IOTManager::publishNetworkData(NetworkData data) {
  String telemetry = formatTelemetry(data);
  Serial.printf("Enviando: %s \n", telemetry.c_str());
  mqtt->publishTelemetry(telemetry);
  delay(20);
}