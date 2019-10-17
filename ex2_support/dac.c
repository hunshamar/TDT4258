#include "dac.h"

#define DAC_CLOCK_BIT 	17
#define PRESC 			5
#define MODE_PIN 		1


void setupDAC()
{
	*CMU_HFPERCLKEN0 |= (1 << DAC_CLOCK_BIT); // Enable the DAC by setting bit 17 in CMU_HFPERCLKEN0
	*DAC0_CTRL |= (PRESC << 16);  // Prescale DAC clock by writing 5 to pin 16-18
	*DAC0_CTRL |= (MODE_PIN << 4); // set PIN output mode by writing 1 to pin 4
	*DAC0_CH0CTRL = 1; // Enable left audo channel
	*DAC0_CH1CTRL = 1; // Enable right audio channel
}




	/* Write a continuous stream of samples to the DAC
	 * data registers, DAC0_CH0DATA and DAC0_CH1DATA, for example from a
	 * timer interrupt 
	 * 
	 * 
	 * 
	 * 
	 */
