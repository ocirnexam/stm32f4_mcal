#include "servo.h"

void Servo_Init(Servo servo)
{
  GPIO_Config(servo.port);
  Timer_Init_PWM(servo.timer, 16, 2500);
}

void Servo_Write(Servo servo, int angle)
{
    switch(servo.channel) {
      case 1:
        servo.timer->CCR1 = angle;
      case 2:
        servo.timer->CCR2 = angle;
        break;
      default:
        break;
    }
}