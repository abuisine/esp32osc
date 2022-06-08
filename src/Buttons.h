#ifndef MY_BUTTONS_H
#define MY_BUTTONS_H

#include <Arduino.h>

#define BUTTONS_0_PIN 15
#define BUTTONS_1_PIN 16
#define BUTTONS_2_PIN 32
#define BUTTONS_3_PIN 33
#define BUTTONS_4_PIN 34
#define BUTTONS_5_PIN 36

#define BUTTONS_0_PIN_MODE INPUT_PULLUP
#define BUTTONS_1_PIN_MODE INPUT_PULLUP
#define BUTTONS_2_PIN_MODE INPUT_PULLUP
#define BUTTONS_3_PIN_MODE INPUT_PULLUP
#define BUTTONS_4_PIN_MODE INPUT
#define BUTTONS_5_PIN_MODE INPUT_PULLUP


class Buttons {
  public:
    volatile bool button0Pressed;
    volatile bool button1Pressed;
    volatile bool button2Pressed;
    volatile bool button3Pressed;
    volatile bool button4Pressed;
    volatile bool button5Pressed;

    volatile uint32_t button0LastPress;
    volatile uint32_t button1LastPress;
    volatile uint32_t button2LastPress;
    volatile uint32_t button3LastPress;
    volatile uint32_t button4LastPress;
    volatile uint32_t button5LastPress;

    Buttons();
    void begin();
};

extern Buttons BUTTONS;

#endif