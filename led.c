/*****************************************************************************
 *   led.c:  
*****************************************************************************/
#include "config.h"                       


/*****************************************************************************
LED init
*****************************************************************************/
void LED_init( void )
{
	// make P0.4..7 as GPIO
	// one pin requires two bits from 
	// PINSELx register.
	// Funstion of P0.0 is set using
	// PINSEL bit 0 and bit 1
	// For P0.4...7 we reqired to set
	// bits 9..15 of PINSEL0
 	PINSEL0 = PINSEL0 & 0xFFFFFF0F;

	// make them as output
 	IO0DIR = IO0DIR | 0x000000F0;

	// make P0.22, P0.28, P0.30  as output
 	PINSEL1 = PINSEL1 & 0xCCFFCFFF;
	// make them as output
	// 0101 0000 0100 
 	IO0DIR = IO0DIR | 0x50400000;

	// make P1.16 as IO. For this bit 3 should b made 1
	// rest of the bits must be zero for debugging through U-Link debugger
 	PINSEL2 = 0x04; //PINSEL2 & 0xFFFF00FF;
	// make P1.16 as output
	IO1DIR |=   0x00010000;	

}

void LED_on(unsigned int led_number)
{
	switch(led_number)
	{
	 	case 0: {IO0SET = 0x00000010;} break;
	 	case 1: {IO0SET = 0x00000020;} break;
	 	case 2: {IO0SET = 0x00000040;} break;
	 	case 3: {IO0SET = 0x00000080;} break;
	 	case 4: {IO0SET = 0x00400000;} break;
	 	case 5: {IO0SET = 0x10000000;} break;
	 	case 6: {IO0SET = 0x40000000;} break;
	 	case 7: {IO1SET = 0x00010000;} break;
		
		// default glows all LEDs
	 	default: 
			{
				IO0SET = 0x000000F0;
				IO0SET = 0x50400000;
				IO1SET = 0x00010000;
			} 	
	} 
}

void LED_off(unsigned int led_number)
{
	switch(led_number)
	{
	 	case 0: {IO0CLR = 0x00000010;} break;
	 	case 1: {IO0CLR = 0x00000020;} break;
	 	case 2: {IO0CLR = 0x00000040;} break;
	 	case 3: {IO0CLR = 0x00000080;} break;
	 	case 4: {IO0CLR = 0x00400000;} break;
	 	case 5: {IO0CLR = 0x10000000;} break;
	 	case 6: {IO0CLR = 0x40000000;} break;
	 	case 7: {IO1CLR = 0x00010000;} break;
		
		// default glows all LEDs
	 	default: 
			{
				IO0CLR = 0x000000F0;
				IO0CLR = 0x50400000;
				IO1CLR = 0x00010000;
			} break;	
	} 
}

/*****************************************************************************
**                            End Of File
******************************************************************************/

