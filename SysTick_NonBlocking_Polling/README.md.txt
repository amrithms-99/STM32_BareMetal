# Non-Blocking LED Control Using SysTick

## Overview
This project demonstrates a non-blocking LED blink implementation using the SysTick timer on an STM32 microcontroller.  
A global 1 ms system tick is generated using SysTick polling, and LED control is performed based on elapsed time without using blocking delay loops.

The application is written using bare-metal programming, with direct access to hardware registers and no RTOS.


## Target Hardware
- Microcontroller: STM32F401
- Architecture: ARM Cortex-M4
- GPIO Port: GPIOA
- LED Pin: PA5
- System Clock: 16 MHz


## Key Concepts Demonstrated
- SysTick timer configuration
- Software time base generation (1 ms tick)
- Non-blocking delay implementation
- GPIO control using bit set/reset register
- State-based LED toggling


## Peripheral Usage
- RCC: Enables clock for GPIOA
- GPIO: Configures PA5 as output
- SysTick: Generates a periodic 1 ms time reference


## Program Description
The program performs the following operations:
1. Configures GPIOA pin 5 as an output.
2. Initializes SysTick to generate a 1 ms time base.
3. Updates a global millisecond counter using SysTick polling.
4. Toggles the LED state every 500 ms using elapsed time comparison.
5. Executes all logic without blocking delays.