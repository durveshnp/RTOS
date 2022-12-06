#include "config.h"
#include "stdlib.h"
#include <stdio.h>

#define	TaskStkLengh	64				//Define the Task0 stack length 
 
OS_STK	TaskStk0 [TaskStkLengh];		//Define the Task stack 
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task stack 
//OS_STK	TaskStk2 [TaskStkLengh];		//Define the Task stack 
//OS_STK	TaskStk3 [TaskStkLengh];		//Define the Task stack 

void 	Task0(void *pdata);				
void 	Task1(void *pdata);				  
//void 	Task2(void *pdata);				  
//void 	Task3(void *pdata);	

//Prototype of interrupt initialization function 
void irq_init(void);
// Prototype of interrupt service routine 1 
void isr_int1(void)__irq;
//Prototype of interrupt service routine 2 
void isr_int2(void)__irq;

//1. Create a pointer to store the address of semaphore necessary for semaphore 
OS_EVENT* pTask0EventSync;
unsigned char err;	
OS_EVENT* pTask1EventSync;
unsigned char err1;		  

char buffer[25];

int main (void)
{   
	LED_init();
	
	TargetInit();	
	OSInit ();
	irq_init();

	//Tell the OS to create semaphore and get the address and store it in the created pointer Argument indicates initial state(1:available , 0: not available )

	pTask0EventSync = OSSemCreate(0);
	pTask1EventSync = OSSemCreate(0);

	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 6);
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 7);	
//	OSTaskCreate (Task2,(void *)0, &TaskStk2[TaskStkLengh - 1], 8);	
//	OSTaskCreate (Task3,(void *)0, &TaskStk3[TaskStkLengh - 1], 9);	
			
	OSStart();
	return 0;															
}
void Task0	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */
	
	while(1)
	{	
		OSSemPend(pTask0EventSync,0,&err);
		LED_on(0);	// All LEDs on
	    OSTimeDly(4);


		LED_off(0);	// All LEDs off
		OSTimeDly(4);
		LED_on(0);	// All LEDs on
	    OSTimeDly(4);


		LED_off(0);	// All LEDs off
		OSTimeDly(4);
	}
}
void Task1	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */

	while(1)
	{		 
		OSSemPend(pTask1EventSync,0,&err1);
		LED_on(1);	// All LEDs on
		

	    OSTimeDly(4);
		LED_off(1);	// All LEDs off
	   
		OSTimeDly(4);
	}
}
void Task2	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */

	while(1)
	{		 
		LED_on(2);	// All LEDs on
		OSTimeDly(4);

		LED_off(2);	// All LEDs off
		OSTimeDly(4);
	}
}
void Task3	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */

	while(1)
	{		 
		LED_on(3);	// All LEDs on
		OSTimeDly(4);

		LED_off(3);	// All LEDs off
		OSTimeDly(4);
	}
}
//ISR of Ext int 1.
// p0.3 used as interrupt pin
char flag=0;
void isr_int1(void)__irq
{
	OSSemPost(pTask0EventSync);	
	   //clear the flag
	EXTINT = 0x00000002;
	VICVectAddr= 0x0;
}
//ISR of Ext int 2.
// p0.15 used EINT2
void isr_int2(void)__irq
{
	//write OSSempost for other semaphore 
	OSSemPost(pTask1EventSync);
	EXTINT = 0x00000004;
	VICVectAddr= 0x0;
}

// P0.3 used as ENT1 (PINSEL:11)
//P0.15 used as EINT2 (PINSEL:10)

void irq_init(void)
{
	//select the EXTINT1 and EXINT2 pins as interrupt 
	PINSEL0 = PINSEL0 & 0x3FFFFF3F	| 0x800000C0;
	//make them as IRQ (15th and 16th bit)
	VICIntSelect = 0x00000000;
	VICVectAddr10 = (unsigned)isr_int1;
	VICVectCntl10 = 0x0000002F;
	VICVectAddr11 = (unsigned)isr_int2;
	VICVectCntl11 = 0x00000030;

	//set the mode to edge triggered 
	EXTMODE = 0x00000006;
	//enable interrupts 
	VICIntEnable = 0x00018000;
}
