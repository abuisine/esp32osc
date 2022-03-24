#include <ETH.h>
#include "Network.h"

Network::Network() {
  ready = false;
  listeningPort = 0;
  // WiFi.onEvent(onEvent);
}

void Network::setListeningPort(uint16_t _listeningPort) {
  listeningPort = _listeningPort;
}

bool Network::isReady() {
  return ready;
}

bool Network::begin() {
  return ETH.begin();
}

// void Network::onEvent(WiFiEvent_t event)
// {
//   switch (event) {
//     case SYSTEM_EVENT_ETH_START:
//       //set eth hostname here
//       ETH.setHostname("esp32osc");
//       break;
//     case SYSTEM_EVENT_ETH_CONNECTED:
//       break;
//     case SYSTEM_EVENT_ETH_GOT_IP:
//       ready = true;
//       udp.begin(WiFi.localIP(), listeningPort);
//       break;
//     case SYSTEM_EVENT_ETH_DISCONNECTED:
//       ready = false;
//       break;
//     case SYSTEM_EVENT_ETH_STOP:
//       ready = false;
//       break;
//     default:
//       break;
//   }
// }