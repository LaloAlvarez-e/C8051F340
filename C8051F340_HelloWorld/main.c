/*
 * main.c
 *
 *  Created on: 18/01/2020
 *      Author: vyldram
 */

//#include <SiLABS\c8051F340.h>
#include <Cygnal\c8051F340.h>

idata unsigned char iData[0xE0-0x30];
xdata unsigned char xData[0x1000-0x00];


bdata unsigned char bData[0x30-0x20];
sbit  bData0_0 =bData[0]^0;
sbit  bData0_1 =bData[0]^1;
sbit  bData0_2 =bData[0]^2;
sbit  bData0_3 =bData[0]^3;

void main(void)
{
	PCA0MD &=~0x40;
	bData0_0=0;
	bData0_1=1;
	bData0_2=0;
	bData0_3=1;
	while(1)
	{
		bData0_0=1;
		bData0_1=0;
		bData0_2=1;
		bData0_3=0;
	}
}
