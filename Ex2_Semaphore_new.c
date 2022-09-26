//**************************************************
// MikroDes Systems	Copyright (c) 2011
// www.mikrodes.com
//**************************************************

// This program illustrates the concept of 
// Semaphore...
// Works on MD2148 ARM7 kit

// The program uses two tasks; 
// Task0 (high priority) and Task1 (low priority) 
// There is one semaphore used to access
// the common resource (8 LEDs)
// Task0 acquires the semaphore
// and shows running LED effect on LED0 to LED3. 
// The semaphore is then released.
// When Task1 gets the semaphore, it flashes
// LED4-LED7 once and then releases the semaphore

// Procedure:
// Build the project. Open the "output" folder. 
// Double click on download.fms file.
// Flash magic will start with all basic settings.
// Change the COM port setting if rquired.
// Click on start (on flash magic).
// Download will start. After the download is complete,
// The program will start executing in the kit and 
// LEDs will be seen activated as per the logic explained
// earlier.

// Observe that at a time only one task is controlling LEDs.
// because at a time only one task has the semaphore.
// Alter the program for different OSTimeDly times
// and repeat the procedure.

// Think of what will happen if the same 
// functionality is	implemented without using semaphore.
// Modify the program and observe the output.
//***************************************************

#include "config.h"
#include "stdlib.h"

#define	TaskStkLengh	64				//Define the Task0 stack length 
 
OS_STK	TaskStk0 [TaskStkLengh];		//Define the Task0 stack 
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task0 stack 

void 	Task0(void *pdata);				// Task0 
void 	Task1(void *pdata);				// Task1  

// necessary for semaphore
OS_EVENT*   MySem;           
unsigned char err;

char buffer[25];

/**********************************************************
	main()
**********************************************************/
int main (void)
{   
	LED_init();
	TargetInit();	
	OSInit ();
	MySem = OSSemCreate(1);			
	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 6);
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 8);	
			
	OSStart();
	return 0;															
}
/**********************************************************
**                            Task0 
**********************************************************/

void Task0	(void *pdata)
{
	pdata = pdata;		/* Dummy data */
	while(1)
	{	
		// wait till semaphore is available	 
		OSSemPend(MySem, 0, &err);

		// Now semaphore is available
		// So the task does its work
		LED_on(0);
		OSTimeDly(3);
		LED_off(0);

		LED_on(1);
		OSTimeDly(3);
		LED_off(1);

		LED_on(2);
		OSTimeDly(3);
		LED_off(2);

		LED_on(3);
		OSTimeDly(3);
		LED_off(3);

		// Semaphore released
		OSSemPost(MySem);
	}
}

void Task1	(void *pdata)
{
	pdata = pdata;			/* Dummy data */
	
	while (1)
	{	
		// wait till semaphore is available	 
		OSSemPend(MySem, 0, &err);

		// Now semaphore is available
		// So the task does its work
		OSTimeDly(10);

		LED_on(4);
		LED_on(5);
		LED_on(6);
		LED_on(7);

		OSTimeDly(10);

		LED_off(4);
		LED_off(5);
		LED_off(6);
		LED_off(7);

		OSTimeDly(10);

		// Semaphore released
		OSSemPost(MySem);
	}
}
  
/********************************************
             End Of File
*********************************************/
