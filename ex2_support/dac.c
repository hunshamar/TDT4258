#include "dac.h"

#define DAC0_BIT 	17 
#define PRESC 		5
#define MODE_PIN 	1
#define PRESC_BIT 	16
#define MODE_BIT 	4


void setupDAC()
{
	*CMU_HFPERCLKEN0 |= (1 << DAC0_BIT); // Enable the DAC0 clock by setting bit 17 in CMU_HFPERCLKEN0
	*DAC0_CTRL |= (PRESC << PRESC_BIT);  // Prescale DAC clock by writing 5 to pin 16-18
	*DAC0_CTRL |= (MODE_PIN << MODE_BIT); // set PIN output mode by writing 1 to pin 4
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
