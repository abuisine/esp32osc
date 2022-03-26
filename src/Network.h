#ifndef MY_NETWORK_H
#define MY_NETWORK_H

#include <Arduino.h>
#include <WiFiUdp.h>

class Network {
  private:
    bool ready;
    uint16_t udpListeningPort;

  public:
    WiFiUDP udp;

    Network();
    void begin(uint16_t udpListeningPort);
    uint16_t getUdpListeningPort();
    bool isReady();
    void setReady(bool newReady = true);
};

extern Network NET;

#endif