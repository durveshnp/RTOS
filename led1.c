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

OS_EVENT *psem;
uint8 err;

int main (void)
{   
	LED_init();
	UART0_Init();
	TargetInit();	
	OSInit ();

	psem = OSSemCreate(1);

	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 6);
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 7);	
//	OSTaskCreate (Task2,(void *)0, &TaskStk2[TaskStkLengh - 1], 8);	
//	OSTaskCreate (Task3,(void *)0, &TaskStk3[TaskStkLengh - 1], 9);	
			
	OSStart();
	return 0;															
}

void myDelay()
{
	unsigned int i;
	for(i=0;i<60000;i++);
}

void Task0	(void *pdata)
{
	
	pdata = pdata;						        /* Dummy data */
	OSTimeDly(30);
	while(1)
	{		
		//OSSemPend(psem,0,&err);
		LED_on(0);	
		//OSTimeDly(30);
		myDelay();
		LED_off(0);
		//OSSemPost(psem);	
		//OSTimeDly(30);
		myDelay();
	}
}
void Task1	(void *pdata)
{

	pdata = pdata;						        /* Dummy data */
	
	while(1)
	{		
		//OSSemPend(psem,0,&err);
		LED_on(1);	
		//OSTimeDly(30);
		myDelay();
		LED_off(1);
		//OSSemPost(psem);	
		//OSTimeDly(30);
		myDelay();
	}
}

/*
void Task2	(void *pdata)
{
	pdata = pdata;						        

	while(1)
	{	

		LED_on(2);	
		OSTimeDly(2);


		LED_off(2);	
		OSTimeDly(2);

	}
}
	*/

  /*
void Task3	(void *pdata)
{
	pdata = pdata;						        

	while(1)
	{		
		
		LED_on(3);	
		OSTimeDly(3);

		LED_off(3);	
		OSTimeDly(3);

	}
}

	   */
