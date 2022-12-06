
#include  	"config.h"

#if  UART0_EN

#if UART_INTERRUPT_FLAG
/*****************************************************************************
** UART0Handler
**
** UART0
** 
*****************************************************************************/
void Uart0_Exception(void)
{
    uint8 IIRValue, LSRValue;
    uint8 Dummy;
	OS_ENTER_CRITICAL();	        
    IIRValue = U0IIR;
    Dummy = U0RBR;		          	
	LSRValue = U0LSR; 
	VICVectAddr = 0; 
	OS_EXIT_CRITICAL();	
	     
	Dummy = Dummy;                      	   
    IIRValue >>= 1;			
    IIRValue &= 0x07;			
    if ( IIRValue == IIR_RLS )		
    {
	
	if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
	{
		UART0_SendData("Help~~~");
		return;
	}
	if ( LSRValue & LSR_RDR )				
	{
	   UART0_SendData("Thankyou for ~~~");	/*  write the code yourself*/
	   return ;
	}
    }
    else if ( IIRValue == IIR_RDA )	
    {
	UART0_SendData("UART0...");
	return ;
    }
    else if ( IIRValue == IIR_CTI )	
    {
	/**/
    }
    else if ( IIRValue == IIR_THRE )	
    {
	if ( LSRValue & LSR_THRE )
	{
     /**/
	}
	else
	{
      /*  */
	}
    }
}

#endif

/****************************************************************************
* SendByte()
****************************************************************************/
void  SendByte0(uint8 data)
{  
	U0THR = data;                                //发送数据
	while((U0LSR & 0x40) == 0);                 // 等待数据发送完毕
}

/****************************************************************************
* ReceiveByte()
****************************************************************************/
unsigned char  UART0_RecvByte(void)
{  
	while(!(U0LSR & 0x01)){OSTimeDly(2);};

	return (unsigned char)U0RBR ;	              
}

/****************************************************************************
* 名称：ISendBuf()
* 功能：将缓冲区的数据发送回主机，并等待发送完毕。
* 入口参数：数据指针
* 出口参数：无
****************************************************************************/
void  UART0_SendData(char *str)
{  
	while(1)
   {  
   		if( *str == '\0' ) break;
		SendByte0(*str++);	    			// 发送数据
   }   
}   

/****************************************************************************
* 名称：UART0_Init()
* 功能：初始化串口0,设置其工作模式及波特率。
* 入口参数：
****************************************************************************/
void UART0_Init(void)
{  

/*引脚连接通道选择*/ 
	PINSEL0 |= 0x00000005;


/* 设置串口波特率在标准的48M主频下1/2VBP下：*/
    U0LCR = 0x83;                    //DLAB位置1,8位数据位,1位停止位,无奇偶校验
#if Baud0==19600						 //设置波特率为19600 误差：0。6％
    U0DLM=0;
	U0DLL=38;
#endif
									
#if Baud0==57600        				  //57600  error:0.16%
    U0DLM=0;						  
	U0DLL=13;
#endif

#if Baud0==115200        				  //57600  error:0.16%
    U0DLM=0;						  
	U0DLL=13;
#endif
	U0LCR = 0x03; 					 //DLAB
    U0FCR = 0x07;		


#if UART_INTERRUPT_FLAG  
    U0IER = IER_RBR | IER_THRE | IER_RLS;	
#endif

}


#endif




#if  UART1_EN



#if UART_INTERRUPT_FLAG

/*****************************************************************************
** UART1Handler
**
** 
** 
*****************************************************************************/
void Uart1_Exception (void)
{
    uint8 IIRValue, LSRValue;
    uint8 Dummy;
	OS_ENTER_CRITICAL();	       /*  */ 
    IIRValue = U1IIR; 
	LSRValue = U1LSR;
    Dummy = U1RBR;		          /* 读RBR寄存器清楚中断 */
	OS_EXIT_CRITICAL();	   
	Dummy = Dummy;               /* 防止编译器警告 */       	   
    IIRValue >>= 1;			
    IIRValue &= 0x07;			/* 中断标识位1～3 */
    if ( IIRValue == IIR_RLS )		/* 接收线状态*/
    {

	if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
	{ 
		UART0_SendData("Help~~~");
	    return;
	}
	if ( LSRValue & LSR_RDR )	/* 接收数据准备好 */			
	{
	    /* 如果在接收线上没有错误, 正常准备好, 则保存数据.读RBR将清楚中断 */
	   UART0_SendData("Thankyou for ~~~");	/*  write the code yourself*/
	}
    }
    else if ( IIRValue == IIR_RDA )	/* 接收数据可用 */
    {
	UART0_SendData("UART1中断－－");
    }
    else if ( IIRValue == IIR_CTI )	/* 字符超时显示 */
    {
	/**/
    }
    else if ( IIRValue == IIR_THRE )	/* THRE, 传送寄存器空 */
    {
	LSRValue = U0LSR;		/* 检查LSR寄存器看U0THR数据是否正确可用 */
	if ( LSRValue & LSR_THRE )
	{
     /**/
	}
	else
	{
      /*  */
	}
    }
}

#endif

/****************************************************************************
* 名称：SendByte()
* 功能：向串口发送字节数据。
* 入口参数：data--要发送的数据
* 出口参数：无
****************************************************************************/
void  SendByte1(uint8 data)
{  
	U0THR = data;                                //发送数据
	while((U1LSR & 0x40) == 0);                 // 等待数据发送完毕
}

/****************************************************************************
* 名称：ISendBuf()
* 功能：将缓冲区的数据发送回主机，并等待发送完毕。
* 入口参数：数据指针
* 出口参数：无
****************************************************************************/
void  UART_SendData1(uint8 *str)
{  
	while(1)
   {  
   		if( *str == '\0' ) break;
		SendByte1(*str++);	    			// 发送数据
   }   
}   

/****************************************************************************
* 名称：UART0_Init()
* 功能：初始化串口0,设置其工作模式及波特率。
* 入口参数：baud         波特率
* 出口参数：
****************************************************************************/
void UART1_Init(void)
{  

/*引脚连接通道选择*/ 
	PINSEL0 |= 0x00050000;


/* 设置串口波特率在标准的48M主频下1/2VBP下：*/
    U1LCR = 0x83;                    //DLAB位置1,8位数据位,1位停止位,无奇偶校验
#if Baud1==19600						 //设置波特率为19600 误差：0。6％
    U1DLM=0;
	U1DLL=76;
#endif
									
#if Baud1==57600        				  //设置波特率为57600  error:0.16%
    U1DLM=0;						  
	U1DLL=26;
#endif

#if Baud1==115200        				  //设置波特率为57600  error:0.16%
    U1DLM=0;						  
	U1DLL=13;
#endif
	U1LCR = 0x03; 					 //DLAB位恢复0,8位数据位,1位停止位,无奇偶校验
    U0FCR = 0x07;		/* 使能并重启Rx、Tx缓冲寄存器 */

#if UART_INTERRUPT_FLAG
    if ( install_irq( UART1_INT, (void *)UART1Handler ) == FALSE )
    {
	return (FALSE);
    }
   
    U0IER = IER_RBR | IER_THRE | IER_RLS;	/* 使能中断 */
	return (TURE);
#endif

}


#endif


/*********************************************************************************
**                            End Of File
*********************************************************************************/

