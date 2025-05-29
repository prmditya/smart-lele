#pragma once

void fillAndDrainPumpOn() {
  digitalWrite(PUMP_DRAIN_PIN, LOW);
  digitalWrite(PUMP_FILL_PIN, LOW);
}

void turnOffAllPumps() {
  digitalWrite(PUMP_DRAIN_PIN, HIGH);
  digitalWrite(PUMP_FILL_PIN, HIGH);
}

void controlPump(int prediction) {
  if (prediction) {
    Serial.println("POMPA MATI");
    turnOffAllPumps();
  } else {
    waterQualityAlert();
    Serial.println("POMPA HIDUP");
    fillAndDrainPumpOn();
  }
}