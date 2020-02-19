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
unsigned short display[4]={0,0,0,0};

void main (void)
{
	unsigned short ADCnumber=0; //variable que sirve para obtenel el nibble apropiado
	unsigned short mean=0;
	unsigned short value=0;
	unsigned char cont=0;

	PCA0MD &= ~0x40;		// WDTE = 0 (clear watchdog timer enable)
	PFE0CN |=0x20;			//Enable Pre-fetch
	FLSCL|=0x10;			//increase wait state


	Oscillator_vInit(Oscillator_enSYSCLKSourceMult4);// Initialize Oscillator
	UART0_enInit(9600);
	//GPIO_vInit(); // Initialize Port I/O
	ADC0_vInit();
	TIMER0_vInit();

	EA=1;
	while (1)
	{
		ADCnumber=ADC0_u16Sample();
		mean+=ADCnumber;
		if(cont >=32)
		{
			mean/=32;
			value=mean;
			display[0]=mean%10;
			mean/=10;
			display[1]=mean%10;
			mean/=10;
			display[2]=mean%10;
			mean/=10;
			display[3]=mean%10;
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

			UART0_vSend(0x30+display[3]);
			UART0_vSend(0x30+display[2]);
			UART0_vSend(0x30+display[1]);
			UART0_vSend(0x30+display[0]);
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
