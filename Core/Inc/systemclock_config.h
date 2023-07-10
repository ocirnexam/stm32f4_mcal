#ifndef SYSTEMCLOCK_CONFIG_H
#define SYSTEMCLOCK_CONFIG_H

#include "stm32f4xx.h"

#define PLL_M 4
#define PLL_N 180
#define PLL_P 0 // PLLP = 2

int SysClockConfig(void);

#endif