#pragma once

void readDataFromESP32() {
  // Beri sedikit waktu untuk SoftwareSerial mengumpulkan semua byte.
  delay(50);

  if (espSerial.available()) {
    // Baca seluruh string hingga karakter newline '\n'
    String receivedString = espSerial.readStringUntil('\n');
    receivedString.trim(); // Hapus spasi di awal/akhir

    Serial.print("Received raw from ESP32: '");
    Serial.print(receivedString);
    Serial.println("'");

    // Periksa apakah string memiliki format yang diharapkan: dimulai dengan '<' dan diakhiri dengan '>'
    if (receivedString.startsWith("<") && receivedString.endsWith(">")) {
      // Ekstrak karakter di antara '<' dan '>'
      String labelCharStr = receivedString.substring(1, receivedString.length() - 1);

      // Pastikan string yang diekstrak tidak kosong dan hanya berisi satu karakter digit
      if (labelCharStr.length() == 1 && (labelCharStr.charAt(0) == '0' || labelCharStr.charAt(0) == '1')) {
        receivedLabel = labelCharStr.toInt(); // Konversi karakter '0' atau '1' menjadi integer 0 atau 1
        Serial.print("Received Label from ESP32 (parsed): ");
        Serial.println(receivedLabel);
        controlPump(receivedLabel);
      } else {
        Serial.print("Invalid label format from ESP32: '");
        Serial.print(labelCharStr);
        Serial.println("'. Expected '0' or '1'.");
        // Jika format label tidak sesuai, jangan ubah status pompa.
        // Biarkan pompa pada status terakhir atau ke mode aman.
      }
    } else {
      Serial.println("Invalid message delimiters from ESP32. Expected '<...>'");
      // Jika format pesan tidak sesuai (tidak ada < atau >), abaikan.
    }
  } else {
    Serial.println("Tidak ada data masuk dari ESP32.");
  }
}