#pragma once

#include <Arduino.h>

const int RX_PIN = 16;
const int TX_PIN = 17;

void readSensorData() {
  if (!Serial2.available()) return;

  String data = Serial2.readStringUntil('\n');
  Serial.print("Received from Arduino: ");
  Serial.println(data);

  // Pisahkan ke dalam 5 elemen
  int idx1 = data.indexOf(',');
  int idx2 = data.indexOf(',', idx1 + 1);
  int idx3 = data.indexOf(',', idx2 + 1);
  int idx4 = data.indexOf(',', idx3 + 1);

  if (idx1 == -1 || idx2 == -1 || idx3 == -1 || idx4 == -1) return;

  String phStr = data.substring(0, idx1);
  String tempStr = data.substring(idx1 + 1, idx2);
  String turbStr = data.substring(idx2 + 1, idx3);
  String lvlStr = data.substring(idx3 + 1, idx4);
  String checksumStr = data.substring(idx4 + 1);

  // Hitung ulang checksum (tanpa menyertakan checksum yang dikirim)
  String rawData = data.substring(0, idx4);
  int calcChecksum = 0;
  for (char c : rawData) calcChecksum += c;

  int receivedChecksum = checksumStr.toInt();

  if (calcChecksum != receivedChecksum) {
    Serial.println("Checksum mismatch! Data rejected.");
    return;
  }

  // Parsing nilai numerik
  float ph = phStr.toFloat();
  float temp = tempStr.toFloat();
  float turbidity = turbStr.toFloat();
  float level = lvlStr.toFloat();

  if (isnan(ph) || isnan(temp) || isnan(turbidity) || isnan(level)) return;

  // Simpan ke variabel global
  lastPh = ph;
  lastTemp = temp;
  lastTurbidity = turbidity;
  lastWaterLevel = level;
  newDataAvailable = true;
}
