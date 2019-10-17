#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

void timer_init(uint16_t period);

#endif