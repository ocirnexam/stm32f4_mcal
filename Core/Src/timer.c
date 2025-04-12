#include "timer.h"

void Timer_PWM_Init(TIM_TypeDef *timer, int prescaler, int steps)
{
    RCC->APB1ENR |= (1<<1);            // Timer 3 TODO: MAKE DYNAMIC

    timer->CCMR1 &= ~(0b11 << 0);      // Enable Output Mode for Channel 1
    timer->CCMR1 |= (0b110 << 4);      // Enable PWM1 mode
    timer->CCMR1 |= (1 << 3);          // Enable OC1PE
    timer->CCER &= ~(1 << 1);          // Output Polarity Active High
    timer->CCER |= (1 << 0);           // Output Compare Enable
    timer->CR1 |= (1 << 7);            // ARPE

    timer->PSC = prescaler-1;          // sysclock / (PSC + 1) = PWM frequency
    timer->ARR = steps-1;              // amount of steps of the PWM cycle 
    timer->CCR1 = 0;                   // duty cycle of 0% in channel 1

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

void Timer_PWM_Set_Duty_Cycle_Steps(TIM_TypeDef *timer, int counter_limit)
{
    timer->CCR1 = counter_limit;
}

void Timer_PWM_Set_Duty_Cycle_Degrees(TIM_TypeDef* timer, int channel, int angle)
{
    timer->CCR1 = (uint32_t) (((float)(angle / 180.f)) * 2000.f) + 500.f;
}