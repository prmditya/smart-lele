#pragma once

void fillAndDrainPumpOn() {
  digitalWrite(PUMP_DRAIN_PIN, HIGH);
  digitalWrite(PUMP_FILL_PIN, HIGH);
}

void turnOffAllPumps() {
  digitalWrite(PUMP_DRAIN_PIN, LOW);
  digitalWrite(PUMP_FILL_PIN, LOW);
}

void controlPump(int prediction) {
  if (prediction) {
    Serial.println("POMPA MATI");
    turnOffAllPumps();
  } else {
    Serial.println("POMPA HIDUP");
    fillAndDrainPumpOn();
  }
}