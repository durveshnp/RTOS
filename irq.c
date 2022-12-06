/*****************************************************************************
 *                       中断服务程序设置
******************************************************************************/
#include "define.h"			

#if   INTERRPUT_EN
/******************************************************************************
** 函数名:		DefaultVICHandler
**
** 函数功能:		默认的VIC中断处理，用于处理伪中断.
**				    如果中断服务程序读VICaddress 寄存器, 而IRQ slot 响应如下描述将返回这个地址.
** 入口参数:		
** 出口参数:		
** 
******************************************************************************/
void DefaultVICHandler (void) __irq
{
    /*如果IRQ没有装入VIC, 而中断产生,这个默认的VIC address 将会北使用. 这将会产生无限循环. 
	在调试中用这个死循环进行调试跟踪. */
    VICVectAddr = 0;
    while ( 1 );
}

/******************************************************************************
** 函数名   :		init_VIC
**
** 功能描述:	初始化VIC interrupt 控制器.
** 
******************************************************************************/
void init_VIC(void) 
{
    uint8 i = 0;
    uint32 *vect_addr, *vect_cntl;
   	
    /* 初始化 VIC*/
    VICIntEnClr = 0xffffffff;		 /*清所有中断*/
    VICVectAddr = 0;
    VICIntSelect = 0;

    /*设置所有中断向量为0 */
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	vect_addr = (uint32 *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
	vect_cntl = (uint32 *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
	*vect_addr = 0;	
	*vect_cntl = 0;
    }

    /* 装入默认的中断处理地址*/
    VICDefVectAddr = (uint32*)DefaultVICHandler;   
}

/******************************************************************************
** 函数名:		install_irq
**
** 功能描述:	装入中断处理，最大数目为16, 但这里有32个中断功能. 所以不能同时装入所有服务.
**				对中断请求的规则是先发生服务
** 入口参数:			中断号和中断服务地址
** 出口参数:	0或者1
** 
******************************************************************************/
boolen install_irq( uint8 IntNumber, void *HandlerAddr )
{
    uint8 i;
    uint32 *vect_addr;
    uint32 *vect_cntl;
      
    VICIntEnClr = 1 << IntNumber;	/* 禁止中断 */
    
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	/* 找出第一个未分配服务地址 */

	vect_addr = (uint32 *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
	vect_cntl = (uint32 *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
	if ( *vect_addr == (uint32)NULL )
	{
	    *vect_addr = (uint32)HandlerAddr;	/* 设置中断向量 */
	    *vect_cntl = (uint32)(IRQ_SLOT_EN | IntNumber);
	    break;
	}
    }
    if ( i == VIC_SIZE )
    {
	return( FALSE );		/* 没有空的vector slot */
    }
    VICIntEnable = 1 << IntNumber;	/* 使能Interrupt */
    return( TRUE );
}

/******************************************************************************
** 函数名:		uninstall_irq
**
** 功能描述:	卸载中断处理
**				通过中断号找到该服务地址, 并设置为空来实现卸载.
** 入口参数:	中断号
**出口参数:		0、1成功与否
** 
******************************************************************************/
boolen uninstall_irq( uint8 IntNumber )
{
    uint8 i;
    uint32 *vect_addr;
    uint32 *vect_cntl;
      
    VICIntEnClr = 1 << IntNumber;
    
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	/* 找到第一个未分配的VIC address  */
	vect_addr = (uint32 *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
	vect_cntl = (uint32 *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
	if ( (*vect_cntl & ~IRQ_SLOT_EN ) == IntNumber )
	{
	    *vect_addr = (uint32)NULL;	/* 清VIC地址 */
	    *vect_cntl &= ~IRQ_SLOT_EN;	/*清使能位 */	
	    break;
	}
    }
    if ( i == VIC_SIZE )
    {
	return( FALSE );		
    }
    VICIntEnable = 1 << IntNumber;
    return( TRUE );
}

#endif
/******************************************************************************
**                            End Of File
******************************************************************************/
