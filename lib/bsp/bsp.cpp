#include <Arduino.h>
#include "bsp.h"

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    pinMode(pin, mode);
}

uint8_t bsp_digital_read(uint8_t pin)
{
    return digitalRead(pin);
}

void bsp_delay(uint32_t msec)
{
    delay(msec);
}
