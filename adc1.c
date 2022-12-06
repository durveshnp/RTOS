/*****************************************************************************
 *  
  AD转换函数
 *
******************************************************************************/
//#include "define.h"
#if ADC_EN                      /*如果启动ADC*/



uint32 ADC0Value[ADC_NUM];
uint32 ADC0IntDone = 0;

#if ADC_INTERRUPT_FLAG
/**************************************************************************************
** 函数名称 ：ADC0Handler (void) __irq
** 函数功能 ：ADC0中断处理
** 入口参数 ：
** 出口参数 ：
***************************************************************************************/
void ADC0Handler (void) __irq 
{
    uint32 regVal;
  
    IENABLE;			/* 处理嵌套中断 */

    regVal = AD0STAT;		/* 读ADC将清除ADC中断标志 */
    if ( regVal & 0x0000FF00 )	/*检查OVERRUN  */
    {
	regVal = (regVal & 0x0000FF00) >> 0x08;
	switch ( regVal )
	{
	    case 0x01:
		regVal = AD0DR0;
		break;
	    case 0x02:
		regVal = AD0DR1;
		break;
	    case 0x04:
		regVal = AD0DR2;
		break;
	    case 0x08:
		regVal = AD0DR3;
		break;
	    case 0x10:
		regVal = AD0DR4;
		break;
	    case 0x20:
		regVal = AD0DR5;
		break;
	    case 0x40:
		regVal = AD0DR6;
		break;
	    case 0x80:
		regVal = AD0DR7;
		break;
	    default:
		break;
	}
	AD0CR &= 0xF8FFFFFF;	/*停止ADC */ 
	ADC0IntDone = 1;
	return;	
    }
    
    if ( regVal & ADC_ADINT )
    {
	switch ( regVal & 0xFF )	/* 检查DONE位 */
	{
	    case 0x01:
		ADC0Value[0] = ( AD0DR0 >> 6 ) & 0x3FF;
		break;
	    case 0x02:
		ADC0Value[1] = ( AD0DR1 >> 6 ) & 0x3FF;
		break;
	    case 0x04:
		ADC0Value[2] = ( AD0DR2 >> 6 ) & 0x3FF;
		break;
	    case 0x08:
		ADC0Value[3] = ( AD0DR3 >> 6 ) & 0x3FF;
		break;
	    case 0x10:
		ADC0Value[4] = ( AD0DR4 >> 6 ) & 0x3FF;
		break;
	    case 0x20:
		ADC0Value[5] = ( AD0DR5 >> 6 ) & 0x3FF;
		break;
	    case 0x40:
		ADC0Value[6] = ( AD0DR6 >> 6 ) & 0x3FF;
		break;
	    case 0x80:
		ADC0Value[7] = ( AD0DR7 >> 6 ) & 0x3FF;
		break;		
	    default:
		break;
	}
	AD0CR &= 0xF8FFFFFF;	/*停止ADC */ 
	ADC0IntDone = 1;
    }

    IDISABLE;
    VICVectAddr = 0;	
}
#endif
/**************************************************************************************
** 函数名称 ：ADCInit (uint32)
** 函数功能 ：ADC初始化
** 入口参数 ：要初始化的通道
** 出口参数 ：
***************************************************************************************/
boolen ADC_Init(uint32 ADCCLK )
{
/* 引脚设置为ADC功能, AD0.0~7*/	
    PINSEL0 = 0x0F333F00;

    AD0CR = ( 0x01 << 0 ) |   	        /* 设置为N时选择通道N  */
	( ( Fpclk / (ADCCLK - 1 )) << 8 ) |  /* CLKDIV = Fpclk / 1000000 - 1  */
	( 0 << 16 ) | 		// BURST = 0, 1
	( 0 << 17 ) |  		// CLKS = 0, 11
	( 1 << 21 ) |  		// PDN = 1, 
	( 0 << 22 ) |  		// TEST1:0 = 00 
	( 0 << 24 ) |  		// START = 0 A/D 转换停止
	( 0 << 27 );		/* EDGE = 0 (CAP/MAT 上升活下降启动 A/D conversion) */


#if ADC_INTERRUPT_FLAG
    AD0INTEN = 0x11E;		/*使能所有ADC中断*/

    if ( install_irq( ADC0_INT, (uint32*)ADC0Handler ) == FALSE )
    {
	return (FALSE);
    }
#endif
    return (TRUE);
}
/*****************************************************************************
**函数名:		ADC0Read
**
** 功能描述:	读ADC0转换结果
**
** 入口参数:			通道号
** 出口参数:	
** 
*****************************************************************************/
uint32 ADC0Read( uint8 channelNum )
{
#if !ADC_INTERRUPT_FLAG
    uint32 regVal, ADC_Data;
#endif

    /* 通道号 */
    if ( channelNum >= ADC_NUM )
    {
	channelNum = 0;		/*如果大于最大ADC通道数（7）则设置通道为0 */
    }
    AD0CR &= 0xFFFFFF00;
    AD0CR |= (1 << 24) | (1 << channelNum);	
				/* 选择通道开启ADC开始转换*/
#if !ADC_INTERRUPT_FLAG
    while ( 1 )			/* 等待ADC转换结束 */
    {
	regVal = *(volatile unsigned long *)(AD0_BASE_ADDR 
			+ ADC_OFFSET + ADC_INDEX * channelNum);
				/* 读ADC转换结果 */
	if ( regVal & ADC_DONE )
	{
	    break;
	}
    }	
        
    AD0CR &= 0xF8FFFFFF;	/* 停止ADC */    
    if ( regVal & ADC_OVERRUN )	/* 在没有错误的情况下保存数据 */
    {
	return ( 0 );
    }
    ADC_Data = ( regVal >> 6 ) & 0x3FF;
    return ( ADC_Data );	/* 返回ADC转换的值 */
#else
    return ( channelNum );	/* 如果ADC中断启动，那么结果将会在ADC中断服务程序中得到这里只返回通道号 */
#endif
}

#endif
/*********************************************************************************
**                            End Of File
*********************************************************************************/
