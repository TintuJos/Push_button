#ifndef BSP_H
#define BSP_H

#include <stdint.h>
#include <stddef.h>

uint8_t bsp_digital_read(uint8_t pin);

void bsp_pin_mode(uint8_t pin, uint8_t mode);

void bsp_delay(uint32_t msec);

#endif /* BSP_H */
