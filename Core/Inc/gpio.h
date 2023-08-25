#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

#include <stm32f446xx.h>

#define GPIO_INPUT 0b00
#define GPIO_GENERAL_OUTPUT 0b01
#define GPIO_ALT_FUNCION 0b10
#define GPIO_ANALOG_MODE 0b11

#define PIN0 0
#define PIN1 2
#define PIN2 4
#define PIN3 6
#define PIN4 8
#define PIN5 10
#define PIN6 12
#define PIN7 14
#define PIN8 16
#define PIN9 18
#define PIN10 20
#define PIN11 22
#define PIN12 24
#define PIN13 26
#define PIN14 28
#define PIN15 30

#define GPIONR_A 0
#define GPIONR_B 1
#define GPIONR_C 2
#define GPIONR_D 3
#define GPIONR_E 4
#define GPIONR_F 5
#define GPIONR_G 6
#define GPIONR_H 7


#define GPIO_PIN_SET 0
#define GPIO_PIN_UNSET 16

void GPIO_Config(GPIO_TypeDef *, int, int, int);
void GPIO_WritePin(GPIO_TypeDef *, int, int);

#endif