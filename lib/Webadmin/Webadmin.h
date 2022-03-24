#ifndef MY_WEBADMIN_H
#define MY_WEBADMIN_H

#define WEBADMIN_HTTP_PORT 80

#include <Arduino.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Settings.h"

class Webadmin {
  private:
    Settings &settings;
    AsyncWebServer server;

    String processor(const String &);
  public:
    Webadmin(Settings &);
};

#endif