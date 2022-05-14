#include "Led.h"

Led::Led()
  : stage(0) {
}

void Led::begin() {
  FastLED.addLeds<APA102, LED_DATA_PIN, LED_CLOCK_PIN, BGR>(leds, SETTINGS_LED_COUNT);
  FastLED.clear();
  leds[0] = CRGB::Green;
  leds[0].subtractFromRGB(230);
  FastLED.show();
}

void Led::applySettings() {
  for (uint8_t i = 0; i < SETTINGS_LED_COUNT; i++) {
    leds[i] = settings.ledColor[i];
  }
  FastLED.show();
}

void Led::bumpStage() {
  leds[stage] = settings.ledColor[stage];
  FastLED.show();
  stage++;
}

void Led::error() {
  leds[0] = CRGB::Red;
  FastLED.show();
}

Led led;