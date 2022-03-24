#ifndef MY_NETWORK_H
#define MY_NETWORK_H

#include <ETH.h>

class Network {
  private:
    bool ready;
    uint16_t listeningPort;
  public:
    WiFiUDP udp;
    // void onEvent(WiFiEvent_t);

    bool isReady();
    bool begin();
    void setListeningPort(uint16_t);
    Network();
};

#endif