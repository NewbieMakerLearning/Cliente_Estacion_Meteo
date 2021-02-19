void InitOTA()
{
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
   ArduinoOTA.setHostname("Cliente.local");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Inicio subida de datos " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progreso: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Fallo autenticación.");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed.");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Fallo conexión.");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Fallo recepción.");
    } else if (error == OTA_END_ERROR) {
      Serial.println("Fin fallo.");
    }
  });

  ArduinoOTA.begin();
  Serial.println("");
  Serial.println("OTA iniciado");
}
