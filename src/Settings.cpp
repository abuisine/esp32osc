#include "Settings.h"

Settings::Settings() {
}

void Settings::restore() {
  if (!prefs.begin(SETTINGS_PREFERENCES_NAMESPACE, true)) {
    Serial.println("(E) Not able to restore");
    return;
  }
  inPort = prefs.getUInt(SETTINGS_IN_PORT, SETTINGS_DEFAULT_IN_PORT);
  outPort = prefs.getUInt(SETTINGS_OUT_PORT, SETTINGS_DEFAULT_OUT_PORT);
  outHost = prefs.getULong(SETTINGS_OUT_HOST, SETTINGS_DEFAULT_OUT_HOST);
  oscAddress = prefs.getString(SETTINGS_OSC_ADDRESS, SETTINGS_DEFAULT_OSC_ADDRESS);
  ledColor[0] = prefs.getULong(SETTINGS_LED_COLOR_0, SETTINGS_DEFAULT_LED_COLOR);
  ledColor[1] = prefs.getULong(SETTINGS_LED_COLOR_1, SETTINGS_DEFAULT_LED_COLOR);
  ledColor[2] = prefs.getULong(SETTINGS_LED_COLOR_2, SETTINGS_DEFAULT_LED_COLOR);
  ledColor[3] = prefs.getULong(SETTINGS_LED_COLOR_3, SETTINGS_DEFAULT_LED_COLOR);
  ledColor[4] = prefs.getULong(SETTINGS_LED_COLOR_4, SETTINGS_DEFAULT_LED_COLOR);
  ledColor[5] = prefs.getULong(SETTINGS_LED_COLOR_5, SETTINGS_DEFAULT_LED_COLOR);
  colorCorrect = prefs.getULong(SETTINGS_COLOR_CORRECT, SETTINGS_DEFAULT_COLOR_CORRECT);
  buttonDebouncingDelay = prefs.getULong(SETTINGS_BUTTON_DEBOUNCING_DELAY, SETTINGS_DEFAULT_BUTTON_DEBOUNCING_DELAY);

  prefs.end();
  Serial.println("(I) Settings restored");
}

void Settings::persist() {
  if (!prefs.begin(SETTINGS_PREFERENCES_NAMESPACE, false)) {
    Serial.println("(E) Not able to persist");
    return;
  }
  prefs.putUInt(SETTINGS_IN_PORT, inPort);
  prefs.putUInt(SETTINGS_OUT_PORT, outPort);
  prefs.putString(SETTINGS_OSC_ADDRESS, oscAddress);
  prefs.putULong(SETTINGS_OUT_HOST, outHost);
  prefs.putULong(SETTINGS_LED_COLOR_0, ledColor[0]);
  prefs.putULong(SETTINGS_LED_COLOR_1, ledColor[1]);
  prefs.putULong(SETTINGS_LED_COLOR_2, ledColor[2]);
  prefs.putULong(SETTINGS_LED_COLOR_3, ledColor[3]);
  prefs.putULong(SETTINGS_LED_COLOR_4, ledColor[4]);
  prefs.putULong(SETTINGS_LED_COLOR_5, ledColor[5]);
  prefs.putULong(SETTINGS_COLOR_CORRECT, colorCorrect);
  prefs.putULong(SETTINGS_BUTTON_DEBOUNCING_DELAY, buttonDebouncingDelay);
  prefs.end();
  Serial.println("(I) Settings persisted");
}

void Settings::clear() {
  prefs.clear();
}

size_t Settings::printTo(Print& p) const
{
    size_t n = 0;
    n += p.println("##### Settings #####");
		n += p.println((String)"inPort: " + inPort);
		n += p.println((String)"outPort: " + outPort);
		n += p.println((String)"outHost: " + outHost);
		n += p.println((String)"oscAddress: " + oscAddress);

    for (int i = 0; i < SETTINGS_LED_COUNT; i++) {
		  n += p.println((String)"ledColor: " + String(ledColor[i], 16));
    }
		n += p.println((String)"colorCorrect: " + String(colorCorrect, 16));
    n += p.println((String)"buttonDebouncingDelay: " + buttonDebouncingDelay);
		n += p.println("####################");
    return n;
}

Settings settings;