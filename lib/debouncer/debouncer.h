#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <stdint.h>

#define MAX_BUTTON (8U)

#define PIN_MIN 0
#define PIN_MAX 57

#define LOW 0
#define HIGH 1

#define DEBOUNCE_ERROR (0U)
#define DEBOUNCE_SUCCESS (1U)

typedef enum
{
    STATE_UNKNOWN,
    STATE_PRESSED,
    STATE_RELEASED,
    STATE_FALLING,
    STATE_RISING
} button_state;

/**
 * @brief  This function is used to initialize the module
 * 
 * @param pin Pin number connected to the push button.
 * @return uint8_t If there is an error DEBOUNCE_ERROR is returned. Otherwise DEBOUNCE_SUCCESS
 */
uint8_t debouncer_init(uint8_t pin);

/**
 * @brief This function is used to update the button state
 * 
 */
void debouncer_update(void);

/**
 * @brief This function is used to get the  state of a particular button
 * 
 * @param pin The pin number connected to the button
 * @return button_state The state of the button is returned
 */
button_state debouncer_get_state(uint8_t pin);

/**
 * @brief This function is used to reset the initialized buttons
 * 
 */
void debouncer_reset(void);

#endif