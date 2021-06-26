# Assignment 1

In this assignment you are supposed to create a single-instance module(debouncer)
to debounce push buttons according to the requirements below.

## Requirements

1. To debounce buttons use the method explained in page 12 of signals-time-timing.pdf

2. Use TDD to develop and test the module on your computer.

    a. The module shall be fully tested and the code coverage shall be 100%.
    b. Use the link-time faking technique to make the test double
    c. To build and run the test, make a Makefile

3. The module shall be able to debounce multiple buttons (max. 8 buttons)

4. The pull-up resistors of the pins connected to the buttons shall be activated

5. To take samples(read) the pins and update the state of the buttons there shall be an
   update function in the interface of the module. The client of your module calls this
   function intervally.

    a. If there are 5 consecutive states of the same value, it means that the state of
    the button is stable and reliable.

6. The module shall detect pressed and released states of buttons

7. The module shall detect raising and falling edges in the state of buttons

8. You need to follow the dual targeting strategy and test the module on Teensy
   by making it independent of Arduino using an abstraction layer over Arduino.

## Build and Run

To build an run the tests, make a Makefile.
