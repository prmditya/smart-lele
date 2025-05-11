#pragma once

void readDataFromESP32() {
  if (espSerial.available()) {
    String labelStr = espSerial.readStringUntil('\n');
    labelStr.trim();
    int receivedLabel = labelStr.toInt();
    Serial.print("Received Label from ESP32: ");
    Serial.println(receivedLabel);
    controlPump(receivedLabel);
  }
}