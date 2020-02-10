/*
 * main.c
 *
 *  Created on: 13/01/2020
 *      Author: vyldram
 */

#include <SiLABS\c8051F340.h>
#include <SiLABS\shared\si8051Base\compiler_defs.h>
#include <si_toolchain.h>
#include <INTRINS.H>

#include <Oscillator.h>
#include <GPIO.h>
#include <ADC0.h>
#include <EXTI.h>


sbit SW1  =  P2^0;                     // SW1 ='0' means switch pressed
sbit SW2  =  P2^1;                     // SW2 ='0' means switch pressed
sbit LED1 =  P2^2;                     // LED1 ='1' means ON
sbit LED2 =  P2^3;                     // LED2 ='1' means ON


bdata unsigned char  variable1[3];

sbit var10= variable1[0]^0;
data unsigned char  variable2;
idata unsigned char  variable3;
pdata unsigned char  variable4;

void main (void)
{
	PCA0MD &= ~0x40;		// WDTE = 0 (clear watchdog timer enable)
	PFE0CN |=0x20;			//Enable Pre-fetch
	FLSCL|=0x10;			//increase wait state


	Oscillator_vInit(Oscillator_enSYSCLKSourceMult4);// Initialize Oscillator
	GPIO_vInit(); // Initialize Port I/O
	ADC0_vInit();

	while (1)
	{
		if ((unsigned short)ADC0_vSample() < 0x200)                    // If switch depressed
		{
			LED1 = 1;                     // Turn on LED
			var10=0;

		}
		else
		{
			LED1 = 0;                     // Else, turn it off
			var10=1;
		}

		if (SW2 == 0)                    // If switch depressed
		{
			LED2 = 1;                     // Turn on LED
		}
		else
		{
			LED2 = 0;                     // Else, turn it off
		}
	}                                   // end of while(1)
}



