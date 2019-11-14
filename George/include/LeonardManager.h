#ifndef __LEONARDMANAGER_H__
#define __LEONARDMANAGER_H__

#include <Arduino.h>
#include "WiFiManager.h"
#include "FlashManager.h"
#include "NetworkData.h"
#include "IOTManager.h"

class CommunicationKeys {
  public:
    static const char* SEPARATOR;
    static const char* WIFI_CREDENTIALS;
    static const char* WIFI_STATUS;
    static const char* MQTT_STATUS;
    static const char* TELEMETRY_DATA;
};

class LeonardManager {
  public:
    static void readCommand();
    static void sendWiFiStatus();
    static void sendMQTTStatus();
};

#endif //__LEONARDMANAGER_H__