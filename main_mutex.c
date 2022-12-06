// Program to illustrate Mutex


#include "config.h"
#include "stdlib.h"

#define	TaskStkLengh	64				//Define the Task0 stack length 定义用户任务0的堆栈长度 
 
OS_STK	TaskStk0 [TaskStkLengh];		//Define the Task0 stack 定义用户任务0的堆栈
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task0 stack 定义用户任务1的堆栈
OS_STK	TaskStk2 [TaskStkLengh];		//Define the Task0 stack 定义用户任务2的堆栈

void 	Task0(void *pdata);			//Task0 任务0
void 	Task1(void *pdata);			/*Tas1  任务1实现显示 */
void 	Task2(void *pdata);			/*Tas1  任务1实现显示 */


OS_EVENT   *MySem;           
unsigned char err;

/****************************************************************************
	main()
****************************************************************************/
int main (void)
{   
	LED_Init();
	lcd_init();
	UART0_Init();
	TargetInit();		 
	UART0_SendData("Hello");
	lcd_data('A');

	OSInit ();
	MySem = OSSemCreate(1);			
	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 6);
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 7);	
	OSTaskCreate (Task2,(void *)0, &TaskStk2[TaskStkLengh - 1], 9);
			
	OSStart();
	return 0;															
}
/*********************************************************************************************************
**                            Task0 任务0
********************************************************************************************************/

void Task0	(void *pdata)
{
//	INT8U err;
	pdata = pdata;						        /* Dummy data */
	//OSTimeDly(5);
	while(1)
	{		 
		// Do action
		UART0_SendData("\n\rTask 0 waiting for Semaphore");
		OSSemPend(MySem, 0, &err);
		UART0_SendData("\n\rTask 0 got the Semaphore");
		LED_on(0);
		OSTimeDly(10);
		LED_off(0);
		OSSemPost(MySem);
		UART0_SendData("\n\rTask 0 released Semaphore \n\r");
		OSTimeDly(10);
	}
}

void Task1	(void *pdata)
{
//	INT8U err;		   
	pdata = pdata;						        /* Dummy data */
	
	while (1)
	{	
		UART0_SendData("\n\rTask 1 waiting for Semaphore");
		OSSemPend(MySem, 0, &err);
		UART0_SendData("\n\rTask 1 got the Semaphore");
		LED_on(1);
		OSTimeDly(1);		
		LED_off(1);
		OSTimeDly(1);
		LED_on(1);
		OSTimeDly(1);		
		LED_off(1);
		OSTimeDly(1);
		OSSemPost(MySem);
		UART0_SendData("\n\rTask 1 released Semaphore\n\r");
	}
}

void Task2	(void *pdata)
{
//	INT8U err;		   
	pdata = pdata;						        /* Dummy data */
	
	while (1)
	{	
		// Do action
		LED_on(2);
		OSTimeDly(2);
		LED_off(2);
		OSTimeDly(2);		
	}
}


   
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
