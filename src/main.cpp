#include "debouncer.h"
#include "bsp.h"
#include <Arduino.h>
#include <IntervalTimer.h>

#define BUTTON_PIN1 2
#define BUTTON_PIN2 8

char state_str[][50] = {"Unknown state", "Pressed", "Released", "Falling", "Rising"};

static IntervalTimer timer;
void setup()
{
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  debouncer_init(BUTTON_PIN1);
  debouncer_init(BUTTON_PIN2);
  timer.begin(debouncer_update, 3000); //debouncer_update is called every 3ms

  Serial.begin(9600);
  delay(2000);
}

void loop()
{
  static button_state state = STATE_UNKNOWN;
  static button_state prev_state1 = STATE_UNKNOWN;
  static button_state prev_state2 = STATE_UNKNOWN;
  state = debouncer_get_state(BUTTON_PIN1);
  if (state != prev_state1)
  {
    Serial.printf("State of button1(pin-%d) : %s\n", BUTTON_PIN1, state_str[state]);

    prev_state1 = state;
  }
  state = debouncer_get_state(BUTTON_PIN2);
  if (state != prev_state2)
  {
    Serial.printf("State of button2(pin-%d) : %s\n", BUTTON_PIN2, state_str[state]);
    prev_state2 = state;
  }
}