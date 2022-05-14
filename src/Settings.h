#ifndef MY_SETTINGS_H
#define MY_SETTINGS_H

#include <Arduino.h>
#include <Print.h>
#include <IPAddress.h>
#include <Preferences.h>

#define SETTINGS_PREFERENCES_NAMESPACE "settings"

#define SETTINGS_DEFAULT_IN_PORT 9998
#define SETTINGS_DEFAULT_OUT_PORT 9999
#define SETTINGS_DEFAULT_OUT_HOST IPAddress(192, 168, 1, 28)
#define SETTINGS_DEFAULT_OSC_ADDRESS String("esp32osc")

#define SETTINGS_IN_PORT "inPort"
#define SETTINGS_OUT_PORT "outPort"
#define SETTINGS_OUT_HOST "outHost"
#define SETTINGS_OSC_ADDRESS "oscAddress"

#define SETTINGS_OUT_HOST_0 "outHost0"
#define SETTINGS_OUT_HOST_1 "outHost1"
#define SETTINGS_OUT_HOST_2 "outHost2"
#define SETTINGS_OUT_HOST_3 "outHost3"

class Settings: public Printable {
	private:
		Preferences prefs;

	public:
		uint16_t inPort;
		uint16_t outPort;
		IPAddress outHost;
		String oscAddress;

		Settings();
		void restore();
		void persist();
		virtual size_t printTo(Print& p) const;
};

extern Settings settings;

#endif