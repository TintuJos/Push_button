#include "debouncer.h"
#include "bsp.h"

#define MIN_BUTTON (1U)
#define INPUT_PULLUP 2

typedef struct
{
    uint8_t pin;
    button_state state;
    uint8_t count;
} button_t;

static button_t buttons[MAX_BUTTON];
static uint8_t num_buttons = 0;
static bool initialized = false;

static bool is_unique(uint8_t pins);

uint8_t debouncer_init(uint8_t pin)
{
    uint8_t status = DEBOUNCE_ERROR;

    if ((pin >= PIN_MIN) && (pin <= PIN_MAX) && (num_buttons < MAX_BUTTON))
    {
        if (is_unique(pin))
        {
            buttons[num_buttons].pin = pin;
            buttons[num_buttons].state = STATE_UNKNOWN;
            buttons[num_buttons].count = 0;
            bsp_pin_mode(pin, INPUT_PULLUP);
            initialized = true;
            num_buttons++;
            status = DEBOUNCE_SUCCESS;
        }
    }
    return status;
}

void debouncer_update(void)
{
    if (initialized)
    {
        for (int i = 0; i < num_buttons; i++)
        {
            int reading = bsp_digital_read(buttons[i].pin);
            buttons[i].count++;

            if (reading == LOW && buttons[i].state != STATE_FALLING && buttons[i].state != STATE_PRESSED)
            {
                buttons[i].state = STATE_FALLING;
                buttons[i].count = 1;
            }
            if (reading == HIGH && buttons[i].state != STATE_RISING && buttons[i].state != STATE_RELEASED)
            {
                buttons[i].state = STATE_RISING;
                buttons[i].count = 1;
            }

            if (buttons[i].count == 5)
            {
                if (buttons[i].state == STATE_FALLING)
                    buttons[i].state = STATE_PRESSED;

                if (buttons[i].state == STATE_RISING)
                    buttons[i].state = STATE_RELEASED;

                buttons[i].count = 0;
            }
        }
    }
}

button_state debouncer_get_state(uint8_t pin)
{
    button_state state = STATE_UNKNOWN;
    if (initialized)
    {
        for (int i = 0; i < num_buttons; i++)
        {
            if (buttons[i].pin == pin)
            {
                state = buttons[i].state;
                break;
            }
        }
    }
    return state;
}

void debouncer_reset(void)
{
    num_buttons = 0;
}

static bool is_unique(uint8_t pin)
{
    bool unique = true;

    for (uint8_t i = 0; unique && (i < num_buttons); i++)
    {
        if (buttons[i].pin == pin)
        {
            unique = false;
            break;
        }
    }

    return unique;
}
