#include "IOTManager.h"

CloudIoTCoreDevice* IOTManager::device;
CloudIoTCoreMqtt* IOTManager::mqtt;
WiFiClientSecure* IOTManager::netClient;
MQTTClient* IOTManager::mqttClient;
unsigned long IOTManager::iss = 0;
String IOTManager::jwt;


// Foward to class-declarations from global handler
extern String getJwt() {
  IOTManager::iss = time(nullptr);
  Serial.println("Refreshing JWT");
  IOTManager::jwt = IOTManager::device->createJWT(IOTManager::iss, jwt_exp_secs);
  return IOTManager::jwt;
}

extern void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void IOTManager::setup(void) {
  Serial.println("Setting up IOT");
  configTime(0, 0, ntp_primary, ntp_secondary);
  
  Serial.println("Waiting on time sync...");
  while (time(nullptr) < 1510644967) {
    delay(10);
  }

  device = new CloudIoTCoreDevice(
    project_id, location, registry_id, device_id,
    private_key_str
  );
  netClient = new WiFiClientSecure(); // WiFiManager::http
  mqttClient = new MQTTClient(512);
  mqttClient->setOptions(180, true, 1000); // keepAlive, cleanSession, timeout
  mqtt = new CloudIoTCoreMqtt(mqttClient, netClient, device);
  mqtt->setUseLts(true);
  mqtt->startMQTT();
}

void IOTManager::connect(void) {
  mqtt->mqttConnect();
}

void IOTManager::messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

String IOTManager::getDefaultSensor() {
  return  "Wifi: " + String(WiFi.RSSI()) + "db";
}

void IOTManager::publishTelemetry(String data) {
  mqtt->publishTelemetry(data);
}

void IOTManager::publishTelemetry(const char* data, int length) {
  mqtt->publishTelemetry(data, length);
}

void IOTManager::publishTelemetry(String subfolder, String data) {
  mqtt->publishTelemetry(subfolder, data);
}

void IOTManager::publishTelemetry(String subfolder, const char* data, int length) {
  mqtt->publishTelemetry(subfolder, data, length);
}