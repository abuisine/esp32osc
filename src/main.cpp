/* enable Ethernet power supply with correct clock */
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12

#include <Arduino.h>
#include <ETH.h>
#include <FastLED.h>
#include "Settings.h"
#include "Network.h"
#include "Webadmin.h"

#define BUTTON_PRESSED()  (!digitalRead (34))
#define DATA_PIN 13
#define CLOCK_PIN 14

CRGB leds[SETTINGS_LED_COUNT];

void setup()
{
  Serial.begin(115200);
  Serial.println("Esp32osc starting ...");

  settings.restore();
  Serial.print(settings);

  pinMode (34, INPUT);  // Button
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, SETTINGS_LED_COUNT);

  NET.begin(settings.inPort);
  webadmin.begin();

  leds[0] = CRGB::Blue;
  leds[0].subtractFromRGB(210);
  FastLED.show();
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
    for (uint8_t i = 0; i < SETTINGS_LED_COUNT; i++) {
      leds[i] = settings.ledColor[i];
    }
    FastLED.show();

    while (BUTTON_PRESSED());
  }

  delay(2000);
}
