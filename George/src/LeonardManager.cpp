#include "LeonardManager.h"

const char* CommunicationKeys::SEPARATOR = "||";
const char* CommunicationKeys::WIFI_CREDENTIALS = "WC";
const char* CommunicationKeys::WIFI_STATUS = "WS";
const char* CommunicationKeys::MQTT_STATUS = "MS";
const char* CommunicationKeys::TELEMETRY_DATA = "TD";


// void LeonardManager::sendWiFiCredentials(WiFiCredentials credentials) {
//   if (!Serial2.available() || !WiFiManager::connected) return;

//   String key = CommunicationKeys::WIFI_CREDENTIALS;

//   Serial2.println(key + CommunicationKeys::SEPARATOR + credentials.ssid + CommunicationKeys::SEPARATOR + credentials.password);
// }

void LeonardManager::readCommand() {
  std::string command(Serial2.readStringUntil('\n').c_str());
  if (command.length() <= 0) return;

  std::string operation = command.substr(0, 2);
  std::string value = (command.length() >= 4) ? command.substr(4, command.length()) : "";

  if (operation.compare(CommunicationKeys::WIFI_CREDENTIALS) == 0) {
    WiFiCredentials credentials;

    credentials.ssid = value.substr(0, value.find(CommunicationKeys::SEPARATOR));
    credentials.password = value.substr(value.find(CommunicationKeys::SEPARATOR) + strlen(CommunicationKeys::SEPARATOR), value.length());

    bool connection = WiFiManager::begin(credentials);
    if (connection) FlashManager::saveWiFiCredentials(credentials);
  } else if (operation.compare(CommunicationKeys::TELEMETRY_DATA) == 0) {
    NetworkData data;

    std::string speedString = value.substr(value.find(CommunicationKeys::SEPARATOR) + strlen(CommunicationKeys::SEPARATOR), value.length());

    data.ssid = value.substr(0, value.find(CommunicationKeys::SEPARATOR));
    data.speed = std::strtod(speedString.c_str(), NULL);

    IOTManager::publishNetworkData(data);
  }
}