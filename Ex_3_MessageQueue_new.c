#include "config.h"
#include "stdlib.h"
#include <stdio.h>

#define	TaskStkLengh	64				//Define the Task0 stack length 
 
OS_STK	TaskStk0 [TaskStkLengh];		//Define the Task stack 
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task stack 
OS_STK	TaskStk2 [TaskStkLengh];		//Define the Task stack 
OS_STK	TaskStk3 [TaskStkLengh];		//Define the Task stack 

void 	T1(void *pdata);				
void 	T2(void *pdata);				  
void 	T3(void *pdata);				  
void 	T4(void *pdata);				  


OS_EVENT* que1;
OS_EVENT* que2;



#define SIZE_OF_Q 15


// This is the actual queue
void* Message1[SIZE_OF_Q];
void* Message2[SIZE_OF_Q];

uint8 err;

// Array for storing the message
char msg_1[25];
char msg_2[25];

/********************
	main()
********************/
int main (void)
{   
	LED_init();
	UART0_Init();

	TargetInit();	
	OSInit ();

	// Create a Queue, Attach it to message storage are
	que1 = OSQCreate(Message1,SIZE_OF_Q);
	que2 = OSQCreate(Message2,SIZE_OF_Q);


	OSTaskCreate (T1,(void *)0, &TaskStk0[TaskStkLengh - 1], 6);
	OSTaskCreate (T2,(void *)0, &TaskStk1[TaskStkLengh - 1], 7);
	OSTaskCreate (T3,(void *)0, &TaskStk2[TaskStkLengh - 1], 8);
	OSTaskCreate (T4,(void *)0, &TaskStk3[TaskStkLengh - 1], 9);	
			
	OSStart();
	return 0;															
}


// T1 - Sending Messages to T2

void T1	(void *pdata)
{

	pdata = pdata;						        /* Dummy data */

	while(1)
	{	 	
		sprintf(msg_1,"Hello\n");
		OSQPost(que1, msg_1);
		LED_on(0);
		OSTimeDly(3);
		LED_off(0);
		OSTimeDly(3);

		sprintf(msg_1,"Durvesh\n");
		OSQPost(que1, msg_1);
		LED_on(0);
		OSTimeDly(3);
		LED_off(0);
		OSTimeDly(10);
		
	}
}

// T2 - Receiving Messages from T1

void T2	(void *pdata)
{
	char* ptr_c;	
	pdata = pdata;						        /* Dummy data */

	while(1)
	{
		// wait for message from queue
		ptr_c = OSQPend(que1,0, &err); 
		UART0_SendData(ptr_c);
		
		LED_on(1);
		OSTimeDly(1);
		LED_off(1);
		OSTimeDly(1);
			 		
	}
}

// T3 - Receiving messages from T4

void T3	(void *pdata)
{
	char* ptr_c;	
	pdata = pdata;						        /* Dummy data */

	while(1)
	{
		// wait for message from queue
		ptr_c = OSQPend(que2,0, &err); 
		UART0_SendData(ptr_c);
		
		LED_on(2);
		OSTimeDly(4);
		LED_off(2);
		OSTimeDly(4);
			 		
	}
}

void T4	(void *pdata)
{

	pdata = pdata;						        /* Dummy data */

	while(1)
	{	 
		OSTimeDly(10);
			
		sprintf(msg_2,"2019BTEEN00035\n");
		OSQPost(que2, msg_2);
		LED_on(3);
		OSTimeDly(4);
		LED_off(3);
		OSTimeDly(4);

		sprintf(msg_2,"B.Tech - Electronics\n");
		OSQPost(que2, msg_2);
		LED_on(3);
		OSTimeDly(4);
		LED_off(3);
		OSTimeDly(4);

		
		
	}
}

/***********************
                            End Of File
************************/
