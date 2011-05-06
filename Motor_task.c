#include "User_task.h"
#include "LPC214x.h"
void Execute_Motor_Task(void)
{
	volatile int j;
	
	PINSEL0 = 0x0000000;
	
	IODIR0 = 0x80000000;
	IOSET0 = 0x80000000;
	
	for (j = 0; j < 500000; j++ );
	
	IOCLR0 = 0x80000000;
	for (j = 0; j < 500000; j++ );
	
}
	
	
