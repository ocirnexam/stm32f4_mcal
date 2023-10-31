#include "usart.h"


static uint8_t init_done = 0;
IOPin p = {GPIOA, PIN2, GPIO_ALT_FUNCION, GPIO_ALTF_SYSTEM};

void USART_Init_PC(void)
{

	RCC->APB1ENR |= (1 << 17);				// enable clock of usart 2
    RCC->AHB1ENR |= (1 << 0);

    GPIO_Config(p);

	GPIOA->AFR[0] &= ~(0xf << 4);			// reset alternate function of pin PB 6
	GPIOA->AFR[0] &= ~(0xf << 8);			// reset alternate function of pin PB 7
	GPIOA->AFR[0] |= (0x7 << 8);			// set alternate function of pin PB 7 to AF 7

	USART2->CR1 = 0x00000000;				// set to reset value
	USART2->CR1 &= ~(1 << 12);				// data length (M[1:0])
	USART2->CR1 &= ~(1 << 15);				// oversampling with 16
	USART2->CR1 &= ~(1 << 10);				// parity control disabled

	USART2->CR2 = 0x00000000;				// set to reset value
	USART2->CR3 = 0x00000000;				// set to reset value

	USART2->BRR = 1600; // TODO

	USART2->CR1 |= (1 << 3);				// enable transmitter
	USART2->CR1 |= (1 << 13);				// enable uart

	init_done = 1;
}

void send_byte_pc(uint8_t byte)
{

	uint16_t bound = 0;
	//Wait until buffer is empty
	while(!(USART2->SR & (1 << 7)) && ++bound < UINT16_MAX)
		;
	
	//Write data to buffer
	USART2->DR = byte;
}

void send_string_pc(char *byte)
{
	uint16_t bound = 0;
	while (*byte && ++bound < UINT16_MAX) // '\0' is the same as value 0
		send_byte_pc((uint8_t) *byte++);
}


uint8_t receive_byte_pc(uint8_t *byte_ptr)
{
	uint8_t ret;

	//check if byte in buffer is available
	if ( (USART2->SR & (1 << 5)) ) {
		//read from buffer
		*byte_ptr = USART2->DR;
		ret = 1;
	} else {
		ret = 0;
	}
	
	return ret;
}
