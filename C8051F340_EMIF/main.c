/*
 * main.c
 *
 *  Created on: 13/01/2020
 *      Author: vyldram
 */

#include <SiLABS\c8051F340.h>
#include <SiLABS\shared\si8051Base\compiler_defs.h>
#include <SiLABS\shared\si8051Base\si_toolchain.h>
#include <INTRINS.H>

#include <CONV.h>

#include <Oscillator.h>
#include <GPIO.h>
#include <ADC0.h>
#include <EXTI.h>
#include <UART.h>
#include <EMIF.h>

INTERRUPT_PROTO(TIMER0_ISR, INTERRUPT_TIMER0);

void TIMER0_vInit(void);

unsigned char Timer0_Count=0;
unsigned char Timer0_OF=0;
unsigned char Timer0Refresh=1;
unsigned short display[5]={0,0,0,0,0};

xdata unsigned char pu8ExternalRam[1000] _at_ 0x8;
xdata unsigned char pu8ExternalRam1[1000] _at_ 0x800;
xdata unsigned short pu16ExternalRam2[0x1000] _at_ 0x1000;

void main (void)
{
	unsigned short ADCnumber=0; //variable que sirve para obtenel el nibble apropiado
	unsigned short mean=0;
	unsigned short value=0;
	unsigned char cont=0;

	PCA0MD &= ~0x40;		// WDTE = 0 (clear watchdog timer enable)
	PFE0CN |=0x20;			//Enable Pre-fetch
	FLSCL|=0x10;			//increase wait state


	EMIF_vInit();
	Oscillator_vInit(Oscillator_enSYSCLKSourceMult4);// Initialize Oscillator
	UART0_enInit(115200);
	ADC0_vInit();
	TIMER0_vInit();

	EA=1;

	UART0_u16Print((unsigned char*)"Fill XRAM off chip: \n\r");
	for(value=0;(unsigned short)value<(unsigned short)0x1000;value++)
	{
		pu16ExternalRam2[value]=value;
	}

	UART0_u16Print((unsigned char*)"Verify XRAM: \n\r");
	for(value=0;(unsigned short)value<(unsigned short)0x1000;value++)
	{
		UART0_u16Print((unsigned char*)"Direccion: ");
		CONV__u8HexToString((unsigned short)&pu16ExternalRam2[value],(char*)display);
		UART0_u16Print((unsigned char*)display);
		UART0_u16Print((unsigned char*)"   \n\rValor: ");
		CONV__u8HexToString((unsigned long)value,(char*)display);
		UART0_u16Print((unsigned char*)display);
		UART0_u16Print((unsigned char*)"=(?) ");
		CONV__u8HexToString((unsigned long)pu16ExternalRam2[value],(char*)display);
		UART0_u16Print((unsigned char*)display);

		if(pu16ExternalRam2[value]!=value)
		{
			UART0_u16Print((unsigned char*)" Error");
		}
		UART0_u16Print((unsigned char*)"\n\r\n\r");
	}
	while (1)
	{
		ADCnumber=ADC0_u16Sample();
		mean+=ADCnumber;
		if(cont >=32)
		{
			mean/=32;
			value=mean;
			mean=0;
			cont=0;
			if ((unsigned short)value < 0x200)                    // If switch depressed
			{
				UART0_u16Print((unsigned char*)"LED ON  ");
			}
			else
			{
				UART0_u16Print((unsigned char*)"LED OFF ");
			}
			CONV__u8UIntToString((unsigned long)value,(char*)display);
			UART0_u16Print((unsigned char*)display);
			UART0_u16Print((unsigned char*)"\n\r");
		}
		cont++;
	}                                   // end of while(1)
}



void TIMER0_vInit()
{
	CKCON&=~0x3;
	CKCON|=2;	//sysclk/48= 1MHz
	CKCON&=~0x4; //clk = sysclk/div

	TMOD&=~0x3;
	TMOD|=2; //TIM0 autoreload
	TMOD&=~0x4; //TIM0 timer function
	TMOD&=~0x8; //timer active without external pin
	TH0=255-100; //100 count, 1M/100 = 10KHz= 100us , 0.1ms
	TL0=255-100;
	TCON&=~0x20; //clear TIM0 Overflow flag
	ET0=1; //enable TIM0 interrupt
	TCON|=0x10; //enable TIM0
}



INTERRUPT(TIMER0_ISR, INTERRUPT_TIMER0)
{
	Timer0_Count++;
	Timer0_Count&=0x3;
}
