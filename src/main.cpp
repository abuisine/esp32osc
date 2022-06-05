/* enable Ethernet power supply with correct clock */
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12

#include <Arduino.h>
#include <ETH.h>
#include "Led.h"
#include "Settings.h"
#include "Network.h"
#include "Webadmin.h"

uint32_t debouncingDelay = 50000; // 50ms

struct Button {
  uint8_t   pin;
  bool      pressed;
  uint32_t  lastPress; 
};

volatile struct Button button0 = {15, false, 0};
volatile struct Button button1 = {16, false, 0};
volatile struct Button button2 = {32, false, 0};
volatile struct Button button3 = {33, false, 0};
volatile struct Button button4 = {34, false, 0};
volatile struct Button button5 = {36, false, 0};

void IRAM_ATTR isr0() {
  if (micros() - button0.lastPress > debouncingDelay) {
    button0.pressed = true;
    button0.lastPress = micros();
  }
}

void IRAM_ATTR isr1() {
  if (micros() - button0.lastPress > debouncingDelay) {
    button1.pressed = true;
    button1.lastPress = micros();
  }
}

void IRAM_ATTR isr2() {
  if (micros() - button0.lastPress > debouncingDelay) {
    button2.pressed = true;
    button2.lastPress = micros();
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Esp32osc starting ...");

  settings.restore();
  Serial.print(settings);

  led.begin();

  pinMode(button0.pin, INPUT_PULLUP);
  pinMode(button1.pin, INPUT_PULLUP);
  pinMode(button2.pin, INPUT_PULLUP);
  pinMode(button3.pin, INPUT_PULLUP);
  pinMode(button4.pin, INPUT);
  pinMode(button5.pin, INPUT_PULLUP);

  attachInterrupt(button0.pin, isr0, FALLING);
  attachInterrupt(button1.pin, isr1, FALLING);
  attachInterrupt(button2.pin, isr2, FALLING);
  attachInterrupt(button3.pin, isr0, FALLING);
  attachInterrupt(button4.pin, isr1, FALLING);
  attachInterrupt(button5.pin, isr2, FALLING);

  NET.begin(settings.inPort);
  webadmin.begin();
}

void loop()
{
  Serial.println("I am alive !");
  Serial.println((String)"Button #1: "+ button0.lastPress);
  Serial.println((String)"Button #2: "+ button1.lastPress);
  Serial.println((String)"Button #3: "+ button2.lastPress);
  Serial.println((String)"Button #4: "+ button3.lastPress);
  Serial.println((String)"Button #5: "+ button4.lastPress);
  Serial.println((String)"Button #6: "+ button5.lastPress);

  if (button0.pressed)
  {
    button0.pressed = false;
    if (!NET.isReady()) {
      Serial.println("(E) network not ready");
    } else {
      Serial.println((String)"(I) local IP: " + NET.getIP().toString());
    }
  }

  if (button1.pressed) {
    button1.pressed = false;

    // OSCMessage msg(dstPath);
    // msg.add(64);
    // network.udp.beginPacket(settings.outHost, settings.outPort);
    // msg.send(network.udp); // send the bytes to the SLIP stream
    // network.udp.endPacket();
    // msg.empty();
    led.applySettings();
    Serial.println("Led settings applied !");
  }

  delay(2000);
}
