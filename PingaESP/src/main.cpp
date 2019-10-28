/**
 * Gustavo Viegas (3026)
 *
 * Data: 02/10/19
 * Descrição:
 * Hardware: Placa ESP32.
 */

#include <BluetoothManager.h>
#include <WiFiManager.h>

#define LED 2
int delayTime = 150;
unsigned long lastMillisMQTT = 0;
unsigned long lastMillisBLE = 60000;
unsigned int retries = 0;

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
  digitalWrite(LED, LOW);

  // Inicializa o Serial
  Serial.begin(115200);

  // Tenta iniciar o Wi-Fi se tiver credenciais salvas
  WiFiManager::init();

  // Configura e inicia o BLE
  BluetoothManager::setup();
}

void loopIOT() {
  // Reseta a placa se não conseguiu mandar pacotes 6 vezes seguidas.
  retries++;
  if (retries >= 6) {
    ESP.restart();
  }

  if (IOTManager::mqttClient != NULL && IOTManager::mqttClient->lastError() != LWMQTT_SUCCESS) {
    Serial.println("O útlimo status foi erro, desconectando bluetooth e MQTT.");
    if (WiFiManager::connected && BluetoothManager::connected) {
      ESP.restart();
      return;
    }

    IOTManager::getReady();
  }

  if (!IOTManager::ready()) {
    Serial.println("[MAIN] GET READY!");
    IOTManager::getReady();
    return;
  }
  
  if (IOTManager::mqttClient && !IOTManager::mqttClient->connected()) {
    Serial.println("[MAIN] CONNECT!");
    IOTManager::connect();
    return;
  }

  Serial.println("[MAIN] LOOP E PUBLISH!");
  retries = 0;
  IOTManager::mqttClient->loop();
  delay(50);
  IOTManager::publishNetworkData();
}

void loopBLE() {
  if (BluetoothManager::connected) {
    Serial.println("[MAIN] BLE!");
    BluetoothManager::notifyDeviceStatus();
  }
}

/**
 * Hook de repetição
 */
void loop() {
  // piscaLed();
  delay(20); // Ajuste para evitar problemas de instabilidade

  // Alterna a execução entre BLE e MQTT
  unsigned long currentMillis = millis();

  if (currentMillis - lastMillisMQTT > 10000) {
    lastMillisMQTT = currentMillis;
    loopIOT();
  } else if (currentMillis - lastMillisBLE > 1500) {
    lastMillisBLE = currentMillis;
    loopBLE();
  }
}
