#include "systemclock_config.h"
#include "helpers.h"

int SysClockConfig(void)
{
  // volatile int reset_count = 10000;
  // while(!(RCC->CR & (1 << 1)) && (--reset_count));
  // if(reset_count == 0) {
  //   return COUNTDOWN_EXCEEDED_ERROR;
  // }
  return INIT_SUCCESS;
}