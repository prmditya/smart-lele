#pragma once
#include <WiFi.h>
#include <vector>

struct WiFiCredential {
  const char* ssid;
  const char* password;
};

const std::vector<WiFiCredential> networks = {
  { "thokayna", "hasnakamila" },  // Prioritas utama
  { "HIFI", "11223344" },         // Backup 1
  { "Smart-Lele", "password" }    // Backup
};

bool connectWiFi() {
  Serial.println("Scanning available networks...");

  int numNetworks = WiFi.scanNetworks();
  if (numNetworks == 0) {
    Serial.println("No WiFi networks found");
    return false;
  }

  for (const auto& network : networks) {
    bool networkFound = false;
    for (int i = 0; i < numNetworks; ++i) {
      if (strcmp(WiFi.SSID(i).c_str(), network.ssid) == 0) {
        networkFound = true;
        break;
      }
    }

    if (!networkFound) {
      Serial.print("Network not found: ");
      Serial.println(network.ssid);
      continue;
    }

    Serial.print("Attempting to connect to: ");
    Serial.println(network.ssid);

    WiFi.begin(network.ssid, network.password);

    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && (millis() - startTime) < 15000) {
      delay(500);
      Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConnected successfully!");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      return true;
    }

    Serial.println("\nConnection failed");
    WiFi.disconnect();
    delay(1000);
  }

  Serial.println("Failed to connect to any known network");
  return false;
}

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}