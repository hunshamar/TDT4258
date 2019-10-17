#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "gpio.h"
#include "sound.h"
#include "efm32gg.h"

uint16_t sound_0 = 0;
uint16_t sound_1 = 0;

void interrupt_init(){
	*GPIO_EXTIPSELL = 0x22222222; // enables interupt generation on pins 0-7(the buttons)
	*GPIO_EXTIFALL = 0xFF;	// enables interrupt generation on the 1->0 transition, when the button is pressed down
	*GPIO_IEN = 0xFF; 	// enable interrupt generation from the specific GPIO-register
}

void interrupt_clear() { 
	*GPIO_IFC = *GPIO_IF; 	// clears the interrupt source, 
							// if this is not done the interrupt will be called repeatedly after the first interrupt
}

void interrupt_handler(){
	if (GPIO_button_pressed(0))
	{
		set_sound_type(0);
	}
	else if (GPIO_button_pressed(1))
	{
		set_sound_type(1);
	}
	else if (GPIO_button_pressed(2))
	{
		set_sound_type(2);
	}
	else if (GPIO_button_pressed(3))
	{
		set_sound_type(3);
	}
	else if (GPIO_button_pressed(4))
	{
		change_frequency(-10);
	}
	else if (GPIO_button_pressed(5))
	{
		change_volume(50);
	}
	else if (GPIO_button_pressed(6))
	{
		change_frequency(10);
	}
	else if (GPIO_button_pressed(7))
	{
		change_volume(-50);
	}
	interrupt_clear();	
}


void __attribute__ ((interrupt)) TIMER1_IRQHandler()
{
	*TIMER1_IFC = 1;
	play_sound();
}


void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	interrupt_handler();	
}


void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{	
	interrupt_handler();
}