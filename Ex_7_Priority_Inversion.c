//*********************************************
// MikroDes Systems	Copyright (c) 2011
//
// Program to illustrate Priority inversion...
// This program uses three tasks; 
// TaskH (high priority) and  
// TaskM (middle priority) 
// TaskL (low priority) 

// There is one semaphore (Shared resource)
// TaskH wants the shared resource at time 20 (ticks)
// TaskL wants the shared resource at time 5 (ticks)
// TaskM starts its work at time 10 and continues to 30 ticks
// The messages are displayed on LCD as well
// as on UART0 port.
//*********************************************

#include "config.h"
#include "stdlib.h"
#include <stdio.h>

#define	TaskStkLengh	64			//Define the Task0 stack length 
 
OS_STK	TaskStkH [TaskStkLengh];	//Define the Task stack 
OS_STK	TaskStkM [TaskStkLengh];	//Define the Task stack 
OS_STK	TaskStkL [TaskStkLengh];	//Define the Task stack 

void 	TaskH(void *pdata);				
void 	TaskM(void *pdata);				  
void 	TaskL(void *pdata);				  


OS_EVENT   *MySem; // shared resource           
unsigned char err;

char buffer[25];
/**********************************************************
	main()
**********************************************************/
int main (void)
{   
	LED_init();
	lcd_init();
	UART0_Init();
	UART0_SendData("\r\n*************************************\r\n");
	UART0_SendData    ("*Program for Priority Inversion demo*\r\n");
	UART0_SendData    ("*************************************\r\n");


	TargetInit();	
	OSInit ();
	MySem = OSSemCreate(1);			
	OSTaskCreate (TaskH,(void *)0, &TaskStkH[TaskStkLengh - 1], 6);
	OSTaskCreate (TaskM,(void *)0, &TaskStkM[TaskStkLengh - 1], 8);	
	OSTaskCreate (TaskL,(void *)0, &TaskStkL[TaskStkLengh - 1], 10);	
			
	OSStart();
	return 0;															
}
/**********************************************************
                            Task0 
**********************************************************/

void TaskH	(void *pdata)
{
	int i=10;
	pdata = pdata;						        /* Dummy data */

	OSTimeDly(50);
	while(1)
	{		 
		UART0_SendData("\r\nTask-H waiting for Semaphore at time ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		OSSemPend(MySem, 0, &err);

		UART0_SendData("\r\nTask-H got the Semaphore at ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		for(i=0; i<7;i++)
		{
			LED_on(0);
			OSTimeDly(10);
			LED_off(0);
			OSTimeDly(10);
		}

		UART0_SendData("\r\nTask-H released the Semaphore at ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		OSSemPost(MySem);
		OSTimeDly(150);
	}
}

void TaskM	(void *pdata)
{
	int i;
	pdata = pdata;						        /* Dummy data */
		
	OSTimeDly(30);

	while (1)
	{	
		UART0_SendData("\r\nTask-M started at ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		for(i=0; i<5;i++)
		{
			LED_on(1);
			delay_200_msec();
			delay_200_msec();
			delay_200_msec();
			delay_200_msec();

			LED_off(1);
			delay_200_msec();
			delay_200_msec();
			delay_200_msec();
			delay_200_msec();
		}

		UART0_SendData("\r\nTask-M finished at ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		OSTimeDly(100);
	}
}

void TaskL	(void *pdata)
{
	int i;
	pdata = pdata;						        /* Dummy data */
	
	while (1)
	{	
		UART0_SendData("\r\nTask-L waiting for Semaphore");

		OSSemPend(MySem, 0, &err);
		UART0_SendData("\r\nTask-L got the Semaphore at ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		for(i=0; i<4;i++)
		{
			LED_on(2);
			OSTimeDly(10);
			LED_off(2);
			OSTimeDly(10);
		}

		UART0_SendData("\r\nTask-L released Semaphore at ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		OSSemPost(MySem);
	}
}  
/*********************************************************************
                            End Of File
**********************************************************************/
