#ifndef COMUNICACAO_H
#define COMUNICACAO_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "EspMQTTClient.h"

typedef struct t{
  IPAddress ip;
  const char* topic;
  int gate;
  const char* id;
  const char* user;
  const char* password;
  const char* date;
}xMQTTConfig_t;

typedef struct{
    const char* ssid;
    const char* password;
    const char* hostname;
}Wifi_t;

void InicializaWifi(Wifi_t *wifiConnect);
int xMQTTConnect(xMQTTConfig_t *pConfig);
void xMQTTSend(xMQTTConfig_t *pSend);

#endif