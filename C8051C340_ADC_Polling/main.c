/*
 * main.c
 *
 *  Created on: 13/01/2020
 *      Author: vyldram
 */

#include <SiLABS\c8051F340.h>
#include <si_toolchain.h>
#include <INTRINS.H>


sbit SW1  =  P2^0;                     // SW1 ='0' means switch pressed
sbit SW2  =  P2^1;                     // SW2 ='0' means switch pressed
sbit LED1 =  P2^2;                     // LED1 ='1' means ON
sbit LED2 =  P2^3;                     // LED2 ='1' means ON

void OSCILLATOR_Init (void);
void PORT_Init (void);
void ADC0_Init(void);
unsigned short ADC0_Sample(void);
bdata unsigned char  variable1[16];

sbit var10= variable1[0]^0;
data unsigned char  variable2[50];
idata unsigned char  variable3[90];
pdata unsigned char  variable4[200];

void main (void)
{
   PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer
                                       // enable)

   PORT_Init();                        // Initialize Port I/O
   OSCILLATOR_Init ();                 // Initialize Oscillator
   ADC0_Init();

   while (1)
   {
      if ((unsigned short)ADC0_Sample() < 0x300)                    // If switch depressed
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


void ADC0_Init(void)
{
	P3MDIN&=~0x1; //3.0 as analog input
	P3SKIP|=0x1;  //skip 3.0 crossbar
	AMX0P = 0x06; //3.0
	AMX0N = 0x1F; //GND
	ADC0CF=0xB8; //maximum sample time and right-jistified
	ADC0CN= 0xC0;
}

unsigned short ADC0_Sample(void)
{
	unsigned short u16Value =0x400;
	ADC0CN|=0x10;
	while((ADC0CN & 0x10));
	u16Value=ADC0H<<8;
	u16Value|=ADC0L;

	return u16Value;
}

void OSCILLATOR_Init (void)
{
	unsigned short i=0;
	OSCICN |= 0x03;                     // Configure internal oscillator for
                                       // its maximum frequency (24 Mhz)
	CLKMUL =0;
	CLKMUL |= 0x80;
	for (i=0; i<50000; i++);
	CLKMUL|=0xC0;
	while((CLKMUL & 0x20) == 0);

	CLKSEL&=~0x7;
	CLKSEL|=3;
}

void PORT_Init (void)
{
   P2MDIN |= 0x0F;                     // Lower four pins on P2 are digital

   P2MDOUT = 0x0C;                     // enable LEDs as push-pull outputs
                                       // enable Switches as open-drain

   P0MDOUT |=0x1;
   P0MDIN |=0x1;


   P2     |= 0x03;                     // Set port latches for P2.0
                                       // and P2.1 to '1'

   XBR1    = 0x40;                     // Enable crossbar and enable
                                       // weak pull-ups

   XBR0		|=0x8;
}


