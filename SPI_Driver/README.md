# Timer and UART Controlled LED (Bare-Metal STM32)

 Overview
This project implements an interrupt-driven bare-metal application on an STM32 microcontroller that combines a general-purpose timer (TIM2) and UART communication (USART2).

An LED is toggled periodically using a TIM2 update interrupt, while the toggle period can be modified at runtime through UART commands.  
The firmware is written using direct register-level programming, without HAL libraries.

This project demonstrates how multiple peripherals interact in a real embedded system.

---

## Target Hardware
- Microcontroller: STM32F401
- Architecture: ARM Cortex-M4
- System Clock: 16 MHz (HSI)
- LED Pin: PA5
- UART Interface: USART2  
  - TX: PA2  
  - RX: PA3  
- Timer Used: TIM2

---

## Functional Description
- TIM2 generates periodic interrupts to toggle the LED.
- USART2 receives user commands via UART.
- UART commands dynamically update the LED toggle period.
- The system operates fully in an event-driven, non-blocking manner.

---

## UART Command Interface

| Command | LED Toggle Period |
|-------|------------------|
| `1` | 1000 ms |
| `2` | 500 ms |
| `3` | 200 ms |

Upon receiving a valid command, the timer period is updated immediately without stopping the system.

## Peripheral Configuration Summary

### GPIO
- PA5 configured as a general-purpose output for LED control.
- PA2 and PA3 configured in alternate function mode (AF7) for USART2.

### Timer (TIM2)
- Prescaler configured to generate a 1 ms time base.
- Auto-reload register used to define LED toggle period.
- Update interrupt enabled and handled in `TIM2_IRQHandler`.

### UART (USART2)
- Baud rate: 115200
- RX interrupt enabled.
- Commands processed inside `USART2_IRQHandler`.


## Program Flow
1. Initialize GPIO, UART, and TIM2 peripherals.
2. TIM2 interrupt toggles the LED at the configured interval.
3. UART RX interrupt updates the LED period based on received input.
4. The main loop remains idle, as all functionality is interrupt-driven.
