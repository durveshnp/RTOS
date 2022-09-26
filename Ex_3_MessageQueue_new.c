//**************************************************
// MikroDes Systems	Copyright (c) 2011
// www.mikrodes.com
//**************************************************

// This program illustrates the concept of 
// Message queue...
// Works on MD2148 ARM7 kit

// This program uses 2 tasks;  Task 0, 1
// Task0 posts a two messages alternately

// Task1 receives message and displays it on LCD

// Procedure:
// Build the project. Open the "output" folder. 
// Double click on download.fms file.
// Flash magic will start with all basic settings.
// Change the COM port setting if rquired.
// Click on start (on flash magic).
// Download will start. After the download is complete,
// the user program will run. The LCD will show
// the received messages.
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

#define SIZE_OF_Q 5
// This is the actual queue
void* MessageStorage[SIZE_OF_Q];

uint8 err;

// Array for storing the message
char msg_1[25];
/**********************************************************
	main()
**********************************************************/
int main (void)
{   
	lcd_init();

	TargetInit();	
	OSInit ();

	// Create a Queue, Attach it to message storage are
	MsgQueue = OSQCreate(MessageStorage,SIZE_OF_Q);

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

	pdata = pdata;						        /* Dummy data */

	while(1)
	{	
		sprintf(msg_1,"Hello");
		OSQPost(MsgQueue, msg_1);
		OSTimeDly(10);

		sprintf(msg_1,"World");
		OSQPost(MsgQueue, msg_1);
		OSTimeDly(10);
	}
}

void Task1	(void *pdata)
{
	char* ptr_c;	
	pdata = pdata;						        /* Dummy data */

	while(1)
	{
		// wait for message from queue
		ptr_c = OSQPend(MsgQueue,0, &err); 
		
		// message received, display it on LCD 		
		lcd_command(0x01);
		LCD_SendData(ptr_c);	 		
		OSTimeDly(1);	 		
	}
}

/*********************************************************************
                            End Of File
**********************************************************************/
