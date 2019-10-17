#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#include <stdbool.h>
#include "efm32gg.h"


void interrupt_setup();
void interrupt_clear();

#endif