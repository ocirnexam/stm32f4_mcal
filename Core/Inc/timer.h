#ifndef _TIMER_H_INCLUDED
#define _TIMER_H_INCLUDED

#include <stm32f446xx.h>
#include <stdint.h>

void Timer_Init_PWM(TIM_TypeDef *, int, int);
int Timer_Init(TIM_TypeDef *, int, int);
int Timer_Quit(TIM_TypeDef *);
int Timer_Start(TIM_TypeDef *);
void Timer_Set_Count_Limit(TIM_TypeDef *, int);

#endif /* _USART_H */
