# Non-Blocking LED Control Using SysTick Interrupt (Bare Metal)

## Overview
This project demonstrates a non-blocking LED blinking application implemented using the SysTick timer interrupt on an STM32 microcontroller.  
A global 1 ms system tick is generated using the SysTick interrupt handler, allowing time-based control of GPIO without blocking delays.

## Target Hardware
- Microcontroller: STM32F401
- Architecture: ARM Cortex-M4
- GPIO Port: GPIOA
- LED Pin: PA5
- System Clock: 16 MHz

## Key Concepts Demonstrated
- SysTick interrupt configuration
- Millisecond system tick generation
- Interrupt-driven timing
- Non-blocking delay implementation
- State-based GPIO control

## Peripheral Usage
- RCC: Enables clock for GPIOA
- GPIO: Configures PA5 as an output
- SysTick: Generates a periodic 1 ms interrupt

## Program Description
The program performs the following operations:
1. Configures GPIOA pin 5 as an output.
2. Initializes SysTick to generate a 1 ms interrupt.
3. Increments a global millisecond counter inside the SysTick interrupt handler.
4. Uses elapsed time comparison to toggle the LED every 500 ms.
5. Executes continuously without blocking the main loop.