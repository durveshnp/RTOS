#include "config.h"
#include "stdlib.h"
#include <stdio.h>

#define	TaskStkLengh	64				//Define the Task0 stack length 
 
OS_STK	TaskStk0 [TaskStkLengh];		//Define the Task stack 
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task stack 
OS_STK	TaskStk2 [TaskStkLengh];		//Define the Task stack 
OS_STK	TaskStk3 [TaskStkLengh];		//Define the Task stack 

void 	Gettime(void *pdata);				
void 	Signal(void *pdata);				  

OS_EVENT *mbox;

uint8 err;
									 
char buffer[25];


int main (void)
{   
	lcd_init();
	LED_init();	
	
	UART0_Init();
	TargetInit();	
	OSInit ();

	mbox = OSMboxCreate((void *)0);

	OSTaskCreate (Gettime,(void *)0, &TaskStk0[TaskStkLengh - 1], 6);
	OSTaskCreate (Signal,(void *)0, &TaskStk1[TaskStkLengh - 1], 7);	

			
	OSStart();
	return 0;															
}


void Gettime (void *pdata)
{
	int time;
	int i = 0;
	pdata = pdata;	
						        /* Dummy data */
	while(1)
	{		 
	
		for(i = 10; i >= 0;i--)
		{
			time = i;
			OSMboxPost(mbox,&time);
			OSTimeDlyHMSM(0,0,1,0);
		}
	

		OSTimeDlyHMSM(0,0,5,0);
	}
}

void Signal	(void *pdata)
{
	int *ptr;
	int time;
	pdata = pdata;		/* Dummy data */


	while(1)
	{		 
		
	   ptr = OSMboxPend(mbox,0,&err);

	   time = *ptr;

	   if(time > 5)
	   {
	   	   LED_on(0);
		   LED_off(1);
		   LED_off(2);
		   UART0_SendData("STOP... \r\n\n");
		   LCD_SendData("    STOP......");
		   LCD_clear();
	   }
	   else if (time == 0)
	   {
			LED_on(2);
			LED_off(1);
		   	LED_off(0);
			UART0_SendData("Go... \r\n\n");
			LCD_SendData("    Go......");
			LCD_clear();
			
	   }
	   else
	   {
	   		LED_on(1);
			LED_off(0);
		    LED_off(2);
			UART0_SendData("Be Ready...  \r\n\n");
			LCD_SendData("    Be Ready...");
			LCD_clear();
	   }

	   OSTimeDly(10);
	   
		
	}
}

