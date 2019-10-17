#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "gpio.h"
#include "sound.h"
#include "efm32gg.h"

uint16_t sound_0 = 0;
uint16_t sound_1 = 0;


void __attribute__ ((interrupt)) TIMER1_IRQHandler()
{
	*TIMER1_IFC = 1;
	play_sound();
}


void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	if (button_pressed(0))
	{

		set_sound_type(0);
	}
	else if (button_pressed(2))
	{
		set_sound_type(2);
	}
	else if (button_pressed(6))
	{
		change_volume(50);
	}
	else if (button_pressed(8))
	{
		change_volume(-50);
	}
	clear_interrupt();
}


void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	if (button_pressed(1))
	{
		set_sound_type(1);
	}
	else if (button_pressed(3))
	{
		set_sound_type(3);
	}
	else if (button_pressed(5))
	{
		change_frequency(-10);
	}
	else if (button_pressed(7))
	{
		change_frequency(10);
	}
	clear_interrupt();
	
}


