#pragma once

#include "./model/smartLeleModel.h"
#include <./lib/tflm_esp32.h>
#include <eloquent_tinyml.h>
#include "utils.h"

#define ARENA_SIZE 20000

// Standardization constants
#define PH_MEAN 7.500265
#define PH_STD 0.706338
#define TEMP_MEAN 24.228911
#define TEMP_STD 4.592424
#define TURB_MEAN 5.122034
#define TURB_STD 2.561515

Eloquent::TF::Sequential<TF_NUM_OPS + 1, ARENA_SIZE> tf;

void initModel() {
  tf.setNumInputs(3);
  tf.setNumOutputs(1);

  // Register model layers (adjust if model has more layers)
  tf.resolver.AddFullyConnected();
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
  if (!isInputValid()) return;

  float input[3] = {
    standardize(lastPh, PH_MEAN, PH_STD),
    standardize(lastTemp, TEMP_MEAN, TEMP_STD),
    standardize(lastTurbidity, TURB_MEAN, TURB_STD)
  };

  if (!tf.predict(input).isOk()) {
    Serial.println("Prediction error: " + tf.exception.toString());
    return;
  }

  float result = tf.output(0);
  predictionResult = (result > 0.5) ? 1 : 0;

  Serial.print("Probability: ");
  Serial.println(result);
  Serial.print("Predicted class: ");
  Serial.println(predictionResult);
  Serial2.println(predictionResult);
}