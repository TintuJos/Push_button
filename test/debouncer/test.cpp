#include "bsp.h"
#include <unity.h>
#include "debouncer.h"

void setUp(void) {}

void tearDown(void)
{
    debouncer_reset();
}

void test_debouncer_invalid(void)
{
    // Test for an invalid pin number and an uninitialized condition
    uint8_t pin = 17;
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_ERROR, debouncer_init(PIN_MAX + 1));
    TEST_ASSERT_EQUAL_UINT8(STATE_UNKNOWN, debouncer_get_state(pin));
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_ERROR, debouncer_init(PIN_MIN - 1));
    TEST_ASSERT_EQUAL_UINT8(STATE_UNKNOWN, debouncer_get_state(pin));
    //Test for duplicate pin number
    pin = 18;
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_SUCCESS, debouncer_init(pin));
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_ERROR, debouncer_init(pin));
}
void test_debouncer_falling(void)
{
    // Test for falling state of all buttons

    for (uint8_t pin = 20; pin < 20 + MAX_BUTTON; pin++)
    {
        TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_SUCCESS, debouncer_init(pin));
        double_digital_write(pin, LOW);
        debouncer_update();
        TEST_ASSERT_EQUAL_UINT8(STATE_FALLING, debouncer_get_state(pin));
    }
}
void test_debouncer_pressed(void)
{
    // Test for pressed state
    uint8_t pin = 7;
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_SUCCESS, debouncer_init(pin));
    double_digital_write(pin, LOW);

    for (int i = 0; i < 5; i++)
    {
        bsp_delay(3);
        debouncer_update(); //Calling update function 5 consecutive time
    }
    TEST_ASSERT_EQUAL_UINT8(STATE_PRESSED, debouncer_get_state(pin));
}
void test_debouncer_rising(void)
{
    // Test for rising state of 8 buttons
    uint8_t pin;
    for (pin = 20; pin < (20 + MAX_BUTTON); pin++)
    {
        TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_SUCCESS, debouncer_init(pin));
        double_digital_write(pin, HIGH);
        debouncer_update();
        TEST_ASSERT_EQUAL_UINT8(STATE_RISING, debouncer_get_state(pin));
    }
}
void test_debouncer_released(void)
{
    // Test for released state
    uint8_t pin = 5;
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_SUCCESS, debouncer_init(pin));
    double_digital_write(pin, HIGH);

    for (int i = 0; i < 5; i++)
    {
        bsp_delay(3);
        debouncer_update();
    }
    TEST_ASSERT_EQUAL_UINT8(STATE_RELEASED, debouncer_get_state(pin));
}
void test_debouncer_maxbuttons(void)
{
    //Test for more than 8 buttons
    uint8_t pin;
    for (pin = 1; pin < (1 + MAX_BUTTON); pin++)
    {
        TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_SUCCESS, debouncer_init(pin));
    }

    pin = 1 + MAX_BUTTON;
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_ERROR, debouncer_init(pin));
}

void test_debouncer_get_all(void)
{
    //Test rising and falling state of  8 buttons
    uint8_t pin;
    for (pin = 1; pin < (1 + MAX_BUTTON); pin++)
    {
        TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_SUCCESS, debouncer_init(pin));
        double_digital_write(pin, HIGH);
        debouncer_update();
        TEST_ASSERT_EQUAL_UINT8(STATE_RISING, debouncer_get_state(pin));
    }
    debouncer_reset();
    for (pin = 1; pin < (1 + MAX_BUTTON); pin++)
    {
        TEST_ASSERT_EQUAL_UINT8(DEBOUNCE_SUCCESS, debouncer_init(pin));
        double_digital_write(pin, LOW);
        debouncer_update();
        TEST_ASSERT_EQUAL_UINT8(STATE_FALLING, debouncer_get_state(pin));
    }
}

int main(void)
{

    bsp_delay(3000);
    UNITY_BEGIN();
    RUN_TEST(test_debouncer_invalid);
    RUN_TEST(test_debouncer_falling);
    RUN_TEST(test_debouncer_pressed);
    RUN_TEST(test_debouncer_rising);
    RUN_TEST(test_debouncer_released);
    RUN_TEST(test_debouncer_maxbuttons);
    RUN_TEST(test_debouncer_get_all);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();

    while (1)
    {
        ;
    }

    return 0;
#endif
}