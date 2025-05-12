#pragma once

#define THRESHOLD_TEMP 0.5
#define THRESHOLD_PH 0.2
#define THRESHOLD_TURBIDITY 5
#define THRESHOLD_WATERLEVEL 2

OneWire oneWire(TEMP_SENSOR_PIN);
DallasTemperature tempSensor(&oneWire);

float readPH() {
  int analogValue = analogRead(PH_SENSOR_PIN);
  float voltage = analogValue * (5.0 / 1023.0);
  float slope = (9.18 - 7.0) / (PH918_VOLTAGE - PH7_VOLTAGE);
  return 7.0 + slope * (voltage - PH7_VOLTAGE);
}

float readTurbidity() {
  const int NUM_SAMPLES = 10;
  int total = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    total += analogRead(TURBIDITY_SENSOR_PIN);
    delay(10);
  }

  int avg = total / NUM_SAMPLES;
  int cleanADC = 450;
  int dirtyADC = 200;
  float turbidityNTU = map(avg, cleanADC, dirtyADC, 0, 2000);
  float result = constrain(0, 2000);
  if (result < 0)
    return 0;

  return result;
}

float readWaterLevel() {
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

  long duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, 30000);
  return duration * 0.034 / 2;
}

void readSensors() {
  float temp1, temp2;
  float ph1, ph2;
  float turb1, turb2;
  float level1, level2;

  // Baca pertama
  tempSensor.requestTemperatures();
  temp1 = tempSensor.getTempCByIndex(0);
  ph1 = readPH();
  turb1 = readTurbidity();
  level1 = readWaterLevel();

  delay(100);  // jeda pendek sebelum baca ulang

  // Baca kedua
  tempSensor.requestTemperatures();
  temp2 = tempSensor.getTempCByIndex(0);
  ph2 = readPH();
  turb2 = readTurbidity();
  level2 = readWaterLevel();

  // Bandingkan dan ambil nilai rata-rata jika perbedaan wajar
  waterTemp = abs(temp1 - temp2) < THRESHOLD_TEMP ? (temp1 + temp2) / 2 : -1;
  waterPH = abs(ph1 - ph2) < THRESHOLD_PH ? (ph1 + ph2) / 2 : -1;
  turbidity = abs(turb1 - turb2) < THRESHOLD_TURBIDITY ? (turb1 + turb2) / 2 : -1;
  waterLevelCM = abs(level1 - level2) < THRESHOLD_WATERLEVEL ? (level1 + level2) / 2 : -1;
}