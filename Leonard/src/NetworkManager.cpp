#include "NetworkManager.h"

HTTPClient NetworkManager::http;
double NetworkManager::lastSpeed = 0.0;

double NetworkManager::getSpeed() {
  return lastSpeed;
}

double NetworkManager::getNetworkSpeed() {
  if (!WiFiManager::connected()) return 0.0;
  unsigned long startTime = millis();
  unsigned long finishTime;
  double speed = 0.0;

  // Tamanho dos dados a chegar em MegaBits
  const size_t dataSize = 4 * 8;

  http.begin("http://107.170.96.207:7788/");
  int httpCode = http.GET();

  Serial.printf("Status: %d\n", httpCode);
  if (httpCode < 200 || httpCode >= 400) {
    lastSpeed = 0;
    http.end();
    return 0.0;
  }
  
  finishTime = millis();
  unsigned long totalTime = finishTime - startTime;
    
  // Convertendo milisegundo pra segundo e pegando a velocidade em Mb/s;
  speed = (dataSize * 1000.0) / totalTime;

  Serial.printf("Tempo total (ms): %lu\n", totalTime);
  Serial.printf("Velocidade: %lf Mb/s\n", speed);

  http.end();
  return speed;
}

void NetworkManager::updateSpeed() {
  if (!WiFiManager::connected()) return;
  
  int requestsAmount = 5;
  std::vector<double> times;

  for (int i = 0; i < requestsAmount; i++) {
    times.push_back(getNetworkSpeed());
  }
  
  std::sort(times.begin(), times.end());
  
  for (int i = 0; i < times.size(); i++) {
    Serial.printf("\t \t [%d]=%lf", i, times[i]);
  }
  
  Serial.printf("Mediana: %lf \n", times[2]);
  lastSpeed = times[2];
};


NetworkData NetworkManager::getCurrentData() {
  NetworkData data;
  data.connected = WiFiManager::connected();
  data.ssid = WiFiManager::ssidConnected;
  data.speed = getSpeed();

  Serial.printf("***TELEMETRY: *** \n\t SSID: %s \n\t SPEED: %lf\n *******\n", data.ssid.c_str(), data.speed);

  return data;
}