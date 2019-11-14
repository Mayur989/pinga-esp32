#include "GeorgeManager.h"

const char* CommunicationKeys::SEPARATOR = "||";
const char* CommunicationKeys::WIFI_CREDENTIALS = "WC";
const char* CommunicationKeys::WIFI_STATUS = "WS";
const char* CommunicationKeys::MQTT_STATUS = "MS";
const char* CommunicationKeys::TELEMETRY_DATA = "TD";

void GeorgeManager::sendWiFiCredentials() {
  WiFiCredentials credentials;
  credentials.ssid = WiFiManager::ssidConnected;
  credentials.password = WiFiManager::passwordConnected;

  sendWiFiCredentials(credentials);
}


void GeorgeManager::sendWiFiCredentials(WiFiCredentials credentials) {
  if (!Serial2.available() || !WiFiManager::connected()) return;

  String key = CommunicationKeys::WIFI_CREDENTIALS;
  std::stringstream ss;

  ss << "WC=" << credentials.ssid << CommunicationKeys::SEPARATOR << credentials.password;
  Serial.printf("[GM] Enviando: %s \n", ss.str().c_str());
  Serial2.println(ss.str().c_str());
}

void GeorgeManager::sendTelemetry(NetworkData data) {
  if (!Serial2.available()) return;

  std::stringstream ss;

  ss << "TD=" << data.ssid << CommunicationKeys::SEPARATOR << data.speed;
  Serial.printf("[GM] Enviando: %s \n", ss.str().c_str());
  Serial2.println(ss.str().c_str());
}

void GeorgeManager::sendCurrentData() {
  digitalWrite(2, HIGH);

  NetworkManager::updateSpeed();
  NetworkData data = NetworkManager::getCurrentData(); 
  sendTelemetry(data);

  digitalWrite(2, LOW);
}