/*****************************************************************************
 *   RELAY.c:  
*****************************************************************************/                      
#include <LPC214x.h>

/*****************************************************************************
LED init
*****************************************************************************/
void relay_init( void)
{
    // make P1.25 as GPIO   ( connected to Relay 0 )    
    PINSEL2 = 0x04;
    // make P1.25 as output
    IODIR1 |=  (1 << 25);   

    // make P0.12 as GPIO   ( connected to Relay 1 )    
	PINSEL0 &= ~(3<<12);  
    // make P0.12 as output	
    IODIR0 |= (1 << 12);
}

void relay_off(unsigned int rly_number)
{
	switch(rly_number)
	{
	 	case 0: {IOCLR1 = (1<<25);} break;
	 	case 1: {IOCLR0 = (1<<12);} break;
		
		// default both relays on 
	 	default: 
		{
			IOCLR1 = (1<<25);
			IOCLR0 = (1<<12);
		}
	} 
}

void relay_on(unsigned int rly_number)
{
	switch(rly_number)
	{
	 	case 0: {IOSET1 = (1<<25);} break; // Relay0 off 
	 	case 1: {IOSET0 = (1<<12);} break; // Relay1 off
		
		// default both relays off 
	 	default: 
			{
				IOSET1 = (1<<25);
				IOSET0 = (1<<12);
			}
	} 
}
