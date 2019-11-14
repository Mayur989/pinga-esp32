#include "NetworkManager.h"

HTTPClient NetworkManager::http;
double NetworkManager::lastSpeed = 0.0;

double NetworkManager::getSpeed() {
  return lastSpeed;
}

void NetworkManager::updateSpeed() {
  // lastSpeed = (-30.0 / WiFi.RSSI()) * 11.5;
  // // lastSpeed = (WiFi.RSSI() / -100.0) * 10.5;
  // if (lastSpeed < 0) lastSpeed *= -1;

  // Serial.printf("RSSI: %d, SPEED: %lf\n", WiFi.RSSI(), lastSpeed);
  if (!WiFiManager::connected) return;

  unsigned long startTime = millis();
  unsigned long finishTime;
  double speed = 0.0;

  const size_t dataSize = 4 * 8; // Tamanho dos dados a chegar em MegaBits

  http.begin("http://107.170.96.207:7788/");
  int httpCode = http.GET();

  Serial.printf("Status: %d\n", httpCode);
  
  finishTime = millis();
  unsigned long totalTime = finishTime - startTime;
    
  // Convertendo milisegundo pra segundo e pegando a velocidade em Mb/s;
  speed = (dataSize * 1000.0) / totalTime;

  Serial.printf("Data Size: %d\n", dataSize);
  Serial.printf("Tempo total (ms): %lu\n", totalTime);
  Serial.printf("Velocidade: %lf Mb/s\n", speed);

  lastSpeed = speed;
  http.end();
};


NetworkData NetworkManager::getCurrentData() {
  NetworkData data;
  data.connected = WiFiManager::connected;
  data.ssid = WiFiManager::ssidConnected;
  data.speed = getSpeed();

  Serial.printf("***TELEMETRY: *** \n\t SSID: %s \n\t SPEED: %lf\n *******\n", data.ssid.c_str(), data.speed);

  return data;
}