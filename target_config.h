#ifndef 	__TARGET_CONFIG_h
#define 	__TARGET_CONFIG_h

/******************************************
*
*
*******************************************/
/******************************************
*UART
*******************************************/

#define  UART1_EN         0     /*UART1*/

#define  UART0_EN         1     /*UART0*/
#define    UART_INTERRUPT_FLAG  1/*ADC*/

#if (UART1_EN)||(UART0_EN)

#define    Baud0         57600
#define    Baud1         57600
#endif
/******************************************
*ADC
******************************************/
#define  ADC_EN           0     /* ADC */

#if      ADC_EN
#define ADC_Clk		1000000		/* 1Mhz */
#define   ADC_INTERRUPT_FLAG    /* ADC  */
#endif
/*****************************************
* UART
*****************************************/
#define  DAC_EN           0     /*DAC */


/*****************************************
* TIMER
*****************************************/
#define  TIMER0_EN        0     /*UART */

#define  TIMER1_EN        0     /*UART*/

#if  TIMER1_EN||TIMER0_EN

#include "timer.h"
#define  TIMER_INTERRUPT_FLAG    1 /* TIMER */
#endif

#define  SPI_EN             0     /*SPI*/

#define  SSP_EN             0     /*SSP*/


#define  RTC_EN             1     
#define  RTC_INTERRUPT_FLAG 0


#endif


/******************************************
**         End Of File
******************************************/
