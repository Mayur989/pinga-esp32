#ifndef __WIFIMANAGER_H__
#define __WIFIMANAGER_H__

#include <WiFi.h>
#include <WiFiClientSecure.h>
// #include "HTTPClient.h"

#include "WiFiCredentials.h"
#include "IOTManager.h"
#include "FlashManager.h"

#include <sstream>

class WiFiManager {
  public:
    // Attributes
    static WiFiClientSecure* secureClient;
    // static HTTPClient http;

    static boolean connected;
    static std::string ssidConnected;
    static std::string testConnectionURL;
    static std::string testConnectionCertificate;
    
    // Methods
    static void init();
    static bool begin(WiFiCredentials credentials);
    static std::string getStatus();
    static std::string listNetworks();
    static bool testConnection();
};

#endif //__WIFIMANAGER_H__