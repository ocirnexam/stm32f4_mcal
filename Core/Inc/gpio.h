#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

#include <stm32f446xx.h>

#define GPIO_INPUT 0b00
#define GPIO_GENERAL_OUTPUT 0b01
#define GPIO_ALT_FUNCION 0b10
#define GPIO_ANALOG_MODE 0b11

#define PORT0 0
#define PORT1 2
#define PORT2 4
#define PORT3 6
#define PORT4 8
#define PORT5 10
#define PORT6 12
#define PORT7 14
#define PORT8 16
#define PORT9 18
#define PORT10 20
#define PORT11 22
#define PORT12 24
#define PORT13 26
#define PORT14 28
#define PORT15 30

#define GPIO_PIN_SET 0
#define GPIO_PIN_UNSET 16


void GPIO_Config(GPIO_TypeDef *, int, int);
void GPIO_WritePin(GPIO_TypeDef *, int, int);

#endif