#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

#include <stdbool.h>
#include "efm32gg.h"


void GPIO_init();

void GPIO_illuminate_LED(uint8_t pin);

void GPIO_delluminate_LED(uint8_t pin);

bool GPIO_button_pressed(uint8_t button_number);

void GPIO_toggle_LED(uint8_t led_number);


int button_poll();

#endif