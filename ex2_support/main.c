#include <stdint.h>
#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

#include "efm32gg.h"
#include "gpio.h"
#include "timer.h"
#include "dac.h"
#include "sound.h"
#include "interrupt_handler.h"
/*
 * The period between sound samples, in clock cycles (CPU runs at 14Mhz)
 */
#define   SAMPLE_PERIOD   317

/*
 * Declaration of peripheral setup functions 
 */
void NVIC_init();

/*
 * Your code will start executing here 
 */
int main(void)
{
	/*
	 * Call the peripheral setup functions 
	 */
	setupGPIO();
	setupNVIC();
	setupDAC();
	setupTimer(SAMPLE_PERIOD);
	startup_tune();
	//setSleep(0b110);
	
	while(true)
	{
		if(busy_wait())
		{
			int button_pressed = button_poll();
			switch(button_pressed)
			{
				case 0:
					set_sound_type(0);
					break;
				case 1:
					set_sound_type(1);
					break;
				case 2:
					set_sound_type(2);
					break;
				case 3:
					set_sound_type(3);
				case 4:
					change_frequency(-20);
				case 5:
					change_volume(20);
				case 6:
					change_frequency(20);
				case 7:
					change_volume(-20);
					break;
				default:
					break;
			}
			play_sound();
		}
	}
	return 0;
}

void NVIC_init()
{
	*ISER0 = 0x1802;	
}

void set_sleep(int arg)
{
	*SCR = arg;
}
