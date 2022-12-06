//*********************************************
// MikroDes Systems	Copyright (c) 2011
//
// Program to illustrate Four tasks...
// This program uses 4 tasks;  Task 0, 1, 2, 3
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

// Required for semnding time to serial port
char buffer[25];
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
	unsigned int c;

	pdata = pdata;						        /* Dummy data */

	lcd_command(0x80);
	LCD_SendData("                ");
	lcd_command(0x80);
	LCD_SendData("Task 0 key = ");


	while(1)
	{	
		// Display string on serial port UART0
		UART0_SendData("\r\nTask0 key = ");
		// Wait for key press on 4x4 matrix keypad		 
		c = get_key();
		// store key as string in the buffer 		 
		sprintf(buffer,"%c", c);
		// Display the key on serial port
		UART0_SendData(buffer);

		// Place the cursor at home position
		lcd_command(0x80);
		// Clear line 1
		LCD_SendData("                ");
		// Place the cursor at home position
		lcd_command(0x80);
		// Display the message and key on LCD
		LCD_SendData("Task 0 key = ");
		LCD_SendData(buffer);

		// LED0 on-off code	(on P0.4)
		LED_on(0);
		OSTimeDly(1);
		LED_off(0);
		OSTimeDly(1);
	}
}

void Task1	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */

	while(1)
	{		 
		LED_on(0);
		OSTimeDly(20);

		LED_off(0);
		OSTimeDly(20);
	}
}

void Task2	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */

	while(1)
	{		 
		relay_on(1);
		OSTimeDly(5);

		relay_off(1);
		OSTimeDly(30);
	}
}

void Task3	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */

	while(1)
	{	
		relay_on(0);
		OSTimeDly(10);

		LED_off(0);
		OSTimeDly(10);
	}
}
/*********************************************************************
                            End Of File
**********************************************************************/
