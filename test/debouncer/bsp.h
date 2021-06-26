#ifndef BSP_H
#define BSP_H

#include <stdint.h>
#include <stddef.h>

uint8_t bsp_digital_read(uint8_t pin);

void bsp_pin_mode(uint8_t pin, uint8_t mode);

void bsp_delay(uint32_t msec);

// Utility functions
uint8_t double_get_pin_num(void);
uint8_t double_get_pin_mode(void);
void double_digital_write(uint8_t pin, uint8_t value);

#endif /* BSP_H */
