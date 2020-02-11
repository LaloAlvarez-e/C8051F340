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

#define CE0 (0x10) //P0.4 = Com0
#define CE1 (0x20) //P0.5 = Com1
#define CE2 (0x40) //P0.6 = Com2
#define CE3 (0x80) //P0.7 = Com3

#define PCE P0 //P1 comunes



//definciones para imprimir numeros en un display de Anodo Común
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
 SEG_N8,SEG_N9//,SEG_NA,SEG_NB,SEG_NC,SEG_ND,SEG_NE,SEG_NF
};

const unsigned char comunes[4]=
{
 CE0,CE1,CE2,CE3
};


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
	unsigned short numero=0; //variable ue sirve para obtenel el nibble apropiado
	unsigned short mean=0;
	unsigned char cont=0;
	unsigned char i=0; //variable para el ciclo de obtencion de los 4 valores
	unsigned short j=0; //variable del retardo intermedio entre los display
	unsigned short aux=0; //variable para guardar los nibbles restantes

	PCA0MD &= ~0x40;		// WDTE = 0 (clear watchdog timer enable)
	PFE0CN |=0x20;			//Enable Pre-fetch
	FLSCL|=0x10;			//increase wait state


	Oscillator_vInit(Oscillator_enSYSCLKSourceMult4);// Initialize Oscillator
	GPIO_vInit(); // Initialize Port I/O
	ADC0_vInit();

	while (1)
	{
		numero=ADC0_vSample();
		mean+=numero;
		if(cont >=32)
		{
			mean/=32;


			if ((unsigned short)mean < 0x200)                    // If switch depressed
			{
				LED1 = 1;                     // Turn on LED
				var10=0;

			}
			else
			{
				LED1 = 0;                     // Else, turn it off
				var10=1;
			}
			aux=numero;
			for(i=0;i<4;i++) //ciclo necesario para imprimir a los 4 display
			{
				for(j=0;j<8000;j++);//retardo necesario para evitar interferencia entre dsplay
				PCE&=~0xF0;
				aux=mean%10;
				PSEG=codificacion[aux];//manda la codificacion del numero
				mean/=10; //obtiene el siguiente nibble de menor peso

				PCE|=comunes[i];//selecciona cual Display se va a modificar o visualizar
		   }
		   mean=0;
		   cont=0;
		}

		if (SW2 == 0)                    // If switch depressed
		{
			LED2 = 1;                     // Turn on LED
		}
		else
		{
			LED2 = 0;                     // Else, turn it off
		}
		cont++;
	}                                   // end of while(1)
}



