#pragma once

#define RX_SOFT 10
#define TX_SOFT 11
#define PH_SENSOR_PIN A0
#define TEMP_SENSOR_PIN 4
#define TURBIDITY_SENSOR_PIN A1
#define PUMP_DRAIN_PIN 6
#define PUMP_FILL_PIN 7
#define ULTRASONIC_TRIG_PIN 8
#define ULTRASONIC_ECHO_PIN 9

const float PH7_VOLTAGE = 3.1;
const float PH918_VOLTAGE = 2.4;

extern float waterTemp = 0, waterPH = 0, turbidity = 0, waterLevelCM = 0;