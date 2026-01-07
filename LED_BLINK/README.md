# LED Toggle Using Bare-Metal Programming

## Overview
This project demonstrates a simple LED blinking application implemented using bare-metal programming on an STM32 microcontroller.  
The program directly accesses memory-mapped peripheral registers without using HAL, CMSIS, or any RTOS.

## Target Hardware
- Microcontroller: STM32F401RE
- Architecture: ARM Cortex-M4
- GPIO pin used: Pin 12

## Registers Used

| Register Name | Address | Description |
|--------------|--------|-------------|
| RCC_IOPENR | 0x40021034 | Enables GPIO peripheral clock |
| GPIO_MODER | 0x50000000 | Configures GPIO pin mode |
| GPIO_ODR | 0x50000010 | Controls GPIO output state |


## Program Description
The program performs the following steps:
1. Enables the GPIO peripheral clock using the RCC register.
2. Configures GPIO pin 12 as an output pin.
3. Toggles the GPIO output data register in an infinite loop.