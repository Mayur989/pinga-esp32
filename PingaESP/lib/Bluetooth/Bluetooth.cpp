/**
 * Gustavo Viegas (3026)
 *
 * Data: 02/10/19
 * Descrição:
 * Hardware: Placa ESP32.
 */
#include "Bluetooth.hpp"

const std::string BluetoothManager::delimiter = "_!_";
bool BluetoothManager::connected = false;
BLEServer *BluetoothManager::pServer = NULL;
BLEService *BluetoothManager::pService = NULL;
BLECharacteristic *BluetoothManager::pChar = NULL;
BLECharacteristic *BluetoothManager::pCharacteristic = NULL;

void PingaBLECallbacks::onConnect(BLEServer* pServer) {
  Serial.println("Conectado");
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

  if (rxValue.length() > 0) {
    std::string ssid = rxValue.substr(0, rxValue.find(BluetoothManager::delimiter));
    std::string password = rxValue.substr(rxValue.find(BluetoothManager::delimiter) + BluetoothManager::delimiter.length(), rxValue.length());

    printStringToSerial(ssid);
    printStringToSerial(password);

    std::string returnValue = "WCR=" + (WiFiManager::begin(ssid, password)) ? "true" : "false";
    BluetoothManager::notifyData(returnValue);
  }
}

/**
 * Configura o dispositivo BLE
 */
void BluetoothManager::setup() {
  Serial.begin(115200);

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