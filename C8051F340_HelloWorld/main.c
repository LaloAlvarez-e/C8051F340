/*
 * main.c
 *
 *  Created on: 18/01/2020
 *      Author: vyldram
 */
#include <Cygnal\c8051F340.h>


/*
 * Overview:
 * Watch Dog Disabled
 * Configuration of P2.0 and P2.1 as Digital Input (Open-Drain)
 * Configuration of P2.2 and P2.2 as Digital Output (Push-Pull)
 *
 * P2.0 and P2.1 are connected to 2 switches from development boars
 * P2.2 and P2.3 are connected to 2 LED
 *
 * Functionality:
 *
 * When the Switch connected to P2.0 (switch1) is pressed the LED in P2.2 (LED1) is turned ON,
 * otherwise LED is OFF
 * When Switch connected to P2.1 (switch2) is pressed, LED in P2.3 (LED2) change its state.
 */

/* P2 is the definitions for Port2 value, this SFR has the property of Bit addressing
 * for this reason, each Pin of Port2 can be accessing independently with the directive sbit
 */

sbit bSwitch1 = P2^0; // 0xA0+0 definition for input value of Switch1
sbit bSwitch2 = P2^1;// 0xA1 definition for input value of Switch2
sbit bLED1 = P2^2;// 0xA2 definition for output value of LED1
sbit bLED2 = P2^3;// 0xA3 definition for outpuy value of LED2

#define SWITCH1_PIN (0x1u) // (1<<0)
#define SWITCH2_PIN (0x2u) // (1<<1)
#define LED1_PIN (0x4u) // (1<<2)
#define LED2_PIN (0x8u) //(1<<3)

bdata bStatusPin;
sbit sSwitch2LastValue = bStatusPin^0;

void main(void)
{
	unsigned short i=0;

	while(1)
	{
		if(bSwitch1 == 0) //if switch1 is pressed LED1 is turned ON otherwise LED1 is turned OFF
		{
			bLED1=1;
		}
		else
		{
			bLED1=0;

		}
		/*
		 * If switch2 value is different from the latest value, then LEd 2 change its value.
		 */
		if(sSwitch2LastValue != bSwitch2)
		{
			sSwitch2LastValue=bSwitch2;
			if(sSwitch2LastValue == 0)
			{
				bLED2 ^=1;
			}
			for(i=0; (unsigned short)i<(unsigned short)15000;i++); //debounce

		}
	}
}
