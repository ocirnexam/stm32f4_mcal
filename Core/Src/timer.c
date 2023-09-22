#include "timer.h"

void Timer_Init_PWM(TIM_TypeDef *timer)
{
    RCC->APB2ENR |= (1<<11); // Timer 1
    timer->PSC = 1800; // 180MHz / 50Hz = 3600KHz
    timer->ARR = 1000;
    timer->CNT = 0;

    timer->CCR1 = 100;
    timer->CCMR1 |= ((1<<6)|(1<<5)); // Enable PWM1 mode
    timer->CCMR1 |= (1<<3); // Enable 0C1

    timer->CCER |= ((1<<0)|(1<<1)); // CCIE, CCIP Enable
    timer->BDTR |= ((1<<15)|(1<<10)); // MOE Enable, OSSI Enable
    timer->EGR |=(1<<0); // UG Bit
    timer->CR1 |= (1<<0);
}