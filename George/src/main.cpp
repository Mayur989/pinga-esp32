/**
 * Responsável por enviar dados pro Google IOT.
 * Gustavo Viegas (3026)
 *
 * Data: 02/10/19
 * Descrição:
 * Hardware: Placa ESP32 - GEORGE.
 */

#include "WiFiManager.h"
#include "LeonardManager.h"

#define LED 2

#define RX_2 16
#define TX_2 17

int delayTime = 150;
unsigned long lastMillisMQTT = 0;
unsigned long lastMillisSerial = 60000;
unsigned int retries = 0;

/**
 * Hook de configuração
 */
void setup() {
  //  Inicializa as led como output
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  // Inicializa o Serial
  Serial.begin(115200);

  // Inicializa o Serial com a outra placa
  Serial2.begin(115200, SERIAL_8N1, RX_2, TX_2);

  // Tenta iniciar o Wi-Fi se tiver credenciais salvas
  WiFiManager::init();
}

void loopIOT() {
  if (!WiFiManager::connected()) return;

  // Reseta a placa se não conseguiu mandar pacotes 6 vezes seguidas.
  retries++;
  if (retries >= 6) {
    ESP.restart();
  }

  if (IOTManager::mqttClient != NULL && IOTManager::mqttClient->lastError() != LWMQTT_SUCCESS) {
    Serial.println("O útlimo status foi erro.");
    if (WiFiManager::connected()) {
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

  retries = 0;
  IOTManager::mqttClient->loop();
  delay(150);
}

void loopSerial() {
  LeonardManager::readCommand();
}

/**
 * Hook de repetição
 */
void loop() {
  delay(50); // Ajuste para evitar problemas de instabilidade
  loopIOT();

  loopSerial();
}
