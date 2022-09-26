#include "config.h"
#include "stdlib.h"
#include <stdio.h>

#define TaskStkLength 64

OS_STK TaskStk0[TaskStkLength];
OS_STK TaskStk1[TaskStkLength];
OS_STK TaskStk2[TaskStkLength];
OS_STK TaskStk3[TaskStkLength];

void Task0(void *pdata);
void Task1(void *pdata);
void Task2(void *pdata);
void Task3(void *pdata);

OS_EVENT *pSemLed;

unsigned char err;

short flg = 0;

int main(void)
{
	LED_init();
	TargetInit();
	OSInit();

	pSemLed = OSSemCreate(1);

	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLength - 1], 6);
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLength - 1], 7);	
	OSTaskCreate (Task2,(void *)0, &TaskStk2[TaskStkLength - 1], 8);	
	OSTaskCreate (Task3,(void *)0, &TaskStk3[TaskStkLength - 1], 9);	

	OSStart();

	return 0;
}



void Task0(void *pdata)
{
	pdata = pdata;

	while(1)
	{  	
		if(flg == 0)
		{

			OSSemPend(pSemLed,0,&err);
			
			LED_on(0);	
			OSTimeDly(3);
	
			UART0_SendData("Task0 \n");
	
			LED_off(0);	
			
			OSSemPost(pSemLed);
	
			OSTimeDly(2);

			flg = 1;
		}
		
		OSTimeDly(1);
		
	}
	
}

void Task1(void *pdata)
{
	pdata = pdata;

	while(1)
	{  	
		if(flg == 1)
		{
			OSSemPend(pSemLed,0,&err);
			
			LED_on(1);	
			OSTimeDly(2);
	
			UART0_SendData("Task1 \n");
	
			LED_off(1);	
	
			OSSemPost(pSemLed);
	
			OSTimeDly(3);

			flg = 2;
		}
		
		OSTimeDly(1);
	}
	
}

void Task2(void *pdata)
{
	pdata = pdata;

	while(1)
	{  	
		if(flg == 2)
		{

			OSSemPend(pSemLed,0,&err);
			
			LED_on(2);	
			OSTimeDly(2);
	
			UART0_SendData("Task2 \n");
	
			LED_off(2);	
	
			OSSemPost(pSemLed);
	
			OSTimeDly(2);

			flg = 3;
		}

		OSTimeDly(1);

	}
	
}


void Task3(void *pdata)
{
	pdata = pdata;

	while(1)
	{  	
		if(flg == 3)
		{
			OSSemPend(pSemLed,0,&err);
			
			LED_on(3);	
			OSTimeDly(3);
	
			UART0_SendData("Task3 \n");
	
			LED_off(3);	
			OSSemPost(pSemLed);
			OSTimeDly(3);

			flg = 0;
		}
		
		OSTimeDly(1);

	}
	
}


