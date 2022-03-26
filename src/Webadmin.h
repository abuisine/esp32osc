#ifndef MY_WEBADMIN_H
#define MY_WEBADMIN_H

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Settings.h"

#define WEBADMIN_HTTP_PORT 80

class Webadmin {
  private:
    AsyncWebServer server;

    static String processor(const String &);

  public:
    Webadmin();

    void begin();
};

extern Webadmin webadmin;

#endif