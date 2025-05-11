#pragma once

SoftwareSerial espSerial(RX_SOFT, TX_SOFT);

void sendDataToESP32() {
  Serial.println("Mengirim Data Ke ESP32");

  // Data format: pH,temp,turbidity,level
  String data = String(waterPH) + "," + String(waterTemp) + "," + String(turbidity) + "," + String(waterLevelCM);

  // Simple checksum: jumlah karakter
  int checksum = 0;
  for (char c : data) checksum += c;

  data += "," + String(checksum);  // Append checksum
  espSerial.println(data);
}
