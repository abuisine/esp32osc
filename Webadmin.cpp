#include <ETH.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Webadmin.h"


String Webadmin::processor(const String &var)
{
  if(var == "MAC_ADDRESS")
    return ETH.macAddress();
  if(var == "IPV4")
    return ETH.localIP().toString();
  if(var == "LINK_SPEED")
    return String(ETH.linkSpeed());
  if(var == "IN_PORT")
    return String(settings.inPort); 
  if(var == "OUT_PORT")
    return String(settings.outPort);
  if(var == "OUT_HOST_0")
    return String(settings.outHost[0]);
  if(var == "OUT_HOST_1")
    return String(settings.outHost[1]);
  if(var == "OUT_HOST_2")
    return String(settings.outHost[2]);
  if(var == "OUT_HOST_3")
    return String(settings.outHost[3]);
  if(var == "OSC_ADDRESS")
    return settings.oscAddress;
  return String();
}

Webadmin::Webadmin()
  : server(WEBADMIN_HTTP_PORT) {
  }

void Webadmin::begin() {
  if(!SPIFFS.begin(true)){
    Serial.println("(E) Not able to mount SPIFFS");
    return;
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.print("POST request received with parameters: ");
    Serial.println(request->params());
    if(request->hasParam(SETTINGS_IN_PORT, true)) {
      AsyncWebParameter* p  = request->getParam(SETTINGS_IN_PORT, true);
      settings.inPort = p->value().toInt();
    }
    if(request->hasParam(SETTINGS_OUT_PORT, true)) {
      AsyncWebParameter* p  = request->getParam(SETTINGS_OUT_PORT, true);
      settings.outPort = p->value().toInt();
    }
    if(request->hasParam(SETTINGS_OSC_ADDRESS, true)) {
      AsyncWebParameter* p  = request->getParam(SETTINGS_OSC_ADDRESS, true);
      settings.oscAddress = p->value().substring(0, 32);
    }
    if(request->hasParam(SETTINGS_OUT_HOST_0, true)
      && request->hasParam(SETTINGS_OUT_HOST_1, true)
      && request->hasParam(SETTINGS_OUT_HOST_2, true)
      && request->hasParam(SETTINGS_OUT_HOST_3, true)) {
      AsyncWebParameter* p0 = request->getParam(SETTINGS_OUT_HOST_0, true);
      AsyncWebParameter* p1 = request->getParam(SETTINGS_OUT_HOST_1, true);
      AsyncWebParameter* p2 = request->getParam(SETTINGS_OUT_HOST_2, true);
      AsyncWebParameter* p3 = request->getParam(SETTINGS_OUT_HOST_3, true);
      settings.outHost = IPAddress(
        p0->value().toInt(),
        p1->value().toInt(),
        p2->value().toInt(),
        p3->value().toInt());
    }
    settings.persist();
    request->send(200);
  });

  server.begin();
  Serial.println("(I) Webserver started");
}

Webadmin webadmin;