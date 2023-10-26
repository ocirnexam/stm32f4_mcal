#include "servo.h"

void Servo_Init(IOPin servo)
{
  GPIO_Config(servo, GPIO_ALT_FUNCION);
  Timer_Init_PWM(TIM4);
  Timer_Start(TIM4);
}

void Servo_Write(int angle)
{
    TIM4->CCR1 = angle;
}