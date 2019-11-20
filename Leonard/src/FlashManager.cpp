#include "FlashManager.h"

Preferences FlashManager::prefs;

void FlashManager::setup() {
  prefs.begin("credentials", false);
}

void FlashManager::saveWiFiCredentials(WiFiCredentials credentials) {
  prefs.putString("ssid", credentials.ssid.c_str());
  prefs.putString("password", credentials.password.c_str());

  Serial.print("\nValor armazenado em SSID: ");
  Serial.println(prefs.getString("ssid"));

  Serial.print("\nValor armazenado em password: ");
  Serial.println(prefs.getString("password"));
}

WiFiCredentials FlashManager::getWiFiCredentials() {
  WiFiCredentials credentials;

  prefs.clear();

  Serial.printf("\nPegando SSID da flash: %s\n", prefs.getString("ssid", "Viegas"));
  Serial.printf("\nPegando senha da flash: %s\n", prefs.getString("password", "steelers"));

  credentials.ssid = std::string(prefs.getString("ssid", "Viegas").c_str());
  credentials.password = std::string(prefs.getString("password", "steelers").c_str());

  return credentials;
}
