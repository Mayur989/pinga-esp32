#ifndef __BLUETOOTHMANAGER_H__
#define __BLUETOOTHMANAGER_H__

/**
 * Gustavo Viegas (3026)
 *
 * Data: 02/10/19
 * Descrição:
 * Hardware: Placa ESP32.
 */
#include <sstream>
#include "WiFiManager.h"
#include "IOTManager.h"
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define BLUETOOTH_SEND_DELAY 450

#define SERVICE_UUID "00002424-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID  "00002424-0000-1000-8000-00805F9B34FC"
#define CHARACTERISTIC2_UUID "00002424-0000-1000-8000-00805F9B34FD"

class PingaBLECallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer);
  void onDisconnect(BLEServer* pServer);
};

class PingaBLECharacteristicCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic);
};

class BluetoothManager {
  public:
    static const std::string keyDelimiter;
    static const std::string valueDelimiter;
    
    static bool connected;
    static BLEServer *pServer;
    static BLEService *pService;
    static BLECharacteristic *pChar;
    static BLECharacteristic *pCharacteristic;

    static void setup();
    static std::string getDeviceStatus();
    static void notifyDeviceStatus();
    static void notifyData(std::string data);
};

#endif //__BLUETOOTHMANAGER_H__