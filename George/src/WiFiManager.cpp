#include "WiFiManager.h"

bool WiFiManager::connected = false;

void WiFiManager::init() {
  FlashManager::setup();
  WiFiCredentials credentials = FlashManager::getWiFiCredentials();
  begin(credentials);
}

bool WiFiManager::begin(WiFiCredentials credentials) {
  if (WiFi.status() == WL_CONNECTED) WiFi.disconnect();

  int maxTries = 20;
  int tries = 0;

  char ssidChars[credentials.ssid.size() + 1];
  char passwordChars[credentials.ssid.size() + 1];

  strcpy(ssidChars, credentials.ssid.c_str());
  strcpy(passwordChars, credentials.password.c_str());

  WiFi.begin(ssidChars, passwordChars);
  while (WiFi.status() != WL_CONNECTED && tries <= maxTries) {
    delay(200);
    tries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    connected = true;
    ssidConnected = credentials.ssid;
    Serial.println("WiFi conectado com sucesso!");

    IOTManager::setup();

    return true;
  } else {
    connected = false;
    ssidConnected = "";
    Serial.println("WiFi não conectado!");
    return false;
  }
}

std::string WiFiManager::getStatus() {
  std::stringstream ss;
  ss << "WST=" << (connected ? "true" : "false") << "&WID=" << ssidConnected;
  return ss.str();
}