

#include "gpio.h"

/*
 * function to set up GPIO mode and interrupts
 */
void setupGPIO()
{
	/*
	 * TODO set input and output pins for the joystick 
	 */
	*GPIO_PC_MODEL = 0x33333333; // Set buttons as inputs
    *GPIO_PC_DOUT = 0xFF; // Enable internal pull-up


	/*
	 * Example of HW access from C code: turn on joystick LEDs D4-D8 check 
	 * efm32gg.h for other useful register definitions 
	 */
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;	/* enable GPIO clock */
	*GPIO_PA_CTRL = 2;	/* set high drive strength */
	*GPIO_PA_MODEH = 0x55555555;	/* set pins A8-15 as output */
	*GPIO_PA_DOUT = 0xFF00;	/* turn on LEDs D4-D8 (LEDs are active low) */
	*GPIO_EXTIPSELL = 0x22222222; 
	*GPIO_EXTIFALL = 0xFF;
	*GPIO_IEN = 0xFF;
}

void illuminate_LED(uint8_t led_number){
	*GPIO_PA_DOUT &= ~( (1 << led_number) << 8 );
}

void dilluminate_LED(uint8_t led_number){
	*GPIO_PA_DOUT |= (1 << led_number ) << 8;
}

bool button_pressed(uint8_t button_number){

	return ~(*GPIO_PC_DIN) & 1 << button_number; // +1 because button 0 is called button 1
}



void toggle_LED(uint8_t led_number){
	*GPIO_PA_DOUT ^= (1 << led_number) << 8;
}

void clear_interrupt() { 
	*GPIO_IFC = *GPIO_IF;
}
