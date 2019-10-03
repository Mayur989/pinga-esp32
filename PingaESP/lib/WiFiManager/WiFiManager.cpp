#include "WiFiManager.hpp"

bool WiFiManager::connected = false;
std::string WiFiManager::ssidConnected = "";

bool WiFiManager::begin(std::string ssid, std::string password) {
  int maxTries = 20;
  int tries = 0;

  char ssidChars[ssid.size() + 1];
  char passwordChars[ssid.size() + 1];
  
  strcpy(ssidChars, ssid.c_str());
  strcpy(passwordChars, password.c_str());

  WiFi.begin(ssidChars, passwordChars);

  while (WiFi.status() != WL_CONNECTED && tries <= maxTries) {
    delay(200);
    tries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    connected = true;
    ssidConnected = ssid;
    Serial.println("WiFi conectado com sucesso!");
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