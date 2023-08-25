#ifndef _USART_H_INCLUDED
#define _USART_H_INCLUDED

#include <stm32f446xx.h>
#include <stdint.h>
#include "gpio.h"

void USART_Init_PC(void);
void send_byte_pc(uint8_t byte);
void send_string_pc(char *byte);
uint8_t receive_byte_pc(uint8_t *byte_ptr);

#endif /* _USART_H */
