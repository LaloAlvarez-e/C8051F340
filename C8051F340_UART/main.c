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

INTERRUPT_PROTO(TIMER0_ISR, INTERRUPT_TIMER0);

void TIMER0_vInit(void);

//lugar del pin donde se encuentra cada segmento
#define SEG_A (1) //P1.0 = seg A
#define SEG_B (2) //P1.1 = seg B
#define SEG_C (4) //P1.2 = seg C
#define SEG_D (8) //P1.3 = seg D
#define SEG_E (0x10) //P1.4 = seg E
#define SEG_F (0x20) //P1.5 = seg F
#define SEG_G (0x40) //P1.6 = seg G
#define SEG_DP (0x80)//P1.7 = seg DP

#define PSEG P1 //P1 segmentos

#define CE0 (0x1) //P0.0 = Com0
#define CE1 (0x2) //P0.1 = Com1
#define CE2 (0x4) //P0.2 = Com2
#define CE3 (0x8) //P0.3 = Com3

#define PCE P0 //P1 comunes



//definciones para imprimir ADCnumbers en un display de Anodo Común
//para activar un led debemos poner el PIN correspondiente en 0
#define SEG_CL (0xFF) //apaga todos los LED del segmento
#define SEG_N0 ~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F)
#define SEG_N1 ~(SEG_B|SEG_C)
#define SEG_N2 ~(SEG_A|SEG_B|SEG_D|SEG_E|SEG_G)
#define SEG_N3 ~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_G)
#define SEG_N4 ~(SEG_B|SEG_C|SEG_F|SEG_G)
#define SEG_N5 ~(SEG_A|SEG_C|SEG_D|SEG_F|SEG_G)
#define SEG_N6 ~(SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define SEG_N7 ~(SEG_A|SEG_B|SEG_C)
#define SEG_N8 ~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define SEG_N9 ~(SEG_A|SEG_B|SEG_C|SEG_F|SEG_G)
#define SEG_NA ~(SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G)
#define SEG_NB ~(SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define SEG_NC ~(SEG_A|SEG_D|SEG_E|SEG_F)
#define SEG_ND ~(SEG_B|SEG_C|SEG_D|SEG_E|SEG_G)
#define SEG_NE ~(SEG_A|SEG_D|SEG_E|SEG_F|SEG_G)
#define SEG_NF ~(SEG_A|SEG_E|SEG_F|SEG_G)

const unsigned char codificacion[10]=
{
 SEG_N0,SEG_N1,SEG_N2,SEG_N3,SEG_N4,SEG_N5,SEG_N6,SEG_N7,
 SEG_N8,SEG_N9
};

const unsigned char comunes[4]=
{
 CE0,CE1,CE2,CE3
};

sbit LED1 =  P2^2;                     // LED1 ='1' means ON
sbit LED2 =  P2^3;                     // LED2 ='1' means ON

unsigned char Timer0_Count=0;
unsigned char Timer0_OF=0;
unsigned char Timer0Refresh=1;
unsigned short display[4]={0,0,0,0};

void main (void)
{
	unsigned short ADCnumber=0; //variable ue sirve para obtenel el nibble apropiado
	unsigned short mean=0;
	unsigned short value=0;
	unsigned char cont=0;

	PCA0MD &= ~0x40;		// WDTE = 0 (clear watchdog timer enable)
	PFE0CN |=0x20;			//Enable Pre-fetch
	FLSCL|=0x10;			//increase wait state


	Oscillator_vInit(Oscillator_enSYSCLKSourceMult4);// Initialize Oscillator
	UART0_vInit(9600);
	GPIO_vInit(); // Initialize Port I/O
	ADC0_vInit();
	TIMER0_vInit();

	EA=1;
	while (1)
	{
		ADCnumber=ADC0_vSample();
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
				LED1 = 1;                     // Turn on LED
				UART0_vSend((unsigned char)'L');
				UART0_vSend((unsigned char)'E');
				UART0_vSend((unsigned char)'D');
				UART0_vSend((unsigned char)' ');
				UART0_vSend((unsigned char)'O');
				UART0_vSend((unsigned char)'N');
				UART0_vSend((unsigned char)' ');
				UART0_vSend((unsigned char)' ');
			}
			else
			{
				LED1 = 0;                     // Else, turn it off
				UART0_vSend((unsigned char)'L');
				UART0_vSend((unsigned char)'E');
				UART0_vSend((unsigned char)'D');
				UART0_vSend((unsigned char)' ');
				UART0_vSend((unsigned char)'O');
				UART0_vSend((unsigned char)'F');
				UART0_vSend((unsigned char)'F');
				UART0_vSend((unsigned char)' ');
			}

			UART0_vSend(0x30+display[3]);
			UART0_vSend(0x30+display[2]);
			UART0_vSend(0x30+display[1]);
			UART0_vSend(0x30+display[0]);
			UART0_vSend((unsigned char)'\n');
			UART0_vSend((unsigned char)'\r');
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

	P3^=0x80;
	Timer0_Count++;
	Timer0_Count&=0x3;
	PCE&=~0x0F;
	PSEG=codificacion[display[Timer0_Count]];//manda la codificacion del ADCnumber
	PCE|=comunes[Timer0_Count];//selecciona cual Display se va a modificar o visualizar


}
