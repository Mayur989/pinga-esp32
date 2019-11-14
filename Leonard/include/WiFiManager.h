#ifndef __WIFIMANAGER_H__
#define __WIFIMANAGER_H__

#include <WiFi.h>
#include <WiFiClientSecure.h>
// #include "HTTPClient.h"

#include "WiFiCredentials.h"
#include "FlashManager.h"
#include "GeorgeManager.h"

#include <sstream>

class WiFiManager {
  public:
    static std::string ssidConnected;
    static std::string passwordConnected;
    
    // Methods
    static void init();
    static bool begin(WiFiCredentials credentials);
    static bool connected();
    static std::string getStatus();
    static std::string listNetworks();
};

#endif //__WIFIMANAGER_H__