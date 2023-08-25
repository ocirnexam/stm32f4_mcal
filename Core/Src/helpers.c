#include "helpers.h"

void msleep(int millisecs) {
  #define STEPS_PER_MSEC 6500000 / 1000
  unsigned int i,s;
  for (s=0; s < millisecs; s++) {
    for (i=0; i < STEPS_PER_MSEC; i++) {
       // skip CPU cycle or any other statement(s) for making loop 
       // untouched by C compiler code optimizations
       asm("nop");
    }
  }
}