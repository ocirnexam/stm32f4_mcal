#include "systemclock_config.h"
#include "helpers.h"

int SysClockConfig(void)
{
  volatile int reset_count;
  // enable HSE
  reset_count = 1000;
  RCC->CR |= (1 << 16);
  while(!(RCC->CR & (1 << 17)) && (--reset_count));
  if(reset_count == 0) {
    return COUNTDOWN_EXCEEDED_ERROR;
  }

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
  reset_count = 1000;
  RCC->CR |= (1 << 24);
  while(!(RCC->CR & (1 << 25)) && (--reset_count));
  if(reset_count == 0) {
    return COUNTDOWN_EXCEEDED_ERROR;
  }

  // set clock source
  reset_count = 1000;
  RCC->CFGR |= (1 << 1); // setting 2 (PLL_P)
  while((RCC->CFGR & 0b1100) != (0b10 << 2) && (--reset_count));
  if(reset_count == 0) {
    return COUNTDOWN_EXCEEDED_ERROR;
  }
  return INIT_SUCCESS;
}