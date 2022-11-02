/*
  Tempo de amostragem de sinal = 10 segundos
  f = 62,5
  T = 16ms
  10 segundos = 6250 amostas
  *Send long data with POST
  https://github.com/me-no-dev/ESPAsyncWebServer/issues/337
*/
#include <Arduino.h>
#include "sensor.h"
#include "comunicacao.h"

#define BUFFER  3000

unsigned long previousMillis = 0;
unsigned long secoundMillis = 0;
boolean CONTIN = true;

void setup() {
  Serial.begin(115200);
  // Wifi defination
  // Wifi_t wificonfig = {
  //   .ssid     = "Rep. Uteiro",
  //   .password = "naotemsenha",
  //   .hostname = "JEAN"
  // };
  // InicializaWifi(&wificonfig);

  Init_ADXL345();
  Serial.print("Initialized finish... \n");
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(CONTIN)
  {
    CONTIN = false;
    // char* msg = (char*)malloc(BUFFER);
    Sample(BUFFER);
    // free(msg);
    Serial.print("Finish\n");
  }

  if ((unsigned long)(currentMillis - previousMillis) >= 5000) // entra a cada 5 segundo
  {
     CONTIN = true;
     previousMillis = currentMillis;
  }
}