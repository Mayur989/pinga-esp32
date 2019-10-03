/**
 * Gustavo Viegas (3026)
 *
 * Data: 02/10/19
 * Descrição:
 * Hardware: Placa ESP32.
 */

#include <Bluetooth.hpp>

#define LED 2
int delayTime = 150;


/**
 * Pisca-se a led azul
 */
void piscaLed() {
  delay(delayTime);
  digitalWrite(LED, HIGH);
  delay(delayTime);
  digitalWrite(LED, LOW);
}

/**
 * Hook de configuração
 */
void setup() {
  //  Inicializa as led como output
  pinMode(LED, OUTPUT);

  // Configura e inicia o BLE
  BluetoothManager::setup();
}

/**
 * Hook de repetição
 */
void loop() {
  piscaLed();

  if (BluetoothManager::connected) {
    BluetoothManager::notifyDeviceStatus();
  }
}