#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

#include <stm32f446xx.h>

#define GPIO_INPUT 0b00
#define GPIO_GENERAL_OUTPUT 0b01
#define GPIO_ALT_FUNCION 0b10
#define GPIO_ANALOG_MODE 0b11

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15

#define GPIO_PIN_SET 0
#define GPIO_PIN_UNSET 16

typedef struct
{
  GPIO_TypeDef *port;
  int pin;
} IOPin;

void GPIO_Config(IOPin p, int);
void GPIO_WritePin(IOPin p, int);

#endif