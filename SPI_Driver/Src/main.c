#include <stdint.h>
#include <stm32f401xe.h>

/* ---------------- Global Variables ---------------- */
volatile uint8_t Tx_flag ;

static void GPIO_init()
{
	RCC->AHB1ENR|= 1U<<0; // GPIO clock enable
	RCC->APB2ENR|=1U<<12; // enable the clock for peripheral
	GPIOA->MODER|=2U <<(2*5);
	GPIOA->MODER|=2U <<(2*6);
	GPIOA->MODER|=2U <<(2*7);
	GPIOA->AFR[0] &= ~((0xF<<(5*4)) | (0xF<<(6*4)) | (0xF<<(7*4)));
	GPIOA->AFR[0]|= (5U<<(4*5)) | (5U<<(4*6)) | (5U<<(4*7)); // Configuring Pin 5,6,6 as alternate function
	GPIOA->OSPEEDR|= 3U<<(2*5); //set as high speed output for SCK
	GPIOA->OSPEEDR|= 3U <<(2*6); //set as high speed output for MISO
	GPIOA->OSPEEDR|= 3U <<(2*7); //set as high speed output for MOSI
	GPIOA ->MODER|= 1U<<(2*4);// configure PA4 (NSS) as output
	//GPIOA->PUPDR|= 1U<<(2*4); // configure PA4  as pull up. Not needed as it is high when SSI is enabled.

}

static void SPI_init()
{
	SPI1->CR1 |= 1U ; //CPHA
	SPI1->CR1 &= ~(1U<<1); //CPOL
	SPI1->CR1 |= 1U <<2; // Master mode
	SPI1->CR1 &= ~(7U << 3);   // Clear those pins
	SPI1->CR1 &= 1U << 3; //set baud rate
	SPI1->CR1 &= ~(1U <<7); //MSB transmitted first
	SPI1->CR1 |= 1U <<8; //SSI is enabled, directly write on NSS.
	SPI1->CR1 |= 1U <<9; //SSM is enabled . i.e slave select is managed by manipulating GPIO
	SPI1->CR1 &= ~(1U <<11); // Data format (8 bit)
	SPI1->CR1 |= 1U <<6; // start clock
	GPIOA->BSRR = (1U << 4);   // CS HIGH (inactive) or use MODER pull up



}



int main(void)
{
	GPIO_init();
	SPI_init();
   uint8_t data = 0xFF;


   while (1)
   {
       while (!(SPI1->SR & SPI_SR_TXE));   // Wait until TX buffer empty

       GPIOA->BSRR = (1U << (4 + 16));     // CS LOW

       SPI1->DR = data;                   // Send byte

       while (!(SPI1->SR & SPI_SR_TXE));   // Wait until DR empty
       while (SPI1->SR & SPI_SR_BSY);      // Wait until SPI not busy

       GPIOA->BSRR = (1U << 4);           // CS HIGH
   }


    }

