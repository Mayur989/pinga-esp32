#include "NetworkManager.h"

NetworkData NetworkManager::getCurrentData() {
  NetworkData data;
  data.connected = WiFiManager::connected;
  data.ssid = WiFiManager::ssidConnected;
  data.speed =  (double) (((float)rand()/(float)(RAND_MAX)) * 2);

  return data;
}