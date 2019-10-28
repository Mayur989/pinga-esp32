#ifndef __NETWORKMANAGER_H__
#define __NETWORKMANAGER_H__

#include <random>
#include <Preferences.h>
#include "NetworkData.h"

class NetworkManager {
  public:
    static NetworkData getCurrentData();
};

#endif
