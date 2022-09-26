//*********************************************
// MikroDes Systems	Copyright (c) 2011
//
// Program to illustrate Four tasks...
// This program uses 2 tasks;  Task 0, 1
// Task0 takes input from 4x4 matrix kayboard
// and writes it to mailbox
// Task1 reads the mailbox and displays the key

// Procedure:
// Build the project. Open the "output" folder. 
// Double click on download.fms file.
// Flash magic will start with all basic settings.
// Change the COM port setting if rquired.
// Click on start (on flash magic).
// Download will start. After the download is complete,
// The program will start executing.
// Press any key on 4x4 matrix keyboard
// The program will show the messages on LCD
// Task0 key = <keynumber>
// This shows how mailbox can be used to send data
// from one task to the other
//*********************************************

#include "config.h"
#include "stdlib.h"
#include <stdio.h>

#define	TaskStkLengh	64				//Define the Task0 stack length 
 
OS_STK	TaskStk0 [TaskStkLengh];		//Define the Task stack 
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task stack 

void 	Task0(void *pdata);				
void 	Task1(void *pdata);				  

OS_EVENT *MyMailBox;	// mail box
uint8 err;

// Required for semnding time to serial port
char buffer[25];
/**********************************************************
	main()
**********************************************************/
int main (void)
{   
	LED_init();
	//kbd_init();
	//lcd_init();
	//relay_init();
	//UART0_Init();

	//UART0_SendData("\r\n*************************************\r\n");
	//UART0_SendData    ("*    Program for demo of Mailbox    *\r\n");
	//UART0_SendData    ("*************************************\r\n");

	TargetInit();	
	OSInit ();

	// create mail box with no message
	MyMailBox = OSMboxCreate((void*)0); 

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
	unsigned int c;
	pdata = pdata;						        /* Dummy data */

	while(1)
	{	
		c = 3;		 

		OSMboxPost(MyMailBox, &c); 

		LED_on(0);
		OSTimeDly(1);

		LED_off(0);
		OSTimeDly(20);
	}
}



void Task1	(void *pdata)
{
	//unsigned int* ptr;
	int i;
	unsigned int* ptr;
	unsigned int c1;
	pdata = pdata;	
	
						        /* Dummy data */

	//lcd_command(0x80);
	//LCD_SendData("Press any key      ");


	while(1)
	{	
		c1 = 0;	 
		ptr = OSMboxPend(MyMailBox, 0, &err);
		c1 = *ptr;

		//sprintf(buffer,"%c", *ptr);

		for(i=0;i<c1;i++)
		{
			LED_on(1);
			OSTimeDly(1);

			LED_off(1);
			OSTimeDly(1);
		}

		//lcd_command(0x80);
		//LCD_SendData("                ");
		//lcd_command(0x80);
		//LCD_SendData("Task 0 key = ");
		//LCD_SendData(buffer);

		//LED_on(1);
		//OSTimeDly(1);

		//LED_off(1);
		OSTimeDly(4);
	}
}


/*********************************************************************
                            End Of File
**********************************************************************/
