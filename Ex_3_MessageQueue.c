//*********************************************
// MikroDes Systems	Copyright (c) 2011
//
// Program to illustrate Message Queue...
// This program uses 2 tasks;  Task 0, 1
// Task0 takes input from 4x4 matrix kayboard
// and displays the key on LCD as well as serial port
// Task1 switches relay on/off at regular interval
// Task2 flashes LED2 and Taks3 flashes LED3.

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
// Task0 key = 
// Press key on matrix keyboard on kit. it will be shown
// on terminal. 
// Also the relay will be seen toggling and LEDs flashing.

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


OS_EVENT* MsgQueue;
#define SIZE_OF_Q 2
void* MessageStorage[SIZE_OF_Q];

uint8 err;

OS_EVENT* MySem;
uint8 err1;


// Required for semnding time to serial port
char msg_1[25];
char msg_2[25];

/**********************************************************
	main()
**********************************************************/
int main (void)
{   
	LED_init();
	kbd_init();
	lcd_init();
	relay_init();

	UART0_Init();
	UART0_SendData("\r\n*************************************\r\n");
	UART0_SendData    ("*    Program for demo of 4 tasks    *\r\n");
	UART0_SendData    ("*************************************\r\n");

	TargetInit();	
	OSInit ();

	// Create a Queue, Attach it to message storage are
	MsgQueue = OSQCreate(MessageStorage,SIZE_OF_Q);
    MySem = OSSemCreate(1);

	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 6);
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 7);	
			
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
		OSSemPend(MySem, 0, &err1);
		
		sprintf(msg_1,"Hello World");
		OSQPost(MsgQueue, msg_1);

		LED_on(0);
		OSTimeDly(1);

		LED_off(0);
		OSTimeDly(10);
		
		OSSemPost(MySem);
	}
}

void Task1	(void *pdata)
{
	char* ptr_c;	
	pdata = pdata;						        /* Dummy data */

	while(1)
	{
		// wait for semaphore
		OSSemPend(MySem, 0, &err1);

		// message received
		// Display it on LCD
		lcd_command(0x01);
		OSTimeDly(3);
		ptr_c = OSQPend(MsgQueue,0, &err); 		
		LCD_SendData(ptr_c);	 		
	 	
		// Release the semaphore	
		OSSemPost(MySem);
	}
}

/*********************************************************************
                            End Of File
**********************************************************************/
