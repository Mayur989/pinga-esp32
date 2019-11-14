#ifndef __NETWORKDATA_H__
#define __NETWORKDATA_H__

#include <Preferences.h>

typedef struct NetworkData {
  double speed = 0.0;
  bool connected = false;
  std::string ssid;
} NetworkData;

#endif
