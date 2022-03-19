#include "Esp32osc.h"
#include "Settings.h"

Esp32osc::Esp32osc(Settings &settings) {
  settings = settings;
  String StrDstPath("/");
  StrDstPath.concat(settings.oscAddress);
  StrDstPath.toCharArray(dstPath, ESP32OSC_DST_PATH_LENGTH);
}

void Esp32osc::sendButtonEvent(uint8_t buttonId) {
  OSCMessage msg(dstPath);

  msg.add(64);
  // udp.beginPacket(settings.outIp, settings.outPort);
  // msg.send(udp); // send the bytes to the SLIP stream
  // udp.endPacket();
  msg.empty();
}

