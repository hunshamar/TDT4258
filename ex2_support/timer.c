#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"


void setupTimer(uint16_t period)
{
	*CMU_HFPERCLKEN0 |=(1<<6);
	*TIMER1_TOP = period;
	*TIMER1_IEN = 1;
	*TIMER1_CMD = 1;	
}

//waits for one period
void busy_wait()
{
	while (*TIMER1_CNT != *TIMER1_TOP){}
}
