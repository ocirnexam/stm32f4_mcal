#ifndef _TIMER_H_INCLUDED
#define _TIMER_H_INCLUDED

#include <stm32f446xx.h>
#include <stdint.h>

int Timer_Init(TIM_TypeDef* timer, int prescaler, int steps);
int Timer_Quit(TIM_TypeDef* timer);
int Timer_Start(TIM_TypeDef* timer);
void Timer_PWM_Init(TIM_TypeDef* timer, int prescaler, int steps);
void Timer_PWM_Set_Count_Limit(TIM_TypeDef* timer, int counter_limit);
void Timer_PWM_Set_Duty_Cycle_Degrees(TIM_TypeDef* timer, int channel, int angle);

#endif /* _USART_H */
