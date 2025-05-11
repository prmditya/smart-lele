// Target Plaftorm : Arduino UNO
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <softwareserial.h>

#include "./src/globals.h"

#include "./src/sensors.h"
#include "./src/display.h"
#include "./src/pumps.h"
#include "./src/transmitter.h"
#include "./src/receiver.h"


void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  tempSensor.begin();

  pinMode(PH_SENSOR_PIN, INPUT);
  pinMode(PUMP_DRAIN_PIN, OUTPUT);
  pinMode(PUMP_FILL_PIN, OUTPUT);
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);

  turnOffAllPumps();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Smart Lele Init ");
  delay(2000);
  lcd.clear();
}

void loop() {
  readSensors();
  printSensorData();
  sendDataToESP32();
  readDataFromESP32();
  delay(2000);
}
