#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#include <stdbool.h>
#include "efm32gg.h"


void interrupt_init();
void interrupt_clear();

#endif