//*********************************************
// MikroDes Systems	Copyright (c) 2011
//
// Program to illustrate Semaphore...
// This program uses two tasks; 
// Task0 (high priority) and  
// Task1 (low priority) 
// There is one semaphore.
// One of the task acquires the semaphore
// and starts flashing an LED. The semaphore
// is released when the flashing of LEDis over
// Same thing is done by the other task.
// The messages are displayed on LCD as well
// as on UART0 port.
//*********************************************

#include "config.h"
#include "stdlib.h"

#define	TaskStkLengh	64				//Define the Task0 stack length 
 
OS_STK	TaskStk0 [TaskStkLengh];		//Define the Task0 stack 
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task0 stack 

void 	Task0(void *pdata);				// Task0 
void 	Task1(void *pdata);				// Task1  


OS_EVENT   *MySem;           
unsigned char err;

/**********************************************************
	main()
**********************************************************/
int main (void)
{   
	LED_Init();
	lcd_init();
	UART0_Init();
	UART0_SendData("\n\r****************************\n\r");
	UART0_SendData    ("*Program for semaphore demo*\n\r");
	UART0_SendData    ("****************************\n\r");


	TargetInit();	
	OSInit ();
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
	int i;
	pdata = pdata;						        /* Dummy data */
	while(1)
	{		 
		UART0_SendData("\n\rTask 0 waiting for Semaphore");

		lcd_command(0x80);
		LCD_SendData("                ");
		lcd_command(0x80);
		LCD_SendData("Task 0 waiting");

		OSSemPend(MySem, 0, &err);

		UART0_SendData("\n\rTask 0 got the Semaphore");
		UART0_SendData("\n\rTask 0 now flashing LED-0 for 15 times");

		lcd_command(0x80);
		LCD_SendData("                ");
		lcd_command(0x80);
		LCD_SendData("Task 0 got sem");

		for(i=0; i<15;i++)
		{
			LED_on(0);
			OSTimeDly(10);
			LED_off(0);
			OSTimeDly(10);
		}

		UART0_SendData("\n\rTask 0 released Semaphore \n\r");
		lcd_command(0x80);
		LCD_SendData("               ");
		lcd_command(0x80);
		LCD_SendData("Task 0 released");

		OSSemPost(MySem);
		OSTimeDly(150);
	}
}

void Task1	(void *pdata)
{
	int i;
	pdata = pdata;						        /* Dummy data */
	
	while (1)
	{	
		UART0_SendData("\n\rTask 1 waiting for Semaphore");

		lcd_command(0xC0);
		LCD_SendData("                ");
		lcd_command(0xC0);
		LCD_SendData("Task 1 waiting");

		OSSemPend(MySem, 0, &err);
		UART0_SendData("\n\rTask 1 got the Semaphore");
		UART0_SendData("\n\rTask 1 now flashing LED-1 for 10 times");

		lcd_command(0xC0);
		LCD_SendData("                ");
		lcd_command(0xC0);
		LCD_SendData("Task 1 got sem");

		for(i=0; i<15;i++)
		{
			LED_on(1);
			OSTimeDly(10);
			LED_off(1);
			OSTimeDly(10);
		}

		UART0_SendData("\n\rTask 1 released Semaphore\n\r");
		lcd_command(0xC0);
		LCD_SendData("               ");
		lcd_command(0xC0);
		LCD_SendData("Task 1 released");

		OSSemPost(MySem);
	}
}
  
/*********************************************************************
                            End Of File
**********************************************************************/
