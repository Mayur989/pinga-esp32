#ifndef __FLASHMANAGER_H__
#define __FLASHMANAGER_H__

#include <Preferences.h>
#include "WiFiCredentials.h"

class FlashManager {
  public:
    static Preferences prefs;
    static void setup();
    static void saveWiFiCredentials(WiFiCredentials credentials);
    static WiFiCredentials getWiFiCredentials();
};

#endif
