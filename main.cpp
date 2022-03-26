/* enable Ethernet power supply with correct clock */
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12

#include <Arduino.h>
#include <ETH.h>
#include "Settings.h"
#include "Network.h"
#include "Webadmin.h"

#define BUTTON_PRESSED()  (!digitalRead (34))

void setup()
{
  Serial.begin(115200);
  Serial.println("Esp32osc starting ...");

  settings.restore();
  Serial.print(settings);

  pinMode (34, INPUT);  // Button

  NET.begin(settings.inPort);
  webadmin.begin();
}

void loop()
{
  Serial.println("I am alive !");
  if (BUTTON_PRESSED())
  {
    // Serial.println("ETH Status:");
    // Serial.println(ETH.linkUp());

    if (!NET.isReady()) {
      Serial.println("(E) network not ready");
    }

    // OSCMessage msg(dstPath);
    // msg.add(64);
    // network.udp.beginPacket(settings.outHost, settings.outPort);
    // msg.send(network.udp); // send the bytes to the SLIP stream
    // network.udp.endPacket();
    // msg.empty();

    while (BUTTON_PRESSED());
  }

  delay(2000);
}
