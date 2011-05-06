#include "User_task.h"
#include "LPC214x.h"
void Execute_Led_Task(void)
{
	volatile int j;
	
	IODIR0 |= 0x00000c00;	// P0.10 & P0.11 output
	IOSET0 =  0x00000c00;
	
	for (j = 0; j < 500000; j++ );		// wait 500 msec
	IOSET0 = 0x00000800;
	IOCLR0 = 0x00000400;	
	for (j = 0; j < 500000; j++ );		// wait 500 msec
	IOSET0 = 0x00000400;
	IOCLR0 = 0x00000800;
	
}

