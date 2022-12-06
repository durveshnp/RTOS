////////////////////////////////////////////////////
// © MikroDes Systems, www.mikrodes.com 
// Analog to Digital Converter (ADC) demo
//
// This program demonstrates ADC operation
// in LPC2148
/////////////////////////////////////////////////////
#ifndef  OS_MASTER_FILE
#include "..\APP\includes.h"
#endif

#include <LPC214X.H>
//void delay_200_msec(void);
void adc_init(void);
int adc_get_val(int channel);


//int main(void)
//{   
//    // select the pin function as GPIO
//    // P0.4,P0.5,P0.6,P0.7 as output
//    PINSEL0 &= 0xFFFFFF0F;
//
//    // Set the port direction (P0.4-P0.7 port pins output)
//    IODIR0 |= 0x000000F0; 
//
//    adc_init();
//
//    while(1)
//    {       
//        if(adc_get_val(2) > 0x1FF)
//        {
//            IOCLR0 = 0x00000010;
//        }
//        else
//        {                           
//            IOSET0 = 0x00000010;
//        }
//    }   
//}

void adc_init(void)
{   
    // select the function of P0.10 as AD input
    // AD1.2 
    PINSEL0 = (PINSEL0 & 0xFFCFFFFF) | 0x00300000;  
    
    // Use ADC1 only
    // bit 7..0: Channel number 00000001 -> channel 0
    // bit 15..8: ADC clock =((pclk/divider)-1) < 4.5MHz
    // for ADC clock ~3 MHz and Pclk = 6 MHz, divider = 1
    // bit 16: 0:Software SoC mode 1: Hardware SoC mode
    // bit 19..17: 000 = 10 bit conversion
    // bit 20: reserved
    // bit 21: 1: ADC on, 0: ADC off
    // bit 23..22: reserved
    // bit 26..24: 001: start now; others see datasheet
    // bit 27: useful if bit 26..24 are other than 000 or 001
    // other bits reserved
    AD1CR=0x00200101;
}


int adc_get_val(int channel)
{
    int val;                        
    // set the channel                         
    AD1CR = (AD1CR & 0xFFFFFF00) | (0x01 << channel );

    // allow the channel voltage to stabilize
    OSTimeDly(20);

    // clear "done" bit
    AD1GDR = AD1GDR & 0x7FFFFFFF;
    // start conversion
    // make bit 26..24 = 001
    AD1CR = AD1CR | 0x01000000 ;

    // now wait for conversion to be over
    // check "done" bit
    while(!(AD1GDR & 0x80000000));
     
    val = (AD1GDR & 0x0000FFC0) >> 6;
    // bit 15..6 has data
    return (val);
}

