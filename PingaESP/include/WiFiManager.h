#ifndef __WIFIMANAGER_H__
#define __WIFIMANAGER_H__

#include "WiFi.h"
#include "WiFiClientSecure.h"
// #include "HTTPClient.h"
#include "IOTManager.h"
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
    static bool begin(std::string ssid, std::string password);
    static std::string getStatus();
    static std::string listNetworks();
    static bool testConnection();
};

#endif //__WIFIMANAGER_H__