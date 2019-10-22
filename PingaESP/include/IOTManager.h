#ifndef __IOTMANAGER_H__
#define __IOTMANAGER_H__

#include <Arduino.h>
#include <Client.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "WiFiManager.h"

#include <MQTT.h>

#include "IOTConfig.h"
#include <CloudIoTCore.h>
#include <CloudIoTCoreMqtt.h>

extern String getJwt();
extern void messageReceived(String &topic, String &payload);

class IOTManager {
  public:
    static CloudIoTCoreDevice *device;
    static CloudIoTCoreMqtt *mqtt;
    static WiFiClientSecure *netClient;
    static MQTTClient *mqttClient;
    static unsigned long iss;
    static String jwt;

    static void setup(void);
    static void connect(void);

    static void messageReceived(String &topic, String &payload);
    static String getDefaultSensor();
    static void publishTelemetry(String data);
    static void publishTelemetry(const char* data, int length);
    static void publishTelemetry(String subfolder, String data);
    static void publishTelemetry(String subfolder, const char* data, int length);
};


#endif //__IOTMANAGER_H__