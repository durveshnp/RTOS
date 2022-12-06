/*****************************************************************************
 *
*
*  定时器函数
*
 *
******************************************************************************/
#include   "define.h"


#if   TIMER0_EN 

uint32 timer_counter = 0;

#define Enable_timer0     	T0TCR = 1;   /*启动计数器0*/
#define Disable_timer0     	T0TCR = 0;   /*关闭计数器0*/
/******************************************************************************
** 函数名：		Timer0Handler
**
** 功能描述:		定时器中断处理函数在60MHz频率下没10Ms执行一次
**

******************************************************************************/
void Timer0Handler (void) __irq 
{  
    T0IR = 1;			/* 清中断标志 */
    IENABLE;			/* 使能嵌套中断 */

    timer_counter++;
    IDISABLE;
    VICVectAddr = 0;   /*中断确认*/
}


/******************************************************************************
** 函数名:		reset_timer
**
** 功能:		
**
** 
******************************************************************************/
void reset_timer( void )
{
    uint32 regVal;

	regVal = T0TCR;
	regVal |= 0x02;
	T0TCR = regVal;
    return;
}

/******************************************************************************
**函数名:		init_timer
**
** 功能描述:		初始化定时器, 设置时间间隔, 重启定时器,
**			        装载定时器中断地址
**

******************************************************************************/
boolen init_timer (void) 
{
    timer_counter = 0;
    T0MR0 = INTERVAL_10MS;	/* */
    T0MCR = 3;			/*  */
    if ( install_irq( TIMER0_INT, (void *)Timer0Handler ) == FALSE )
    {
	return (FALSE);
    }
    else
    {
	return (TRUE);
    }
}

#endif



#if   TIMER1_EN 

uint32 timer_counter = 0;

#define Enable_timer0     	T1TCR = 1;   /*启动计数器0*/
#define Disable_timer0     	T1TCR = 0;   /*关闭计数器0*/
/******************************************************************************
** 函数名：		Timer0Handler
**
** 功能描述:		定时器中断处理函数在60MHz频率下没10Ms执行一次
**

******************************************************************************/
void Timer1Handler (void) __irq 
{  
    T1IR = 1;			/* 清中断标志 */
    IENABLE;			/* 使能嵌套中断 */

    timer_counter++;
    IDISABLE;
    VICVectAddr = 0;   /*中断确认*/
}


/******************************************************************************
** 函数名:		reset_timer
**
** 功能:		Reset timer
**
** 
******************************************************************************/
void reset_timer( void )
{
    uint32 regVal;

	regVal = T1TCR;
	regVal |= 0x02;
	T1TCR = regVal;
    return;
}

/******************************************************************************
**函数名:		init_timer
**
** 功能描述:		初始化定时器, 设置时间间隔, 重启定时器,
**			        装载定时器中断地址
**

******************************************************************************/
boolen init_timer (void) 
{
    timer_counter = 0;
    T1MR0 = INTERVAL_10MS;	/* */
    T1MCR = 3;			/*  */
    if ( install_irq( TIMER1_INT, (void *)Timer1Handler ) == FALSE )
    {
	return (FALSE);
    }
    else
    {
	return (TRUE);
    }
}

#endif     

