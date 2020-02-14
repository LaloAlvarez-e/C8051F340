/*
 * ADC.c
 *
 *  Created on: 09/02/2020
 *      Author: vyldram
 */


#include <ADC0.h>

void ADC0_vInit(void)
{
	REF0CN|=0x8; //VCC VREF
	P3MDIN&=~0x1; //3.0 as analog input
	P3SKIP|=0x1;  //skip 3.0 crossbar
	AMX0P = 0x06; //3.0
	AMX0N = 0x1F; //GND
	ADC0CF=0xB8; //maximum sample time and right-jistified
	ADC0CN= 0xC0;
}

unsigned short ADC0_vSample(void)
{
	unsigned short u16Value =0x400;
	ADC0CN|=0x10;
	while((ADC0CN & 0x10));
	u16Value=ADC0H<<8;
	u16Value|=ADC0L;

	return u16Value;
}
