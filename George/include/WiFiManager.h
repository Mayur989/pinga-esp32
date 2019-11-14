#ifndef __WIFIMANAGER_H__
#define __WIFIMANAGER_H__

#include <WiFi.h>

#include "WiFiCredentials.h"
#include "IOTManager.h"
#include "FlashManager.h"

#include <sstream>

class WiFiManager {
  public:
    // Attributes
    static boolean connected;
    static std::string ssidConnected;
    
    // Methods
    static void init();
    static bool begin(WiFiCredentials credentials);
    static std::string getStatus();
};

#endif //__WIFIMANAGER_H__