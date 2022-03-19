#include "Settings.h"

Settings::Settings() {
  prefs.begin(SETTINGS_PREFERENCES_NAMESPACE, true);
  inPort = prefs.getUInt(SETTINGS_IN_PORT, SETTINGS_DEFAULT_IN_PORT);
  outPort = prefs.getUInt(SETTINGS_OUT_PORT, SETTINGS_DEFAULT_OUT_PORT);
  outHost = prefs.getULong(SETTINGS_OUT_HOST, SETTINGS_DEFAULT_OUT_HOST);
  oscAddress = prefs.getString(SETTINGS_OSC_ADDRESS, SETTINGS_DEFAULT_OSC_ADDRESS);
  prefs.end();
}

size_t Settings::printTo(Print& p) const
{
    size_t n = 0;
    n += p.println("##### Settings #####");
		n += p.print("inPort: ");
		n += p.println(inPort);
		n += p.print("outPort: ");
		n += p.println(outPort);
		n += p.print("outHost: ");
		n += p.println(outHost);
		n += p.print("oscAddress: ");
		n += p.println(oscAddress);
		n += p.println("####################");
    return n;
}