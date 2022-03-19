#ifndef ESP32OSC_H
#define ESP32OSC_H

#include <Arduino.h>
#include <OSCMessage.h>
#include "Settings.h"

#define ESP32OSC_DST_PATH_LENGTH 32

class Esp32osc {
  private:
    char dstPath[ESP32OSC_DST_PATH_LENGTH];
    Settings *settings;
  public:
    Esp32osc(Settings &);
    void sendButtonEvent(uint8_t);
};

#endif