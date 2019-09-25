        .syntax unified
	
	      .include "efm32gg.s"

	/////////////////////////////////////////////////////////////////////////////
	//
  // Exception vector table
  // This table contains addresses for all exception handlers
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .section .vectors
	
	      .long   stack_top               /* Top of Stack                 */
	      .long   _reset                  /* Reset Handler                */
	      .long   dummy_handler           /* NMI Handler                  */
	      .long   dummy_handler           /* Hard Fault Handler           */
	      .long   dummy_handler           /* MPU Fault Handler            */
	      .long   dummy_handler           /* Bus Fault Handler            */
	      .long   dummy_handler           /* Usage Fault Handler          */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* SVCall Handler               */
	      .long   dummy_handler           /* Debug Monitor Handler        */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* PendSV Handler               */
	      .long   dummy_handler           /* SysTick Handler              */

	      /* External Interrupts */
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO even handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO odd handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler

	      .section .text

	/////////////////////////////////////////////////////////////////////////////
	//
	// Reset handler
  // The CPU will start executing here after a reset
	//
	/////////////////////////////////////////////////////////////////////////////

	      .globl  _reset
	      .type   _reset, %function
        .thumb_func
_reset: 
	// start gpioklokke
	ldr r4, =CMU_BASE
	ldr r5, [r4, #CMU_HFPERCLKEN0]

	mov r6, #1
	lsl r6, r6, #CMU_HFPERCLKEN0_GPIO
	orr r5, r5, r6

	str r5, [r4, #CMU_HFPERCLKEN0]

	// sett til high drive
	mov r1, #1
	ldr r2, =GPIO_PA_BASE
	str r1, [r2, #GPIO_CTRL]

	// sett output på pins 8-15
	ldr r3, =0x55555555
	str r3, [r2, #GPIO_MODEH]

	// skriv ledverdier til bla
	// testfor lys
	//ldr r6, =0xff00
	ldr r6, =0b1011010100000000
	str r6, [r2, #GPIO_DOUT]

	// setup for knapper
	ldr r6, =0x33333333
	ldr r3, =GPIO_PC_BASE
	str r6, [r3, #GPIO_MODEL]
	// sett internal pull-up
	ldr r6, =0xff
	str r6, [r3, #GPIO_DOUT]
	ldr r10, =0x0400
	str r10, [r2, #GPIO_DOUT]
	b main_loop

main_loop:

	ldr r7, [r3, #GPIO_DIN]

	cmp r7, 0b11111110
	beq ill_led_1

	cmp r7, 0b11111101
	beq ill_led_2

	cmp r7, 0b11111011
	beq ill_led_3

	cmp r7, 0b11110111
	beq ill_led_4

	cmp r7, 0b11101111
	beq ill_led_5

	cmp r7, 0b11011111
	beq ill_led_6

	cmp r7, 0b10111111
	beq ill_led_7

	cmp r7, 0b01111111
	beq ill_led_8	


	cmp r7, 0b11111111
	beq del_all	
	
	b main_loop
	

ill_led_1:
	ldr r11, = 0xFE00
	str r11, [r2, #GPIO_DOUT]

	b main_loop
	
ill_led_2:
	ldr r11, = 0xFD00
	str r11, [r2, #GPIO_DOUT]

	b main_loop

ill_led_3:
	ldr r11, = 0xFB00
	str r11, [r2, #GPIO_DOUT]

	b main_loop

ill_led_4:
	ldr r11, = 0xF700
	str r11, [r2, #GPIO_DOUT]

	b main_loop

ill_led_5:
	ldr r11, = 0xEF00
	str r11, [r2, #GPIO_DOUT]

	b main_loop

ill_led_6:
	ldr r11, = 0xDF00
	str r11, [r2, #GPIO_DOUT]

	b main_loop

ill_led_7:
	ldr r11, = 0xBF00
	str r11, [r2, #GPIO_DOUT]

	b main_loop

ill_led_8:
	ldr r11, = 0x7F00
	str r11, [r2, #GPIO_DOUT]

	b main_loop


del_all:
	ldr r11, = 0xFF00
	str r11, [r2, #GPIO_DOUT]

	b main_loop


	

	/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  

	      b .  // do nothing
	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

	.thumb_func
Setup:
	



.section .data
vars:
	.word 0x2 // 0x2
	.word 0x55555555 //

