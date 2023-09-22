#include "servo.h"



void Servo_Init(IOPin servo)
{
  GPIO_Config(servo, GPIO_ALT_FUNCION);
  Timer_Init_PWM(TIM1);
}

void Servo_Write(int angle)
{
    TIM1->CCR1 = angle;
}