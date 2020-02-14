/*
 * GPIO.c
 *
 *  Created on: 23/01/2020
 *      Author: vyldram
 */

#include <GPIO.h>




#define SWITCH1_PIN (0x1u) // (1<<0)
#define SWITCH2_PIN (0x2u) // (1<<1)
#define LED1_PIN (0x4u) // (1<<2)
#define LED2_PIN (0x8u) //(1<<3)

bdata bStatusPin;
sbit sSwitch2LastValue = bStatusPin^0;


void GPIO_vInit(void)
{
	/*LED and Switches configured as Digital Input*/
	P2MDIN|=(SWITCH1_PIN|SWITCH2_PIN|LED1_PIN|LED2_PIN);
	P1MDIN=0xFF;
	P0MDIN|=0x0F;
	P3MDIN|=0x80;

	/*Switches configured as Open Drain Output*/
	P2MDOUT&=~(SWITCH1_PIN|SWITCH2_PIN);

	/*Switches configured as push-pull Output*/
	P2MDOUT|=(LED1_PIN|LED2_PIN);
	P1MDOUT=0xFF;
	P0MDOUT|=0x0F;
	P3MDOUT|=0x80;

	/*LED and Switches skipped from CrossBar*/
	P2SKIP|=(SWITCH1_PIN|SWITCH2_PIN|LED1_PIN|LED2_PIN);
	P1SKIP=0xFF;
	P0SKIP|=0x0F;
	P3SKIP|=0x80;


	/*LED initial State as LOW value*/
	P2&=~(LED1_PIN|LED2_PIN);
	P1=0;
	P0&=~0x0F;
	P3&=~0x80;

	/*Switches configured as high impedance to avoid short circuits on inputs*/
	P2|=(SWITCH1_PIN|SWITCH2_PIN);
	sSwitch2LastValue = 1;

	P2MDIN |=0x4;						//Conf P2.2 as Output, Push-Pull Initial LOW
	P2MDOUT|=0x4;
	P2SKIP|=0x4;
	P2&=~0x4;


	/* Activate SYSCLK output*/
	XBR0|=0x8;

	/*Wake pull-up enable in all pins except on output and analog input*/
	XBR1&=~0x80;

	/*CrossBar enable*/
	XBR1|=0x40;
}
