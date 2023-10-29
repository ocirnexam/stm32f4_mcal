#ifndef _SERVO_H_INCLUDED
#define _SERVO_H_INCLUDED

#include <stm32f446xx.h>
#include <stdint.h>
#include "gpio.h"
#include "timer.h"

typedef struct
{
  IOPin port;
  TIM_TypeDef *timer;
  int channel;
} Servo;

void Servo_Init(Servo);
void Servo_Write(Servo, int);

#endif /* _USART_H */
