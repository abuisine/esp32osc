#include "Buttons.h"
#include "Settings.h"

void IRAM_ATTR isr0() {
  if (micros() - BUTTONS.button0LastPress > settings.buttonDebouncingDelay * 1000) {
    BUTTONS.button0Pressed = true;
    BUTTONS.button0LastPress = micros();
  }
}

void IRAM_ATTR isr1() {
  if (micros() - BUTTONS.button1LastPress > settings.buttonDebouncingDelay * 1000) {
    BUTTONS.button1Pressed = true;
    BUTTONS.button1LastPress = micros();
  }
}

void IRAM_ATTR isr2() {
  if (micros() - BUTTONS.button2LastPress > settings.buttonDebouncingDelay * 1000) {
    BUTTONS.button2Pressed = true;
    BUTTONS.button2LastPress = micros();
  }
}

void IRAM_ATTR isr3() {
  if (micros() - BUTTONS.button3LastPress > settings.buttonDebouncingDelay * 1000) {
    BUTTONS.button3Pressed = true;
    BUTTONS.button3LastPress = micros();
  }
}

void IRAM_ATTR isr4() {
  if (micros() - BUTTONS.button4LastPress > settings.buttonDebouncingDelay * 1000) {
    BUTTONS.button4Pressed = true;
    BUTTONS.button4LastPress = micros();
  }
}

void IRAM_ATTR isr5() {
  if (micros() - BUTTONS.button5LastPress > settings.buttonDebouncingDelay * 1000) {
    BUTTONS.button5Pressed = true;
    BUTTONS.button5LastPress = micros();
  }
}

Buttons::Buttons() 
  : button0Pressed(false),
    button1Pressed(false),
    button2Pressed(false),
    button3Pressed(false),
    button4Pressed(false),
    button5Pressed(false),
    button0LastPress(0),
    button1LastPress(1),
    button2LastPress(2),
    button3LastPress(3),
    button4LastPress(4),
    button5LastPress(5)
{
}

void Buttons::begin() {
  pinMode(BUTTONS_0_PIN, BUTTONS_0_PIN_MODE);
  pinMode(BUTTONS_1_PIN, BUTTONS_1_PIN_MODE);
  pinMode(BUTTONS_2_PIN, BUTTONS_2_PIN_MODE);
  pinMode(BUTTONS_3_PIN, BUTTONS_3_PIN_MODE);
  pinMode(BUTTONS_4_PIN, BUTTONS_4_PIN_MODE);
  pinMode(BUTTONS_5_PIN, BUTTONS_5_PIN_MODE);

  attachInterrupt(BUTTONS_0_PIN, isr0, FALLING);
  attachInterrupt(BUTTONS_1_PIN, isr1, FALLING);
  attachInterrupt(BUTTONS_2_PIN, isr2, FALLING);
  attachInterrupt(BUTTONS_3_PIN, isr3, FALLING);
  attachInterrupt(BUTTONS_4_PIN, isr4, FALLING);
  attachInterrupt(BUTTONS_5_PIN, isr5, FALLING);
}

Buttons BUTTONS;