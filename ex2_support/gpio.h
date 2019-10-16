#include <stdint.h>
#include <stdbool.h>

#include <stdbool.h>
#include "efm32gg.h"


void setupGPIO();

void illuminate_LED(uint8_t pin);

void dilluminate_LED(uint8_t pin);

bool button_pressed(uint8_t button_number);