#ifndef MY_LED_H
#define MY_LED_H

#include "Settings.h"
#include <FastLED.h>

#define LED_DATA_PIN 13
#define LED_CLOCK_PIN 14

#define LED_LOADING_IDX_SIZE 3

#define LED_LOADING_START_COLOR CRGB::Red
#define LED_LOADING_WEBADMIN_COLOR CRGB::Blue
#define LED_LOADING_NETWORK_NOK_COLOR CRGB::Purple
#define LED_LOADING_NETWORK_OK_COLOR CRGB::Green
#define LED_LOADING_NETWORK_OK_DELAY 2000

class Led {
  private:
    CRGB leds[SETTINGS_LED_COUNT];
    uint8_t loadingIdx;
    bool loading;
    bool nextLoading;
    uint32_t nextLoadingWhen;
    CRGB loadingColor;

	public:
    Led();
    void begin();
    void applySettings();
    void error();
    void effects();
    void setLoadingColor(CRGB);
    void setLoading(bool);
    void setDelayedLoading(bool, uint16_t);
    void setColorCorrection(uint32_t);
};

extern Led led;

#endif