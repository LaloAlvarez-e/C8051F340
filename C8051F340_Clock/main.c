/*
 * main.c
 *
 *  Created on: 15/01/2020
 *      Author: vyldram
 */

#include <c8051F340.h>
#include <si_toolchain.h>
#include <INTRINS.H>

void OSCILLATOR_Init (void);




void main (void)
{
	PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer enable)

	OSCILLATOR_Init ();                 // Initialize Oscillator


	while (1)
	{
	}
}



void OSCILLATOR_Init (void)
{
	unsigned short i=0;
	OSCICN |= 0x03;                     // Configure internal oscillator for
                                       // its maximum frequency (12 Mhz)

	CLKMUL =0;							//activate oscillator multiplier
	CLKMUL |= 0x80;
	for (i=0; i<50000; i++);
	CLKMUL|=0xC0;
	while((CLKMUL & 0x20) == 0);

	CLKSEL&=~0x7;						//set x4 multiplier source
	CLKSEL|=3;

	P0MDOUT |=0x1;						//conf GPIO P0 as CLKOUT
	P0MDIN 	|=0x1;

	XBR0	|=0x8;
}
