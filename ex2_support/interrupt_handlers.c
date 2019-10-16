#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "efm32gg.h"

uint16_t sound_0 = 0;
uint16_t sound_1 = 0;
double time = 0.0;
double period_c_note = 0.0038222;

/*
 * TIMER1 interrupt handler 
 */
void __attribute__ ((interrupt)) TIMER1_IRQHandler()
{
	*TIMER1_IFC = 1;
	time += 0.000022643;//timer period in seconds

	*DAC0_CH0DATA = 1000 + (int)round(1000 * sin(time*2*3.14/period_c_note));
	*DAC0_CH1DATA = 1000 + (int)round(1000 * sin(time*2*3.14/period_c_note));


	/*
	 * TODO feed new samples to the DAC remember to clear the pending
	 * interrupt by writing 1 to TIMER1_IFC 
	 */
}

/*
 * GPIO even pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
}

/*
 * GPIO odd pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
}
