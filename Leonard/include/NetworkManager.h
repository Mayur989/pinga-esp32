#ifndef __NETWORKMANAGER_H__
#define __NETWORKMANAGER_H__

#include <HTTPClient.h>
#include <WiFi.h>

#include "NetworkData.h"
#include "WiFiManager.h"

class NetworkManager {
  public:
    static double lastSpeed;
    static HTTPClient http;

    static NetworkData getCurrentData();
    static double getSpeed();
    static double getNetworkSpeed();
    static void updateSpeed();
};

#endif
