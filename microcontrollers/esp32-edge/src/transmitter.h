#pragma once

#include <HTTPClient.h>
#include "utils.h"

const char* SERVER_URL = "http://smart-lele.my.id/insert_data.php";
const unsigned long SEND_INTERVAL = 1 * 60 * 1000;  // 1 minute

unsigned long previousMillis = 0;

WiFiClient client;
HTTPClient http;

void sendDataToServer(const String& payload) {
  if (!isWiFiConnected()) {
    Serial.println("WiFi disconnected. Reconnecting...");
    connectWiFi();
    return;
  }

  http.begin(client, SERVER_URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int responseCode = http.POST(payload);
  if (responseCode > 0) {
    Serial.println("Data sent successfully. Response: " + String(responseCode));
  } else {
    Serial.println("Error sending data. Response: " + String(responseCode));
  }

  http.end();
}

void sendDataIfReady() {
  if (!newDataAvailable) return;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis < SEND_INTERVAL) return;

  previousMillis = currentMillis;

  String payload = "ph=" + String(lastPh) + "&temp=" + String(lastTemp) + "&turbidity=" + String(lastTurbidity) + "&waterLevel=" + String(lastWaterLevel);

  uint32_t crc = calculateCRC(payload);
  payload += "&crc=" + String(crc, HEX);

  sendDataToServer(payload);
  newDataAvailable = false;
}