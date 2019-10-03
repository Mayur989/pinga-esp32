#include "WiFi.h"
#include <sstream>

class WiFiManager {
  public:
    static boolean connected;
    static std::string ssidConnected;
    static bool begin(std::string ssid, std::string password);
    static std::string getStatus();
};