#include <stdint.h>
#include <stm32f401xe.h>

/* ---------------- Global Variables ---------------- */

volatile uint32_t led_period_ms = 1000;

/* ---------------- GPIO ---------------- */

static void GPIO_Init(void)
{
    /* Enable GPIOA clock */
    RCC->AHB1ENR |= (1U << 0);

    /* PA5 as output */
    GPIOA->MODER &= ~(3U << (2 * 5));
    GPIOA->MODER |=  (1U << (2 * 5));

    /* PA2, PA3 (RX, TX) as alternate function (USART2) */
    GPIOA->MODER &= ~(3U << (2 * 2));
    GPIOA->MODER &= ~(3U << (2 * 3));
    GPIOA->MODER |=  (2U << (2 * 2));
    GPIOA->MODER |=  (2U << (2 * 3));

    /* AF7 for USART2 */
    GPIOA->AFR[0] |= (7U << (4 * 2));
    GPIOA->AFR[0] |= (7U << (4 * 3));
}

/* ---------------- UART ---------------- */

static void UART2_Init(void)
{
    /* Enable USART2 clock */
    RCC->APB1ENR |= (1U << 17);

    /* Baud rate = 115200 at16 MHz */
    USART2->BRR = 16000000 / 115200;

    /* Enable RX, RX interrupt, USART */
    USART2->CR1 |= (1U << 2);   // RE
    USART2->CR1 |= (1U << 5);   // RXNEIE
    USART2->CR1 |= (1U << 13);  // UE

    NVIC_EnableIRQ(USART2_IRQn);
}

/* ---------------- Timer ---------------- */

static void TIM2_Init(uint32_t period_ms)
{
    /* Enable TIM2 clock */
    RCC->APB1ENR |= (1U << 0);

    /* Disable timer */
    TIM2->CR1 = 0;

    /* 16 MHz / 16000 = 1 kHz → 1 ms tick */
    TIM2->PSC = 16000 - 1;
    TIM2->ARR = period_ms - 1;

    /* Enable update interrupt */
    TIM2->DIER |= (1U << 0);

    /* Clear flag */
    TIM2->SR &= ~(1U << 0);

    NVIC_EnableIRQ(TIM2_IRQn);

    /* Enable timer */
    TIM2->CR1 |= (1U << 0);
}

/* ---------------- ISRs ---------------- */

void TIM2_IRQHandler(void)
{
    if (TIM2->SR & (1U << 0))   // UIF
    {
        GPIOA->ODR ^= (1U << 5);  // Toggle LED
        TIM2->SR &= ~(1U << 0);   // Clear flag
    }
}

void USART2_IRQHandler(void)
{
    if (USART2->SR & (1U << 5)) // RXNE
    {
        char cmd = USART2->DR;

        if (cmd == '1')
        	led_period_ms = 1000;
        else if (cmd == '2')
        	led_period_ms = 500;
        else if (cmd == '3')
        	led_period_ms = 200;

        //Update Timer
        TIM2->ARR = led_period_ms - 1;
    }
}

/* ---------------- Main ---------------- */

int main(void)
{
    GPIO_Init();
    UART2_Init();
    TIM2_Init(led_period_ms);

    while (1)
    {
        // event driven
    }
}
