#pragma once

#include <WiFi.h>

const char* SSID = "HIFI";
const char* PASSWORD = "11223344";

void connectWiFi() {
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}