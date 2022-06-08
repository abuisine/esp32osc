#include <OSCMessage.h>
#include "Settings.h"
#include "Network.h"
#include "OSC.h"

OpenSoundControl::OpenSoundControl() {
}

void OpenSoundControl::send(uint8_t buttonId) {
  String path = "/" + settings.oscAddress + "/" + buttonId;
  char address[OSC_ADDRESS_MAX_LENGTH];
  path.toCharArray(address, OSC_ADDRESS_MAX_LENGTH);

  OSCMessage msg(address);
  msg.add(true);
  NET.udp.beginPacket(settings.outHost, settings.outPort);
  msg.send(NET.udp); // send the bytes to the SLIP stream
  NET.udp.endPacket();
  msg.empty();
}

OpenSoundControl OSC;