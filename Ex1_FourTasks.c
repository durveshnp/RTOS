//*********************************************
// MikroDes Systems	Copyright (c) 2011
//
// Program to illustrate Four tasks...
// This program uses 4 tasks;  Task 0, 1, 2, 3
// Each task flashes a separate LED	at different rates.

// Procedure:
// Build the project. Open the "output" folder. 
// Double click on download.fms file.
// Flash magic will start with all basic settings.
// Change the COM port setting if rquired.
// Click on start (on flash magic).
// Download will start. After the download is complete,
// The program will start executing in the kit and 
// LEDs will be seen flashing.
// Now, start the MikroDes Terminal Program.
// Set the COM port and set the baud rate to 57600.
// Click on Open port. The kit will get reset and 
// The program will show the messages on the terminal
// about which LED is ON/OFF at what time.
// After some time, click on Close port.
// Select all the output messages and paste them in 
// any new text file (in notepad)
// Take a graph paper and plot the LED on/OFF states
// for all LEDs. Check if the waveform is as per the 
// program.
// Alter the program for different ON/OFF times
// and repeat the procedure.
//*********************************************

#include "config.h"
#include "stdlib.h"
#include <stdio.h>

#define	TaskStkLengh	64				//Define the Task0 stack length 
 
OS_STK	TaskStk0 [TaskStkLengh];		//Define the Task stack 
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task stack 
OS_STK	TaskStk2 [TaskStkLengh];		//Define the Task stack 
OS_STK	TaskStk3 [TaskStkLengh];		//Define the Task stack 

void 	Task0(void *pdata);				
void 	Task1(void *pdata);				  
void 	Task2(void *pdata);				  
void 	Task3(void *pdata);				  

// Required for semnding time to serial port
char buffer[25];
/**********************************************************
	main()
**********************************************************/
int main (void)
{   
	LED_init();

	UART0_Init();
	UART0_SendData("\r\n*************************************\r\n");
	UART0_SendData    ("*    Program for demo of 4 tasks    *\r\n");
	UART0_SendData    ("*************************************\r\n");

	TargetInit();	
	OSInit ();

	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 6);
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 7);	
	OSTaskCreate (Task2,(void *)0, &TaskStk2[TaskStkLengh - 1], 8);	
	OSTaskCreate (Task3,(void *)0, &TaskStk3[TaskStkLengh - 1], 9);	
			
	OSStart();
	return 0;															
}
/**********************************************************
**                            Task0 
**********************************************************/

void Task0	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */

	while(1)
	{		 
		UART0_SendData("\r\nTask0 made LED0 ON  at time ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		LED_on(0);
		OSTimeDly(10);

		UART0_SendData("\r\nTask0 made LED0 OFF  at time ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		LED_off(0);
		OSTimeDly(10);
	}
}

void Task1	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */

	while(1)
	{		 
		UART0_SendData("\r\nTask1 made LED1 ON  at time ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		LED_on(1);
		OSTimeDly(15);

		UART0_SendData("\r\nTask1 made LED1 OFF  at time ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		LED_off(0);
		OSTimeDly(15);
	}
}

void Task2	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */

	while(1)
	{		 
		UART0_SendData("\r\nTask2 made LED2 ON  at time ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		LED_on(2);
		OSTimeDly(20);

		UART0_SendData("\r\nTask2 made LED2 OFF  at time ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		LED_off(2);
		OSTimeDly(20);
	}
}

void Task3	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */

	while(1)
	{		 
		UART0_SendData("\r\nTask3 made LED3 ON  at time ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		LED_on(3);
		OSTimeDly(25);

		UART0_SendData("\r\nTask3 made LED3 OFF  at time ");
		sprintf(buffer,"%d", OSTimeGet());
		UART0_SendData(buffer);

		LED_off(3);
		OSTimeDly(25);
	}
}
/*********************************************************************
                            End Of File
**********************************************************************/
