// Target platform: ESP32
#include "./src/globals.h"

#include "./src/connection.h"
#include "./src/receiver.h"
#include "./src/prediction.h"
#include "./src/transmitter.h"

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  initModel();
  connectWiFi();
}

void loop() {
  readSensorData();
  delay(500);
  makePrediction();
  sendDataIfReady();
}
