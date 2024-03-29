/* enable Ethernet power supply with correct clock */
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12

#include <Arduino.h>
#include <ETH.h>
#include <WebSerialPro.h>
// #include <ArduinoOTA.h>
#include "version.h"
#include "Led.h"
#include "Settings.h"
#include "Network.h"
#include "Webadmin.h"
#include "OSC.h"
#include "Buttons.h"

void setup()
{
  Serial.begin(115200);
  Serial.println((String)"Esp32osc v" + VERSION + " starting ...");

  settings.restore();
  Serial.print(settings);

  led.begin();

  NET.begin(settings.inPort);
  webadmin.begin();
  BUTTONS.begin();
}

uint8_t   loopIdx = 0;
uint16_t  loopDelay = 100;
uint16_t  loopDebugOffset = 100;
void loop()
{
  if (loopIdx % loopDebugOffset == 0)
  {
    Serial.println((String)"I am alive, " + micros());
    WebSerialPro.println((String)"I am alive, " + micros());

    if (!NET.isReady()) {
      Serial.println("(E) network not ready");
    } else {
      Serial.println((String)"(I) local IP: " + NET.getIP().toString());
    }

    // Serial.println((String)"Free mem: " + xPortGetFreeHeapSize());
    Serial.println((String)"Buttons: "
      + BUTTONS.button0LastPress + ", "
      + BUTTONS.button1LastPress + ", "
      + BUTTONS.button2LastPress + ", "
      + BUTTONS.button3LastPress + ", "
      + BUTTONS.button4LastPress + ", "
      + BUTTONS.button5LastPress
      );
  }

  if (BUTTONS.button0Pressed) {
    BUTTONS.button0Pressed = false;
    OSC.send(1);
  }

  if (BUTTONS.button1Pressed) {
    BUTTONS.button1Pressed = false;
    OSC.send(1);
  }

  if (BUTTONS.button2Pressed) {
    BUTTONS.button2Pressed = false;
    OSC.send(2);
  }

  if (BUTTONS.button3Pressed) {
    BUTTONS.button3Pressed = false;
    OSC.send(3);
  }

  if (BUTTONS.button4Pressed) {
    BUTTONS.button4Pressed = false;
    OSC.send(4);
  }

  if (BUTTONS.button5Pressed) {
    BUTTONS.button5Pressed = false;
    OSC.send(5);
  }

  led.effects();
  delay(loopDelay);
  loopIdx++;
}
