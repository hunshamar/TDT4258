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

	// start GPIO clock
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

	// sett output on pins 8-15
	ldr r3, =0x55555555
	str r3, [r2, #GPIO_MODEH]


	// setup for buttons
	ldr r6, =0x33333333
	ldr r3, =GPIO_PC_BASE
	str r6, [r3, #GPIO_MODEL]
	// sett internal pull-up

	ldr r6, =0xff
	str r6, [r3, #GPIO_DOUT]
	ldr r10, =0x0400
	str r10, [r2, #GPIO_DOUT]


    // setup interupt controller
    //ISERO
    ldr r7, =0x802
    ldr r8, =ISER0
    str r7, [r8]

	// sett GPIO interupts
	ldr r7, =0x22222222
	ldr r8, =GPIO_BASE
	str r7, [r8, #GPIO_EXTIPSELL]


	// sett 1->0 transition
	ldr r7, =0xff
	str r7, [r8, #GPIO_EXTIFALL]

	// sett 0->1 transtion
	str r7, [r8, #GPIO_EXTIRISE]

	// enable interupt generation
	str r7, [r8, #GPIO_IEN]




	b top
	// b top


top:
	// Write 6 to SCR register to enable low energy mode 2
	ldr r11, =0x6
	ldr r12, =SCR
	str r11, [r12]

	//Run wfi function
	wfi

	

	/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  

	// clear the GPIO_IFC Register
	ldr r9, =GPIO_BASE
	ldr r10, [r9, #GPIO_IF]
	str r10, [r9, #GPIO_IFC]

	// read buttonstatus

	ldr r10, [r3, #GPIO_DIN]
	lsl r10, r10, #8
	str r10, [r2, #GPIO_DOUT]



	bx r14

	      b .  // do nothing
	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing
	
