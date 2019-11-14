#ifndef __GEORGEMANAGER_H__
#define __GEORGEMANAGER_H__

#include <Arduino.h>

#include "NetworkData.h"
#include "WiFiManager.h"
#include "NetworkManager.h"

class CommunicationKeys {
  public:
    static const char* SEPARATOR;
    static const char* WIFI_CREDENTIALS;
    static const char* WIFI_STATUS;
    static const char* MQTT_STATUS;
    static const char* TELEMETRY_DATA;
};

class GeorgeManager {
  public:
  static void sendWiFiCredentials();
    static void sendWiFiCredentials(WiFiCredentials credentials);
    static void requestWiFiStatus();
    static void requestMQTTStatus();
    static void sendTelemetry(NetworkData data);

    static void sendCurrentData();
};

#endif //__GEORGEMANAGER_H__