#pragma once

LiquidCrystal_I2C lcd(0x27, 16, 2);

void printSensorData() {
  Serial.print("Temp: ");
  Serial.print(waterTemp);
  Serial.print(" °C | pH: ");
  Serial.print(waterPH);
  Serial.print(" | Turbidity: ");
  Serial.print(turbidity);
  Serial.print(" NTU | Water Level: ");
  Serial.print(waterLevelCM);
  Serial.println(" cm");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH:");
  lcd.print(waterPH, 1);
  lcd.print(" T:");
  lcd.print(waterTemp, 1);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("NTU:");
  lcd.print(turbidity, 0);
  lcd.print(" WL:");
  lcd.print(waterLevelCM, 0);
  lcd.print("cm");
  delay(2000);
}

void waterQualityAlert() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kualitas Air");
  lcd.setCursor(0, 1);
  lcd.print("Tidak baik");
  delay(2000);
}