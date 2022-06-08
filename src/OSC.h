#ifndef MY_OSC_H
#define MY_OSC_H

#include <Arduino.h>

#define OSC_ADDRESS_MAX_LENGTH 64

class OpenSoundControl {
  public:
    OpenSoundControl();
    void send(uint8_t buttonId);
};

extern OpenSoundControl OSC;

#endif