#include <LPC214x.h>
#include "delay.h"
#include "kbd.h"
#ifndef  OS_MASTER_FILE
#include "..\APP\includes.h"
#endif

// Row P1.17, P1.18, P1.19, P1.20
#define MASK_ROW		0x001E0000			// Used as SCAN LINES

#define MASK_ROW0		0x00020000			// Used as SCAN0 LINES
#define MASK_ROW1		0x00040000			// Used as SCAN1 LINES
#define MASK_ROW2		0x00080000			// Used as SCAN2 LINES
#define MASK_ROW3		0x00100000			// Used as SCAN3 LINES
	
//0000 0000 0001 1110 0000 0000 0000 0000

// Row P1.21, P1.22, P1.23, P1.24
#define MASK_COL		0x01E00000			// Used as RETURN LINES
//0000 0001 1110 0000 0000 0000 0000 0000
#define MASK_COL_NEG	0xFE1FFFFF			// Used as RETURN LINES


#define MASK_BUZZER		0x00000010		    // LED-0 on LED_i/f

// Buzzer to be connected to P0.4
//0000 0000 0000 0000 0000 0000 0001 0000

#define BUZZER_ON	{IOSET0 = MASK_BUZZER;}
#define BUZZER_OFF	{IOCLR0 = MASK_BUZZER;}


void kbd_init(void)
{
	// ROWs are OUTPUT
	// COLOUMNs are INPUT
	IODIR1 = IODIR1 | (MASK_ROW & MASK_COL_NEG);
	IOSET1 = MASK_ROW;	// make all rows high

	// Set direction for buzzer
	IODIR0 = (IODIR0 | MASK_BUZZER);
}
unsigned int get_key(void)
{	
	unsigned int k1,k2;
	k1 = 'm';	 // k1 and k2 deliberately made unequal
	k2 = 'n';	 // 


	// wait till the key is released
	while( chk_key() != 'z')
	{OSTimeDly(1);}

	do
	{
		k1 = chk_key();
		OSTimeDly(1);
		k2 = chk_key();

	} while(k1!= k2 || k1 == 'z');
	
	

	if(k1==k2)
	{
//		BUZZER_ON
//		delay_200_msec();
//		BUZZER_OFF
		return k1;
	}
	else
	{	
//		BUZZER_ON
		return 'z';
	}
	
}	//end of get key subroutine		

unsigned int chk_key(void)
{
	unsigned int  temp;  
	unsigned int  k = 'z';
	//press any key

	IOSET1 = MASK_ROW3;
	IOCLR1 = MASK_ROW0;			//ground row 0
	temp = IOPIN1  & MASK_COL;	// read the coloumns
	
	switch(temp)
	{	
		// MASK_COL	0x01E00000
		// MASK_ROW 0x001E0000 
		case 0x01C00000: 	k='0';	  // 0000 0001 1100 0000
							break; 
		case 0x01A00000: 	k='1';	  // 0000 0001 1010 0000
							break;
		case 0x01600000:	k='2';	  // 0000 0001 0110 0000
							break;
		case 0x00E00000:	k='3';	  // 0000 0000 1110 0000
							break;
		default: break;
	}
	IOSET1 = MASK_ROW0;	
	IOCLR1 = MASK_ROW1;			//ground row 0
	temp = IOPIN1  & MASK_COL;	// read the coloumns
	
	switch(temp)
	{	
		// MASK_COL	0x01E00000
		case 0x01C00000: 	k='4';	  // 0000 0001 1010 0000
							break; 
		case 0x01A00000: 	k='5';	  // 0000 0001 0110 0000
							break;
		case 0x01600000:	k='6';	  // 0000 0000 1110 0000
							break;
		case 0x00E00000:	k='7';	  // 0000 0001 1110 0000
							break;
		default: break;
	}

	IOSET1 = MASK_ROW1;		
	IOCLR1 = MASK_ROW2;			//ground row 0
	temp = IOPIN1  & MASK_COL;	// read the coloumns
	
	switch(temp)
	{	
		// MASK_COL	0x01E00000
		case 0x01C00000: 	k='8';	  // 0000 0001 1010 0000
							break; 
		case 0x01A00000: 	k='9';	  // 0000 0001 0110 0000
							break;
		case 0x01600000:	k='A';	  // 0000 0000 1110 0000
							break;
		case 0x00E00000:	k='B';	  // 0000 0001 1110 0000
							break;
		default: break;
	}
	
	IOSET1 = MASK_ROW2;	
	IOCLR1 = MASK_ROW3;			//ground row 0
	temp = IOPIN1  & MASK_COL;	// read the coloumns
	
	switch(temp)
	{	
		// MASK_COL	0x01E00000
		case 0x01C00000: 	k='C';	  // 0000 0001 1010 0000
							break; 
		case 0x01A00000: 	k='D';	  // 0000 0001 0110 0000
							break;
		case 0x01600000:	k='E';	  // 0000 0000 1110 0000
							break;
		case 0x00E00000:	k='F';	  // 0000 0001 1110 0000
							break;
		default: break;
	}

	return k;

}
