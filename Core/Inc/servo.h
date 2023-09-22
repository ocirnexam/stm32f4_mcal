#ifndef _SERVO_H_INCLUDED
#define _SERVO_H_INCLUDED

#include <stm32f446xx.h>
#include <stdint.h>
#include "gpio.h"
#include "timer.h"

void Servo_Init(IOPin servo);
void Servo_Write(int angle);

#endif /* _USART_H */
