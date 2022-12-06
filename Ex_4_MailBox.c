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

int main (void)
{   
	LED_init();
	TargetInit();	
	OSInit ();

	// create mail box with no message
	MyMailBox = OSMboxCreate((void*)0); 

	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 6);
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 7);	
			
	OSStart();
	return 0;															
}

void Task0	(void *pdata)
{
	unsigned int c;
	pdata = pdata;						        /* Dummy data */

	while(1)
	{	
		c = 2;		 

		OSMboxPost(MyMailBox, &c); 

		LED_on(0);
		OSTimeDly(5);

		LED_off(0);
		OSTimeDly(100);
	}
}



void Task1	(void *pdata)
{
	int i;
	unsigned int* ptr;
	unsigned int c1;
	pdata = pdata;	
	
	while(1)
	{	
		c1 = 0;	 
		ptr = OSMboxPend(MyMailBox, 0, &err);
		c1 = *ptr;

		for(i=0;i<c1;i++)
		{
			LED_on(1);
			OSTimeDly(10);

			LED_off(1);
			OSTimeDly(10);
		}

		
		OSTimeDly(10);
	}
}


/*********************************************************************
                            End Of File
**********************************************************************/
