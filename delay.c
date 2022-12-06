// Delay routines.
// The delay is approximate.
// The crystal frequency is 
// **** assumed to be 12MHz.
// **** CCLK = 24MHz

#include "delay.h"

void delay_5us(void)
{
	unsigned int delay=0;

	for(delay=25; delay > 0; --delay) {}
}

void delay_200us(void)
{
	unsigned int delay=100;

	for(delay=1000; delay > 0; --delay) {}
}

void delay_5ms(void)
{
	unsigned int delay;

	for(delay = 25000; delay > 0; --delay) { }
}


void delay_200_msec(void)
{
	unsigned int s,delay1, delay2;

	for(s = 2;s > 0; --s)
	{ 
		for(delay2 = 20; delay2 > 0; --delay2)
		{ 
			for(delay1 = 25000; delay1 > 0; --delay1) { }
		} 
	}
}

void delay_1sec(void)
{
	unsigned int s,delay1, delay2;

	for(s = 10;s > 0; --s)
	{ 
		for(delay2 = 200; delay2 > 0; --delay2)
		{ 
			for(delay1 = 250; delay1 > 0; --delay1) { }
		} 
	}
}

void delay(void)
{
	unsigned int delay,s;
	 	for(s=4;s>0;s--)
		{
 			for(delay = 10; delay > 0; --delay){}
		}
}

