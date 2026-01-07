#  Delay program using SysTick Timer (Bare Metal)

## Overview
This project demonstrates how to generate a software delay using the SysTick timer on an STM32 microcontroller and use it to blink an LED.  
The application is written using bare-metal programming, with direct access to peripheral registers and without the use of RTOS.

The delay is implemented using the core SysTick timer configured to generate a fixed time interval.

## Target Hardware
- Microcontroller: STM32F401
- Architecture: ARM Cortex-M4
- GPIO Port: GPIOA
- LED Pin: PA5
- System Clock: 16 MHz (assumed)


## Peripheral Usage
- RCC: Enables clock for GPIOA
- GPIO: Configures PA5 as output
- SysTick: Generates approximately 500 ms delay


## Program Description
The program performs the following steps:
1. Enables the clock for GPIOA using the RCC register.
2. Configures PA5 as a general-purpose output pin.
3. Configures the SysTick timer to generate a delay.
4. Toggles the LED state using the GPIO bit set/reset register.
5. Repeats the process continuously.
