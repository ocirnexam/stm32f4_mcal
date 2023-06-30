#include "stm32f4xx.h"
#include "core_cm4.h"

#define PLL_M 4
#define PLL_N 180
#define PLL_P 0 // PLLP = 2

void SystemInit(void)
{
  /* FPU settings ------------------------------------------------------------*/
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
  #endif
}

void SysClockConfig(void)
{
  // enable HSE
  RCC->CR |= (1 << 16);
  while(!(RCC->CR & (1 << 17)));

  // set POWER ENABLE CLOCK and VOLTAGE REGULATOR
  RCC->APB1ENR |= (1 << 28);
  PWR->CR |= (0b11 << 14); //writing bit 14 and 15

  // configure FLASH PREFETCH and LATENCY settings
  FLASH->ACR |= (1 << 8) | // prefetch enable
                (1 << 9) | // instruction cache enable
                (1 << 10) | // data cache enable
                (0b101); // 5 wait states latency

  // configure prescalars HCLK, PCLK1, PCLK2
  RCC->CFGR |= (0b000 << 4);
  RCC->CFGR |= (0b101 << 10);
  RCC->CFGR |= (0b100 << 13);

  // configure MAIN PLL
  RCC->PLLCFGR = (PLL_M << 0) | (PLL_N << 6) | (PLL_P << 16) | (1 << 22);

  // enable PLL
  RCC->CR |= (1 << 24);
  while(!(RCC->CR & (1 << 25)));

  // set clock source
  RCC->CFGR |= (1 << 1); // setting 2 (PLL_P)
  while((RCC->CFGR & 0b1100) != (0b10 << 2));
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

void sleep(int secs) {
  #define STEPS_PER_SEC 6500000
  unsigned int i,s;
  for (s=0; s < secs; s++) {
    for (i=0; i < STEPS_PER_SEC; i++) {
       // skip CPU cycle or any other statement(s) for making loop 
       // untouched by C compiler code optimizations
       asm("nop");
    }
  }
}

int main(void)
{
  SysClockConfig();
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