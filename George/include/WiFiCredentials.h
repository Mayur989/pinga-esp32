#ifndef __WIFICREDENTIALS_H__
#define __WIFICREDENTIALS_H__

#include <Arduino.h>

typedef struct WiFiCredentials {
  std::string ssid;
  std::string password;
} WiFiCredentials;

#endif