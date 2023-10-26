#include "timer.h"

void Timer_Init_PWM(TIM_TypeDef *timer)
{
    RCC->APB1ENR |= (1<<0);            // Timer 2 TODO: MAKE DYNAMIC
    timer->PSC = 16-1;                 // 16MHZ / 16 = 1MHZ
    timer->ARR = 100-1;                // Period of 100 ticks
    timer->CCR2 = 50;                 // duty cycle of 50% in channel 2
    timer->CNT = 0;                    // count 0

    timer->CCMR1 &= ~(0b11 << 8);      // Enable Output Mode for Channel 2
    timer->CCMR1 |= ((0b110 << 12));   // Enable PWM1 mode
    timer->CCMR1 |= (1 << 11);         // Enable OC1PE
    timer->CR1 |= (1 << 7);            // ARPE: TIM2_ARR register is buffered
    timer->CR1 |= (1 << 0);

}

int Timer_Init(TIM_TypeDef *timer, int prescaler, int steps) 
{
    /* configure interrupt for tim4 */
    NVIC->ISER[0] = (uint32_t)(1UL << (((uint32_t)TIM4_IRQn))); // NVIC ISER Nr. 30 set to 1 (enable) TODO: MAKE DYNAMIC

    /* setup timer */
    RCC->APB1ENR |= (1<<2);	     // Enables APB1 to use TIMER TODO: MAKE DYNAMIC
    timer->CR1 &= ~(1<<1);	     // UDIS: Update event enabled. Update events generated
    timer->CR1 |= (1<<2);	     // URS: Only over-/underflow generates update interrupt
    timer->CR1 &= ~(1<<3);       // OPM: Counter stops counting at the next update event (CEN set to 0)
    timer->CR1 &= ~(1<<7);       // ARPE: TIM4_ARR register is buffered
    timer->CNT = 0;
    timer->DIER |= (1<<8);       // UDE: Update DMA request enable
    timer->DIER |= (1<<0);       // TIE: Trigger interrupt enable
    timer->DIER |= (1<<14);      // TDE: Trigger DMA request enable
    timer->EGR |= (1<<0);	     // UG: Update generation. Re-initialize the counter and generates an update of the registers
    timer->PSC = prescaler;      // Counter clock frequency is systemclock / (prescaler)
    timer->ARR = steps;          // amount of steps with frequency in PSC
    return 1;
}

int Timer_Quit(TIM_TypeDef *timer)
{
    timer->CR1 &= ~(1<<0);	    // CEN: Disables counter
    return ((timer->CR1 & (1<<0)) == 0);
}

int Timer_Start(TIM_TypeDef *timer)
{
    timer->CR1 |= (1<<0);
    return ((timer->CR1 & (1<<0)) == 1);
}

void Timer_Set_Count_Limit(TIM_TypeDef *timer, int counter_limit)
{
    timer->ARR = counter_limit;
}
