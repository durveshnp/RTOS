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
			  


//pointer to semaphore

//OS_EVENT* ptr_Sem_LED0;
//OS_EVENT* ptr_Sem_LED1;

OS_EVENT* ptr_Sem_UART0;

//variable for storing error

uint8 err;


int main (void)
{   
	LED_init();
	//UART0_Init();


	TargetInit();	
	OSInit ();

//	ptr_Sem_LED0 = OSSemCreate(1);
//	ptr_Sem_LED1 = OSSemCreate(1);

	ptr_Sem_UART0 = OSSemCreate(1);

	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 6);
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 7);	
	//OSTaskCreate (Task2,(void *)0, &TaskStk2[TaskStkLengh - 1], 8);	
	//OSTaskCreate (Task3,(void *)0, &TaskStk3[TaskStkLengh - 1], 9);	
			
	OSStart();
	return 0;															
}


void Task0	(void *pdata)
{
	unsigned int i;
	pdata = pdata;						        /* Dummy data */

	while(1)
	{		

		// wait for semaphore to be available

		OSSemPend(ptr_Sem_UART0,0,&err);

		UART0_SendData("**	Durvesh Patil \r\n");

		

		   
		for(i=0;i<4;i++)
		{
			LED_on(0);	// All LEDs on
			OSTimeDly(3);
			LED_off(0);
			OSTimeDly(3);
		}
			 

		OSSemPost(ptr_Sem_UART0);
		OSTimeDly(1);

	}
}
void Task1	(void *pdata)
{
	unsigned int i;
	pdata = pdata;						        /* Dummy data */
	
	while(1)
	{		
		OSSemPend(ptr_Sem_UART0,0,&err);
		UART0_SendData("**	2019BTEEN00035 \r\n");
		 
		for(i=0;i<2;i++)
		{
			LED_on(0);	// All LEDs on
			OSTimeDly(1);
			LED_off(0);
			OSTimeDly(1);
		}  

		OSSemPost(ptr_Sem_UART0);
		OSTimeDly(1);

	}
}

 /*

void Task2	(void *pdata)
{
	unsigned int i;
	pdata = pdata;						       

	while(1)
	{		 
		OSSemPend(ptr_Sem_UART0,0,&err);
		UART0_SendData("**	2019BTEEN00035 \r\n");
	
		OSSemPost(ptr_Sem_UART0);
		OSTimeDly(3);

	}

}


void Task3	(void *pdata)
{
	unsigned int i;
	pdata = pdata;						        

	while(1)
	{		 
		OSSemPend(ptr_Sem_UART0,0,&err);
		UART0_SendData("**	B.Tech Electronics \r\n");
	
		OSSemPost(ptr_Sem_UART0);
		OSTimeDly(3);
	}
}

*/
