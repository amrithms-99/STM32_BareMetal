//LED blinking program using Bare metal
#include<stdint.h>
#define GPIO_Base 0x50000000
#define RCC_Base 0x40021000UL

#define GPIO_MODER *((uint32_t*)(GPIO_Base + 0x00))
#define GPIO_ODR *((uint32_t*)(GPIO_Base + 0x10))
#define RCC_IOPENR *((uint32_t*)(RCC_Base + 0x34))


int main(void)
{
	//enable RCC peripheral
	RCC_IOPENR |= (1U << 0);
	GPIO_MODER  &= (3U << (2*12));
	GPIO_MODER |= (1U << (2*12));
	while (1)
	{
	GPIO_ODR ^=(1U << 12);
	}




	//set GPIO Mode

}
