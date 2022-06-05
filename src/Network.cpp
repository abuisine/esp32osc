#include <ETH.h>
#include <WiFiType.h>
#include <IPAddress.h>
#include "Network.h"
#include "Led.h"

void onEvent(WiFiEvent_t event) {
  IPAddress ip;
  switch (event) {
    case ARDUINO_EVENT_ETH_START:
      Serial.println("(I) Setting hostname");
      ETH.setHostname("esp32osc");
      break;
    case ARDUINO_EVENT_ETH_CONNECTED:
      break;
    case ARDUINO_EVENT_ETH_GOT_IP:
      ip = ETH.localIP();
      NET.udp.begin(ip, NET.getUdpListeningPort());
      NET.setReady();
      Serial.println((String)"(I) Network is now ready with IP : " + ip.toString());
      led.bumpStage();
      break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
      Serial.println("(I) Network is now disconnected");
      NET.setReady(false);
      led.error();
      break;
    case ARDUINO_EVENT_ETH_STOP:
      NET.setReady(false);
      break;
    default:
      Serial.println((String)"Unknown network event: " + event);
      break;
  }
}

Network::Network()
  : ready(false),udpListeningPort(0) {
}

void Network::begin(uint16_t udpListeningPort) {
  udpListeningPort = udpListeningPort;
  Serial.println("(I) Network start ...");
  WiFi.onEvent(onEvent);
  ETH.begin();
  led.bumpStage();
}

uint16_t Network::getUdpListeningPort() {
  return udpListeningPort;
}

bool Network::isReady() {
  return ready;
}

void Network::setReady(bool newReady) {
  ready = newReady;
}

IPAddress Network::getIP() {
  return ETH.localIP();
}

Network NET;