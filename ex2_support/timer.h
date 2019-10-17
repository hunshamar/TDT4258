#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
bool busy_wait();
void setupTimer(uint16_t period);

#endif
