#include "config.h"
#include <stdio.h>
#include "stdlib.h"

#define TaskStkLength 64

OS_STK TaskStk0[TaskStkLenghth];
OS_STK TaskStk0[TaskStkLenghth];
OS_STK TaskStk0[TaskStkLenghth];
OS_STK TaskStk0[TaskStkLenghth];

void Task0(void *pdata);
void Task1(void *pdata);
void Task2(void *pdata);
void Task3(void *pdata);


int main()
{
	LED_init();
	UART0_Init();
	TargetInit();
	OSInit();

	OSTaskCreate(Task0,(void *)0, &TaskStk0[TaskStkLength-1],6);
	OSTaskCreate(Task1,(void *)0, &TaskStk1[TaskStkLength-1],7);
	OSTaskCreate(Task2,(void *)0, &TaskStk2[TaskStkLength-1],8);
	OSTaskCreate(Task3,(void *)0, &TaskStk3[TaskStkLength-1],9);

	OSStart();

	return 0;

}
