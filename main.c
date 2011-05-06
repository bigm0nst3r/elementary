
void Initialize(void);
void feed(void);
void set_timer(void);

void IRQ_Routine (void)   __attribute__ ((interrupt("IRQ")));
void FIQ_Routine (void)   __attribute__ ((interrupt("FIQ")));
void SWI_Routine (void)   __attribute__ ((interrupt("SWI")));
void UNDEF_Routine (void) __attribute__ ((interrupt("UNDEF")));

volatile int task_no = 0;
volatile int new_task_no;


/**********************************************************
                  Header files
 **********************************************************/
#include "LPC214x.h"
#include "VIClowlevel.h"
#include "task.h"
#include "User_task.h"

/**********************************************************
                       MAIN
**********************************************************/

int	main (void) {
	
	// Initialize the system
	Initialize();	
	
	
	
	scheduler_init("led_task",0);
	scheduler_init("motor_task",1);
	set_timer();
	enableIRQ();
	Execute_Led_Task();
	while(1);
	
}



/**********************************************************
                      Initialize
**********************************************************/

#define PLOCK 0x400

void Initialize(void)  {

   
	// Setting Multiplier and Divider values
  	PLLCFG=0x23;
  	feed();
  
	// Enabling the PLL */	
	PLLCON=0x1;
	feed();
  
	// Wait for the PLL to lock to set frequency
	while(!(PLLSTAT & PLOCK)) ;
  
	// ConnectT0TCR = 0x02;
	T0IR = 0xff;
	T0MCR = 0x003;
	T0MR0 = 0x3938700;
	
	VICVectCntl0 = 0x00000024;
	VICVectAddr0 = (unsigned)IRQ_Routine;
	VICIntEnable = 0x00000010;
	
	T0TCR = 0x01; 
	PLLCON=0x3;
	feed();
  
	// Enabling MAM and setting number of clocks used for Flash memory fetch (4 cclks in this case)
	MAMCR=0x2;
	MAMTIM=0x4;
  
	// Setting peripheral Clock (pclk) to System Clock (cclk)
	VPBDIV=0x1;

}

void set_timer(void)
{
	T0TCR = 0x02;
	T0IR = 0xff;
	T0MCR = 0x003;
	T0MR0 = 0x3938700;
	
	VICVectCntl0 = 0x00000024;
	VICVectAddr0 = (unsigned)IRQ_Routine;
	VICIntEnable = 0x00000010;
	
	T0TCR = 0x01;	
}


void feed(void)
{
  PLLFEED=0xAA;
  PLLFEED=0x55;
}


void IRQ_Routine (void) {
	//disableIRQ();
	task_no = context_switch(task_no);
	//enableIRQ();
	if(task_no == 0){
		Execute_Led_Task();
		
	
	}
	else{
		Execute_Motor_Task();
	}
	T0IR = 0x01;
	VICVectAddr = 0;
}
		
void FIQ_Routine (void)  {
	while (1) ;	
}


void SWI_Routine (void)  {
	while (1) ;	
}


void UNDEF_Routine (void) {
	while (1) ;	
}










