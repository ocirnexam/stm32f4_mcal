#include "servo.h"

void Servo_Init(Servo* servo)
{
  GPIO_Config(servo->port);
  Timer_PWM_Init(servo->timer, 16, 20000); // pwm frequency 16MHz / 16 = 1MHz, 20000 steps => 1 cycle 50Hz
  Timer_Start(servo->timer);
}

void Servo_Write(Servo* servo, int angle)
{
    // TIM3->CR1 &= ~1;
    Timer_PWM_Set_Duty_Cycle_Degrees(servo->timer, servo->channel, angle);
    // TIM3->CR1 |= 1;
}