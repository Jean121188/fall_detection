#include "comunicacao.h"

WiFiClient wifi_client;
PubSubClient mqttClient(wifi_client);

void InicializaWifi(Wifi_t *wifiConnect)
{
  WiFi.disconnect();
  delay(500);
    Serial.printf("HOST: %s\n", wifiConnect->hostname);
    Serial.printf("SSID: %s\n", wifiConnect->ssid);
    Serial.printf("PASS: %s\n", wifiConnect->password);

  WiFi.mode(WIFI_STA);
  WiFi.hostname(wifiConnect->hostname);
  WiFi.begin(wifiConnect->ssid, wifiConnect->password);

  while (WiFi.status() != WL_CONNECTED)
  {
    if(WiFi.status() == WL_NO_SSID_AVAIL)break;
    if(WiFi.status() == WL_CONNECT_FAILED)break;
    delay(300);
    Serial.print("#");
  }
  Serial.print("Wifi Connected: ");Serial.println(WiFi.localIP());
}

int xMQTTConnect(xMQTTConfig_t *pConfig){
  mqttClient.connect(pConfig->id);
  mqttClient.setKeepAlive(60);
  if(!mqttClient.connected())
  {
    mqttClient.connect(pConfig->id, pConfig->user, pConfig->password);
  }
  mqttClient.setServer(pConfig->ip, pConfig->gate);
  delay(500);
  return mqttClient.state();
}

void xMQTTSend(xMQTTConfig_t *pConfig){
    mqttClient.publish(pConfig->topic, pConfig->date);
    mqttClient.endPublish();
}