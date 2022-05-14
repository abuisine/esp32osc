#ifndef MY_LED_H
#define MY_LED_H

#include "Settings.h"
#include <FastLED.h>

#define LED_DATA_PIN 13
#define LED_CLOCK_PIN 14

class Led {
  private:
    CRGB leds[SETTINGS_LED_COUNT];
    uint8_t stage;

	public:
    Led();
    void begin();
    void applySettings();
    void bumpStage();
    void error();
};

extern Led led;

#endif