/* enable Ethernet power supply with correct clock */
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12

#include <Arduino.h>
#include <ETH.h>
#include <OSCMessage.h>
#include "Led.h"
#include "Settings.h"
#include "Network.h"
#include "Webadmin.h"

uint32_t debouncingDelay = 50000; // 50ms

struct button {
  uint8_t   pin;
  bool      pressed;
  uint32_t  lastPress; 
};

volatile struct button buttons[6] = {
  {15, false, 0},
  {16, false, 0},
  {32, false, 0},
  {33, false, 0},
  {34, false, 0},
  {36, false, 0}
  };

void IRAM_ATTR isr0() {
  if (micros() - buttons[0].lastPress > debouncingDelay) {
    buttons[0].pressed = true;
    buttons[0].lastPress = micros();
  }
}

void IRAM_ATTR isr1() {
  if (micros() - buttons[0].lastPress > debouncingDelay) {
    buttons[1].pressed = true;
    buttons[1].lastPress = micros();
  }
}

void IRAM_ATTR isr2() {
  if (micros() - buttons[0].lastPress > debouncingDelay) {
    buttons[2].pressed = true;
    buttons[2].lastPress = micros();
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Esp32osc starting ...");

  settings.restore();
  Serial.print(settings);

  led.begin();

  pinMode(buttons[0].pin, INPUT_PULLUP);
  pinMode(buttons[1].pin, INPUT_PULLUP);
  pinMode(buttons[2].pin, INPUT_PULLUP);
  pinMode(buttons[3].pin, INPUT_PULLUP);
  pinMode(buttons[4].pin, INPUT);
  pinMode(buttons[5].pin, INPUT_PULLUP);

  attachInterrupt(buttons[0].pin, isr0, FALLING);
  attachInterrupt(buttons[1].pin, isr1, FALLING);
  attachInterrupt(buttons[2].pin, isr2, FALLING);
  attachInterrupt(buttons[3].pin, isr0, FALLING);
  attachInterrupt(buttons[4].pin, isr1, FALLING);
  attachInterrupt(buttons[5].pin, isr2, FALLING);

  NET.begin(settings.inPort);
  webadmin.begin();
}

void loop()
{
  Serial.println("I am alive !");
  Serial.println((String)"Buttons: "
    + buttons[0].lastPress + ", "
    + buttons[1].lastPress + ", "
    + buttons[2].lastPress + ", "
    + buttons[3].lastPress + ", "
    + buttons[4].lastPress + ", "
    + buttons[5].lastPress
    );

  if (buttons[0].pressed)
  {
    buttons[0].pressed = false;
    if (!NET.isReady()) {
      Serial.println("(E) network not ready");
    } else {
      Serial.println((String)"(I) local IP: " + NET.getIP().toString());
    }
  }

  if (buttons[1].pressed) {
    buttons[1].pressed = false;
    led.applySettings();
    Serial.println("Led settings applied !");
  }

  if (buttons[2].pressed) {
    buttons[2].pressed = false;
    char address[32];
    settings.oscAddress.toCharArray(address, 32);
    OSCMessage msg(address);
    msg.add(64);
    NET.udp.beginPacket(settings.outHost, settings.outPort);
    msg.send(NET.udp); // send the bytes to the SLIP stream
    NET.udp.endPacket();
    msg.empty();
  }





  delay(1000);
}
