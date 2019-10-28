#include "WiFiManager.h"

WiFiClientSecure* WiFiManager::secureClient = new WiFiClientSecure();
// HTTPClient WiFiManager::http;

bool WiFiManager::connected = false;
std::string WiFiManager::ssidConnected = "";
std::string WiFiManager::testConnectionURL = "http://5d9b2503686ed000144d1cfb.mockapi.io/api/v1/availability";
std::string WiFiManager::testConnectionCertificate = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4G\n" \
"A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNp\n" \
"Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1\n" \
"MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEG\n" \
"A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n" \
"hvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6ErPL\n" \
"v4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8\n" \
"eoLrvozps6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklq\n" \
"tTleiDTsvHgMCJiEbKjNS7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzd\n" \
"C9XZzPnqJworc5HGnRusyMvo4KD0L5CLTfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pa\n" \
"zq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6CygPCm48CAwEAAaOBnDCB\n" \
"mTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUm+IH\n" \
"V2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5n\n" \
"bG9iYWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG\n" \
"3lm0mi3f3BmGLjANBgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4Gs\n" \
"J0/WwbgcQ3izDJr86iw8bmEbTUsp9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO\n" \
"291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu01yiPqFbQfXf5WRDLenVOavS\n" \
"ot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG79G+dwfCMNYxd\n" \
"AfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n" \
"TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n" \
"-----END CERTIFICATE-----\n";

void WiFiManager::init() {
  FlashManager::setup();
  WiFiCredentials credentials = FlashManager::getWiFiCredentials();
  begin(credentials);
}

bool WiFiManager::begin(WiFiCredentials credentials) {
  int maxTries = 20;
  int tries = 0;

  char ssidChars[credentials.ssid.size() + 1];
  char passwordChars[credentials.ssid.size() + 1];

  strcpy(ssidChars, credentials.ssid.c_str());
  strcpy(passwordChars, credentials.password.c_str());

  WiFi.begin(ssidChars, passwordChars);
  while (WiFi.status() != WL_CONNECTED && tries <= maxTries) {
    delay(200);
    tries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    connected = true;
    ssidConnected = credentials.ssid;
    Serial.println("WiFi conectado com sucesso!");

    IOTManager::setup();

    return true;
  } else {
    connected = false;
    ssidConnected = "";
    Serial.println("WiFi não conectado!");
    return false;
  }
}

std::string WiFiManager::getStatus() {
  std::stringstream ss;
  ss << "WST=" << (connected ? "true" : "false") << "&WID=" << ssidConnected;
  return ss.str();
}

std::string WiFiManager::listNetworks() {
    int networksCount = WiFi.scanNetworks();
    std::string networks;
    std::string delimiter = ";";

    Serial.println("WiFi scan feito");
    if (networksCount == 0) {
        Serial.println("Nenhuma rede disponível");
    } else {
        Serial.print(networksCount);
        Serial.println(" redes encontradas");

        for (int i = 0; i < networksCount; ++i) {
            // Print SSID and RSSI for each network found
            String ssid = WiFi.SSID(i);
            int rssi = WiFi.RSSI(i);

            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(ssid);
            Serial.print(" (");
            Serial.print(rssi);
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");

            std::string str(ssid.c_str());
            networks += str;
            if (i < (networksCount - 1)) networks += delimiter;

            delay(10);
        }
    }
    Serial.println("");

    return networks;
}

bool WiFiManager::testConnection() {
  if (!secureClient) return false;

  secureClient->setCACert(testConnectionCertificate.c_str());

  // TODO: Isso
  return false;

  // // if (!http.begin(*client, testConnectionURL.c_str())) return false;

  // if (!http.begin(testConnectionURL.c_str())) return false;

  // int httpCode = http.GET();
  // if (httpCode <= 0) return false;
  // Serial.println(httpCode);

  // return (httpCode < 500);
}
