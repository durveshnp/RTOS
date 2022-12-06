#include "config.h"
#include "stdlib.h"
#include <stdio.h>

#define TaskStkLengh 64 //Define the Task0 stack length

OS_STK TaskStk0 [TaskStkLengh]; //Define the Task stack
OS_STK TaskStk1 [TaskStkLengh]; //Define the Task stack
OS_STK TaskStk2 [TaskStkLengh]; //Define the Task stack
OS_STK TaskStk3 [TaskStkLengh]; //Define the Task stack

void Task0(void *pdata);
void Task1(void *pdata);
void Task2(void *pdata);
void Task3(void *pdata);

OS_EVENT* MsgQueue1;

OS_EVENT* MsgQueue2;

#define SIZE_OF_Q 15

void* MessageStorage1[SIZE_OF_Q];
void* MessageStorage2[SIZE_OF_Q];


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
	MsgQueue1 = OSQCreate(MessageStorage1,SIZE_OF_Q);
	MsgQueue2 = OSQCreate(MessageStorage2,SIZE_OF_Q);

	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 6);
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 7);
	OSTaskCreate (Task2,(void *)0, &TaskStk2[TaskStkLengh - 1], 8);

	OSStart();
	return 0;
}
/********************
** Task0
********************/

void Task0 (void *pdata)
{
	pdata = pdata; /* Dummy data */
	while(1)
	{
		sprintf(msg_1,"Hello\n");
		OSQPost(MsgQueue1, msg_1);

		LED_on(0);
		OSTimeDly(7);
		LED_off(0);
		OSTimeDly(7);

		sprintf(msg_1,"Durvesh\n");
		OSQPost(MsgQueue1, msg_1);

		LED_on(0);
		OSTimeDly(7);
		LED_off(0);
		OSTimeDly(7);

		sprintf(msg_1,"Good afternoon\n");
		OSQPost(MsgQueue1, msg_1);

		LED_on(0);
		OSTimeDly(7);
		LED_off(0);
		OSTimeDly(7);

		OSTimeDly(30);
	}
}

void Task1 (void *pdata)
{
	char* ptr_c;

	pdata = pdata; /* Dummy data */
	while(1)
	{
	// wait for message from queue
		ptr_c = OSQPend(MsgQueue1,0, &err);
		UART0_SendData(ptr_c);
		LED_on(1);
		OSTimeDly(2);
		LED_off(1);
		OSTimeDly(2);
		

		sprintf(msg_2,"From Task1\n");
		OSQPost(MsgQueue2, msg_2);

		LED_on(0);
		OSTimeDly(2);
		LED_off(0);
		OSTimeDly(2);

		sprintf(msg_2,"Also from Task1\n");
		OSQPost(MsgQueue2, msg_2);

		LED_on(0);
		OSTimeDly(2);
		LED_off(0);
		OSTimeDly(2);

	}
}

void Task2 (void *pdata)
{
	char* ptr_c;

	pdata = pdata; /* Dummy data */
	while(1)
	{
	// wait for message from queue
		ptr_c = OSQPend(MsgQueue2,0, &err);
		UART0_SendData(ptr_c);

		LED_on(2);
		OSTimeDly(2);
		LED_off(2);
		OSTimeDly(2);
		


	}
}

