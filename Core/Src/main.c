#include "helpers.h"
#include "systemclock_config.h"
#include "stm32f4xx.h"

void SystemInit(void)
{
  /* FPU settings ------------------------------------------------------------*/
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
  #endif
}

void GPIO_Config(void)
{
  // enable gpioa clock
  RCC->AHB1ENR |= (1 << 0);

  // set pin as output
  GPIOA->MODER |= (1 << 10);

  // configure OUTPUT MODE
  GPIOA->OTYPER = 0;
  GPIOA->OSPEEDR = 0;
}

int main(void)
{
  if(SysClockConfig() == COUNTDOWN_EXCEEDED_ERROR)
  {
    return COUNTDOWN_EXCEEDED_ERROR;
  }
  GPIO_Config();
  while (1)
  {
    GPIOA->BSRR |= (1 << 5);
    sleep(1);
    GPIOA->BSRR |= (1 << 21);
    sleep(1);
  }
  return 0;
}