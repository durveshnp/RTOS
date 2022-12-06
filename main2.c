/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			main.c
** Last modified Date:  2004-09-16
** Last Version:		1.0
** Descriptions:		The main() function example template
**
**------------------------------------------------------------------------------------------------------
** Created by:			Chenmingji
** Created date:		2004-09-16
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
** mcu123.com add keil
********************************************************************************************************/
#include "config.h"
#include "stdlib.h"
#include "..\GUI\BMP.h"

WINDOWS  Mwindows;   /* 主窗口句柄 */
WINDOWS  *current_Mwindows=&Mwindows;



#define	TaskStkLengh	64			//Define the Task0 stack length 定义用户任务0的堆栈长度 
 
OS_STK	TaskStk0 [TaskStkLengh];		//Define the Task0 stack 定义用户任务0的堆栈
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task0 stack 定义用户任务1的堆栈
OS_STK	TaskStk2 [TaskStkLengh];		//Define the Task0 stack 定义用户任务2的堆栈

void 	Task0(void *pdata);			//Task0 任务0
void 	Task1(void *pdata);			/*Tas1  任务1实现显示 */
void    Task_Keyboard(void *pdata);	 /* 键盘扫描任务 */

OS_EVENT   *DispSem;    
OS_EVENT   *Display_Box;        

uint8   Wait_Signal0;

/****************************************************************************
	main()
****************************************************************************/
int main (void)
{   	 	
	LED_Init();

	TargetInit();

	//while(1);
	OSInit ();
				
	DispSem = OSSemCreate(1);	       /**/	
	//Display_Box = OSMboxCreate((void *)0);	/**/																			
	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 2);
	OSTaskCreate(Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 3);	
		
	OSStart();
	return 0;															
}
/*********************************************************************************************************
**                            Task0 任务0
********************************************************************************************************/

void Task0	(void *pdata)
{
	pdata = pdata;						        /* Dummy data */

	while(1)
	{		 
		OSSemPend(DispSem,0,&Wait_Signal0);     /* Acquire the semaphore */
		// Do action
		LED_on(0);
		OSTimeDlyHMSM(0,0,0,20);
		LED_off(0);
		OSTimeDlyHMSM(0,0,0,20); //OSTimeDly(2);
		Wait_Signal0=OSSemPost(DispSem);        /* Release the semaphore */	
	}
}

void Task1	(void *pdata)
{		   
	pdata = pdata;						        /* Dummy data */
	
	while (1)
	{	
		OSSemPend(DispSem,0,&Wait_Signal0); 	/* Acquire the semaphore */
		LED_on(1);
		OSTimeDlyHMSM(0,0,1,20); //OSTimeDly(15); 
		Wait_Signal0=OSSemPost(DispSem);		/* Release the semaphore */
		LED_off(1);
		OSTimeDlyHMSM(0,0,1,20); //OSTimeDly(15);		
	}
}

void Task_Keyboard	(void *pdata)
{     
	uint32   key_temp=0,old_key=0;	          /* */
	uint8  	Key_Message;
	pdata = pdata;						     /*防止编译器警告*/
	
	while (1)
	{	 
		OSTimeDly(3);               /**Delay 30Ms*/
	    key_temp=(FIO0PIN&0x00000078);
		OSTimeDly(2);               /**Delay 20Ms The key is Ture*/
	   if((FIO0PIN&0x00000078) ==key_temp)
	  {
	    if(key_temp != old_key)     /* 识别长按 */
		{
		old_key=key_temp;
	    switch(key_temp)
		 {
		  case    0x00000038: 
		               Key_Message =  OSMboxPost(Display_Box,(void *)me); 
		               break;
		  case    0x00000070: Key_Message = OSMboxPost(Display_Box,(void *)meinv); 
		                break;
		  case    0x00000068: Key_Message = OSMboxPost(Display_Box,(void *)BMP);
		                break;
		  case    0x00000058:Key_Message =  OSMboxPost(Display_Box,(void *)&Fengjing);
		                break;
		 default :     break;
		 }
		Key_Message=Key_Message;
	  }
	  }
	}
	

}  
   
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
