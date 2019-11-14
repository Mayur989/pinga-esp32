#include "WiFiManager.h"

std::string WiFiManager::ssidConnected = "";
std::string WiFiManager::passwordConnected = "";

void WiFiManager::init() {
  FlashManager::setup();
  WiFiCredentials credentials = FlashManager::getWiFiCredentials();
  begin(credentials);
}

bool WiFiManager::connected() {
  return (WiFi.status() == WL_CONNECTED);
}

bool WiFiManager::begin(WiFiCredentials credentials) {
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

  ssidConnected = credentials.ssid;
  passwordConnected = credentials.password;

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi conectado com sucesso!");

    GeorgeManager::sendWiFiCredentials(credentials);

    return true;
  } else {
    Serial.println("WiFi não conectado!");
    return false;
  }
}

std::string WiFiManager::getStatus() {
  std::stringstream ss;
  ss << "WST=" << (connected() ? "true" : "false") << "&WID=" << ssidConnected;
  return ss.str();
}

std::string WiFiManager::listNetworks() {
  int networksCount = WiFi.scanNetworks();
  std::string networks;
  std::string delimiter = ";";

  Serial.println("WiFi scan feito");
  if (networksCount == 0) {
    Serial.println("Nenhuma rede disponível");
  } else {
    Serial.print(networksCount);
    Serial.println(" redes encontradas");

    for (int i = 0; i < networksCount; ++i) {
      // Print SSID and RSSI for each network found
      String ssid = WiFi.SSID(i);
      int rssi = WiFi.RSSI(i);

      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(ssid);
      Serial.print(" (");
      Serial.print(rssi);
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");

      std::string str(ssid.c_str());
      networks += str;
      if (i < (networksCount - 1)) networks += delimiter;

      delay(10);
    }
  }
  Serial.println("");

  return networks;
}