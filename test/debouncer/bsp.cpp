#ifndef DEVENV
#include <Arduino.h>
#endif
#include "bsp.h"

static uint8_t pin_num = 0xFF;
static uint8_t pin_mode = 0xFF;
static uint8_t pin_state = 0xFF;

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    pin_num = pin;
    pin_mode = mode;
#ifndef DEVENV
    pinMode(pin, mode);
#endif
}

uint8_t bsp_digital_read(uint8_t pin)
{
    pin_num = pin;
    return pin_state;
#ifndef DEVENV
    return digitalRead(pin);
#endif
}

void bsp_delay(uint32_t msec)
{
#ifndef DEVENV
    delay(msec);
#endif
}

uint8_t double_get_pin_num(void)
{
    return pin_num;
}

uint8_t double_get_pin_mode(void)
{
    return pin_mode;
}

void double_digital_write(uint8_t pin, uint8_t value)
{
    pin_num = pin;
    pin_state = value;
}