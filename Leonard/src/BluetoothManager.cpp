/**
 * Gustavo Viegas (3026)
 *
 * Data: 02/10/19
 * Descrição:
 * Hardware: Placa ESP32.
 */
#include "BluetoothManager.h"

const std::string BluetoothManager::keyDelimiter = "=";
const std::string BluetoothManager::valueDelimiter = "_!_";
bool BluetoothManager::connected = false;
BLEServer *BluetoothManager::pServer = NULL;
BLEService *BluetoothManager::pService = NULL;
BLECharacteristic *BluetoothManager::pChar = NULL;
BLECharacteristic *BluetoothManager::pCharacteristic = NULL;

void PingaBLECallbacks::onConnect(BLEServer* pServer) {
  Serial.println("Conectado");

  Serial.println(WiFiManager::listNetworks().c_str());

  BluetoothManager::connected = true;
};
void PingaBLECallbacks::onDisconnect(BLEServer* pServer) {
  Serial.println("Desconectado");
  BluetoothManager::connected = false;
};

void printStringToSerial(std::string value) { 
  Serial.println("*********");
  Serial.print("SSID: ");
  for (int i = 0; i < value.length(); i++)
    Serial.print(value[i]);
  Serial.println();
  Serial.println("*********");
}

void PingaBLECharacteristicCallbacks::onWrite(BLECharacteristic *pCharacteristic) {
  std::string rxValue = pCharacteristic->getValue();
  if (rxValue.length() <= 0) return;

  std::string operation = rxValue.substr(0, 3);
  std::string value = (rxValue.length() >= 4) ? rxValue.substr(4, rxValue.length()) : "";

  Serial.println(operation.c_str());
  Serial.println(value.c_str());

  if (operation.compare("WCR") == 0) {
    std::string ssid = value.substr(0, value.find(BluetoothManager::valueDelimiter));
    std::string password = value.substr(value.find(BluetoothManager::valueDelimiter) + BluetoothManager::valueDelimiter.length(), value.length());

    WiFiCredentials credentials;
    credentials.ssid = ssid;
    credentials.password = password;
    bool connection = WiFiManager::begin(credentials);

    if (connection) {
      FlashManager::saveWiFiCredentials(credentials);
      GeorgeManager::sendWiFiCredentials(credentials);
    }

    std::string returnValue = (connection) ? "WCR=true" : "WCR=false";
    BluetoothManager::notifyData(returnValue);
  } else if (operation.compare("WTC") == 0) {
    std::string returnValue = (2 > 0) ? "WTC=true" : "WTC=false";
    BluetoothManager::notifyData(returnValue);
  } else if (operation.compare("WNL") == 0) {
    std::string networks = WiFiManager::listNetworks();
    std::string returnValue = "WNL=" + networks;
    Serial.println(returnValue.c_str());
    BluetoothManager::notifyData(returnValue);
  }
}

/**
 * Configura o dispositivo BLE
 */
void BluetoothManager::setup() {
  BLEDevice::init("ViegasESP32_BLE");

  pServer = BLEDevice::createServer();

  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE |
    BLECharacteristic::PROPERTY_NOTIFY |
    BLECharacteristic::PROPERTY_INDICATE
  );
  pChar = pService->createCharacteristic(
    CHARACTERISTIC2_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE |
    BLECharacteristic::PROPERTY_NOTIFY |
    BLECharacteristic::PROPERTY_INDICATE
  );

  pServer->setCallbacks(new PingaBLECallbacks());
  pCharacteristic->setCallbacks(new PingaBLECharacteristicCallbacks());
  pChar->addDescriptor(new BLE2902());

  pService->start();
  pServer->getAdvertising()->start();

  Serial.println("Dispositivo pronto para ser pareado!");
}

std::string BluetoothManager::getDeviceStatus() {
  std::string status = WiFiManager::getStatus();
  return status;
}

void BluetoothManager::notifyDeviceStatus() {
  notifyData(getDeviceStatus());
}

void BluetoothManager::notifyData(std::string data) {
  char returnChars[data.size()];
  strcpy(returnChars, data.c_str());

  BluetoothManager::pCharacteristic->setValue(returnChars);
  BluetoothManager::pCharacteristic->notify();

  Serial.print(".");
  delay(BLUETOOTH_SEND_DELAY);
}