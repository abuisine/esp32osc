#include "Led.h"

Led::Led()
  : loadingIdx(0),
    loading(true),
    nextLoading(true),
    loadingColor(LED_LOADING_START_COLOR),
    nextLoadingWhen(0) {
}

void Led::begin() {
  FastLED.addLeds<APA102, LED_DATA_PIN, LED_CLOCK_PIN, BGR>(leds, SETTINGS_LED_COUNT);
  FastLED.setCorrection(settings.colorCorrect);
  FastLED.clear();
  leds[loadingIdx] = loadingColor;
  // leds[loadingIdx].subtractFromRGB(230);
  FastLED.show();
}

void Led::applySettings() {
  FastLED.setCorrection(settings.colorCorrect);
  for (uint8_t i = 0; i < SETTINGS_LED_COUNT; i++) {
    leds[i] = settings.ledColor[i];
  }
  FastLED.show();
}

void Led::error() {
  setLoadingColor(CRGB::Red);
  setLoading(true);
}

void Led::setDelayedLoading(bool newLoading, uint16_t ms) {
  effects();
  nextLoading = newLoading;
  nextLoadingWhen = micros() / 1000 + ms;
}

void Led::setLoading(bool newLoading) {
  effects();
  loading = newLoading;
  if (!loading)
    applySettings();
}

void Led::effects() {
  if (nextLoadingWhen != 0 && nextLoadingWhen * 1000 < micros()) {
    loading = nextLoading;
    if (!loading)
      applySettings();
    nextLoadingWhen = 0;
  }
  if (!loading)
    return;
  FastLED.clear();
  leds[loadingIdx] = loadingColor;
  // uint8_t lateIdx1 = (loadingIdx + LED_LOADING_IDX_SIZE - 1) % LED_LOADING_IDX_SIZE;
  // leds[lateIdx1] = CRGB::Red;
  // leds[lateIdx1].subtractFromRGB(235);
  // uint8_t lateIdx2 = (loadingIdx + LED_LOADING_IDX_SIZE - 2) % LED_LOADING_IDX_SIZE;
  // leds[lateIdx2] = CRGB::Black;

  FastLED.show();
  loadingIdx = (loadingIdx + 1) % SETTINGS_LED_COUNT;
}

void Led::setLoadingColor(CRGB color) {
  loadingColor = color;
}

Led led;