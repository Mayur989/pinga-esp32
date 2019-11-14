/**
 * Responsável por coletar dados da velocidade da internet e gerenciar a conexão das placas 
 * (Leonard e George) com a rede Wi-Fi.
 * Gustavo Viegas (3026)
 *
 * Data: 02/10/19
 * Descrição:
 * Hardware: Placa ESP32 - LEONARD.
 */

#include "BluetoothManager.h"
#include "WiFiManager.h"
#include "GeorgeManager.h"

#define LED 2

#define RX_2 16
#define TX_2 17

int maxLoops = 10;
int currentLoop = 0;
unsigned long lastMillisIOT = 0;
unsigned long lastMillisBLE = 60000;

/**
 * Hook de configuração
 */
void setup() {
  //  Inicializa as led como output
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  // Inicializa o Serial com o PC
  Serial.begin(115200);

  // Inicializa o Serial com a outra placa
  Serial2.begin(115200, SERIAL_8N1, RX_2, TX_2);

  // Tenta iniciar o Wi-Fi se tiver credenciais salvas
  WiFiManager::init();

  // Configura e inicia o BLE
  BluetoothManager::setup();
}

void loopIOT() {
  if (!WiFiManager::connected()) {
    currentLoop++;

    // Reseta a placa se passou muito tempo sem conexao ao wifi.
    if (currentLoop == maxLoops) {
      WiFiCredentials credentials = FlashManager::getWiFiCredentials();
      WiFiManager::begin(credentials);
    } else if (currentLoop > maxLoops) {
      ESP.restart();
    }

    return;
  }

  GeorgeManager::sendWiFiCredentials();
  delay(150);
  GeorgeManager::sendCurrentData();

  currentLoop = 0;
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
  delay(20); // Ajuste para evitar problemas de instabilidade

  // Alterna a execução entre BLE e IOT
  unsigned long currentMillis = millis();

  if (currentMillis - lastMillisIOT > 7500) {
    Serial.println("IOT");
    lastMillisIOT = currentMillis;
    loopIOT();
  } else if (currentMillis - lastMillisBLE > 5000) {
    Serial.println("BLE");
    lastMillisBLE = currentMillis;
    loopBLE();
  }
}
