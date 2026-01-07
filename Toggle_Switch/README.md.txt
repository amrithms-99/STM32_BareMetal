# LED Frequency Control Using External Interrupt and SysTick (Bare Metal)

## Overview
This project demonstrates how to control the LED toggle frequency using an external interrupt from a push button combined with a SysTick-based timing mechanism on an STM32 microcontroller.

By default, the LED toggles at a 1 second interval. Each button press changes the toggle frequency dynamically, without blocking delays or polling the button in the main loop.

## Target Hardware
- Microcontroller: STM32F401
- Architecture: ARM Cortex-M4
- GPIO Port: GPIOA
- LED Pin: PA5
- Push Button Pin: PA0
- System Clock: 16 MHz (assumed)

## Key Concepts Demonstrated
- External interrupt (EXTI) configuration
- SysTick interrupt for time base generation
- Non-blocking LED control
- Interrupt debouncing using software timing
- State-based application design


## Peripheral Usage
- RCC: Enables clocks for GPIOA and SYSCFG
- GPIO: Configures PA5 as output and PA0 as input
- EXTI: Detects falling-edge interrupt from push button
- NVIC: Handles external interrupt servicing
- SysTick: Provides a 1 ms system tick


## Program Description
The program performs the following operations:
1. Initializes GPIO for LED output and push button input.
2. Configures SysTick to generate a 1 ms interrupt.
3. Configures EXTI line 0 to detect button presses on PA0.
4. Updates a global switch state inside the EXTI interrupt handler.
5. Controls LED toggle frequency based on the current switch state.
6. Uses non-blocking timing logic to toggle the LED.


## LED Frequency Control
Each valid button press cycles through three LED toggle intervals:

| Switch State | LED Toggle Interval |
|-------------|---------------------|
| 0 | 1000 ms |
| 1 | 500 ms |
| 2 | 200 ms |

The LED control logic calculates elapsed time using the SysTick counter.


## Interrupt Handling
### SysTick Interrupt
- Increments a global millisecond counter.
- Provides a system-wide time reference.

### External Interrupt (EXTI0)
- Triggered on falling edge of PA0.
- Implements software debounce using SysTick timing.
- Updates the switch state cyclically.