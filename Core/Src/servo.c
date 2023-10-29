#include "servo.h"

void Servo_Init(Servo servo)
{
  GPIO_Config(servo.port);
  Timer_Init_PWM(servo.timer, 16000, 180);
}

void Servo_Write(Servo servo, int angle)
{
    switch(servo.channel) {
      case 2:
        servo.timer->CCR2 = angle;
        break;
      default:
        break;
    }
}