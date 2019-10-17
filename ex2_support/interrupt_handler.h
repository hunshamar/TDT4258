#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#include <stdbool.h>
#include "efm32gg.h"


void setupInterrupt();
void clear_interrupt();

#endif