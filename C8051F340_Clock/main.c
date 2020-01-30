/*
 * main.c
 *
 *  Created on: 15/01/2020
 *      Author: vyldram
 */

#include <SiLABS\c8051F340.h>
#include <Oscillator.h>


void Port_vInit (void);



void main (void)
{
	unsigned short i=0;
	unsigned char j=0;
	PCA0MD &= ~0x40;		// WDTE = 0 (clear watchdog timer enable)
	PFE0CN |=0x20;			//Enable Pre-fetch
	FLSCL|=0x10;			//increase wait state
	Oscillator_vInit (Oscillator_enSYSCLKSourceMult4);	// Initialize Oscillator
	Port_vInit();			// Initialize Clkout as output

	while (1)
	{
		for(j=0;(unsigned char)j<(unsigned char)100; j++)
		for(i=0;(unsigned short)i<(unsigned short)1000ul; i++);
		P2^=0x4;
	}
}


void Port_vInit(void)
{

	P0MDIN 	|=0x1;						//conf as Digital Input
	P0MDOUT |=0x1;						//conf GPIO P0 as push-pull output


	P2MDIN |=0x4;						//Conf P2.2 as Output, Push-Pull Initial LOW
	P2MDOUT|=0x4;
	P2SKIP|=0x4;
	P2&=~0x4;

	/* Activate SYSCLK output*/
	XBR0	|=0x8;

	/*Wake pull-up enable in all pins except on output and analog input*/
	XBR1&=~0x80;

	/*CrossBar enable*/
	XBR1|=0x40;

}
