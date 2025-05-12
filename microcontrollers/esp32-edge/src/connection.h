#pragma once

#include <WiFi.h>

const char* SSID = "thokayna";
const char* PASSWORD = "hasnakamila";

void connectWiFi() {
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}