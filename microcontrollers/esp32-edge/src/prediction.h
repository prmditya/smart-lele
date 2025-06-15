#pragma once

#include "./model/smartLeleModel.h"
#include <./lib/tflm_esp32.h>
#include <eloquent_tinyml.h>
#include "utils.h"

#define ARENA_SIZE 10000

// Standardization constants
#define PH_MEAN 7.500265
#define PH_STD 0.706338 	
#define TEMP_MEAN 24.228911
#define TEMP_STD 4.592424
#define TURB_MEAN 5.122034
#define TURB_STD 2.561515 	

Eloquent::TF::Sequential<TF_NUM_OPS + 3, ARENA_SIZE> tf;

void initModel() {
  // Register model layers (adjust if model has more layers)
  tf.resolver.AddRelu();
  tf.resolver.AddLogistic();

  // Load model with retries (limit attempts)
  uint8_t attempts = 0;
  while (!tf.begin(smartLeleModel).isOk() && attempts < 5) {
    Serial.println("Model load failed: " + tf.exception.toString());
    delay(1000);
    attempts++;
  }
  if (attempts >= 5) {
    Serial.println("Failed to load model after 5 attempts.");
    while (true)
      ;  // Halt if model won't load
  }
  Serial.println("Model loaded successfully!");
}

float standardize(float x, float mean, float std) {
  return (x - mean) / std;
}

void makePrediction() {
  if (!Serial2.available()) return;
  if (!newDataAvailable) return;

  float input[3] = {
    standardize(lastPh, PH_MEAN, PH_STD),
    standardize(lastTemp, TEMP_MEAN, TEMP_STD),
    standardize(lastTurbidity, TURB_MEAN, TURB_STD)
  };

  float startTime = micros();

  if (!tf.predict(input).isOk()) {
    Serial.println("Prediction error: " + tf.exception.toString());
    return;
  }

  float result = tf.output(0);
  predictionResult = (result > 0.5) ? 1 : 0;

  float timeToPredict = micros() - startTime;

  Serial.println("\n-------- Prediction Debugging --------"); // Tambah newline untuk kejelasan
  Serial.print("Input (PH, Temp, Turb): ");
  Serial.print(lastPh);
  Serial.print(", ");
  Serial.print(lastTemp);
  Serial.print(", ");
  Serial.println(lastTurbidity);
  Serial.print("Time Elapsed for Prediction: ");
  Serial.print(timeToPredict);
  Serial.println(" μs"); // Jelas menyatakan satuan mikros detik
  Serial.print("Raw Probability: ");
  Serial.println(result, 4); // Cetak probabilitas dengan 4 desimal
  Serial.print("Stable Predicted Class: ");
  Serial.println(predictionResult);
  Serial.println("--------------------------------------\n");

  String dataLoad = "<" + String(predictionResult) + ">";
  Serial2.println(dataLoad);
}