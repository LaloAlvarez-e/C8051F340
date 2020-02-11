/*
 * Oscillator.c
 *
 *  Created on: 21/01/2020
 *      Author: vyldram
 */

#include "Oscillator.h"


void Oscillator_vInit (Oscillator_nSYSCLKSource nSource)
{

	switch(nSource)
	{
	case Oscillator_enSYSCLKSourceIOSC: //12MHz
		Oscillator_vHighFrecInit(Oscillator_enDiv1);
		break;
	case Oscillator_enSYSCLKSourceMult2: //24MHz
	case Oscillator_enSYSCLKSourceMult4: //48MHz
		Oscillator_vMultiplierFrecInit(Oscillator_enMultSourceIOSC);
		break;
	case Oscillator_enSYSCLKSourceLF:  //120KHz
		Oscillator_vLowFrecInit(Oscillator_enDiv1);
		break;
	case Oscillator_enSYSCLKSourceEOSC:
	default:
		return;//External Oscillator Init

	}

	CLKSEL&=~0x7;						//set SYSCLK source
	CLKSEL|=(unsigned char)nSource;
}

void Oscillator_vMultiplierFrecInit (Oscillator_nMultSource nSource)
{
	unsigned short i=0;
	/* Enable 4x multiplier and select it as SYSCLK     */

	CLKMUL =0;							//Disable Multiplier functionality
	CLKMUL |=((unsigned char)nSource);	//multiplier source Internal OSC
	CLKMUL |= 0x80;						//Enable Multiplier
	for (i=0; i<50000; i++);			//Delay needed after enable Multiplier
	CLKMUL|=0xC0;						//Initialize Clock Multiplier
	while((CLKMUL & 0x20) == 0);		//Wait until Multiplier Ready
}

void Oscillator_vLowFrecInit (Oscillator_nDiv nDiv)
{
	/* Enable Low Frequency Oscillator     */

	OSCLCN =0;							//Disable Low frequency Oscillator functionality
	OSCLCN|=(unsigned char)nDiv;						///divider 1

	OSCLCN |= 0x80;						//Enable Low Freq Oscillator
	while((OSCLCN & 0x40) == 0);		//Wait until Low Frequency Oscillator Ready
}


void Oscillator_vHighFrecInit (Oscillator_nDiv nDiv)
{
	/* Enable High Frequency Oscillator     */
	OSCICN|=(unsigned char)nDiv;				///divider 1
}
