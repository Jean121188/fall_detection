/*
  Tempo de amostragem de sinal = 10 segundos
  f = 62,5
  T = 16ms
  10 segundos = 6250 amostas
  *Send long data with POST
  https://github.com/me-no-dev/ESPAsyncWebServer/issues/337

  Listas
  A ideia é boa mas a amostragem é muito rápida
*/
#include <Arduino.h>
#include "sensor.h"
#include "comunicacao.h"
#include "List.hpp"

#define BUFFER  3000

unsigned long previousMillis = 0;
unsigned long secoundMillis = 0;
boolean contne = true, contprint = false;
List<String> results;
int* pDados = (int*)malloc(BUFFER_SIZE);

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
  
  if(contne)
  {
    contne = false;
    pDados = Sample(BUFFER);
    contprint = true;
  }

  if(contprint){
    contprint = false;
    //results = PrintDados(pDados);
    Serial.printf("Size of results: %i\n", sizeof(results));
    contne = true;
    free(pDados);
  }
    
}