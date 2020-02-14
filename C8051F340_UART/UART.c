/*
 * UART.c
 *
 *  Created on: 12/02/2020
 *      Author: vyldram
 */

#include <UART.h>

pdata uint8_t Uart0_u8TxBuffer[UART0_TXMAX]={0};
volatile uint8_t* Uart0_pu8PutTx=&Uart0_u8TxBuffer[0];
volatile uint8_t* Uart0_pu8GetTx=&Uart0_u8TxBuffer[0];
int8_t  Uart0_s8TxCounter=0;
int8_t  Uart_s8TxInit=0;


pdata uint8_t Uart0_u8RxBuffer[UART0_RXMAX]={0};
volatile uint8_t* Uart0_pu8PutRx=&Uart0_u8RxBuffer[0];
volatile uint8_t* Uart0_pu8GetRx=&Uart0_u8RxBuffer[0];
int8_t  Uart0_s8RxCounter=0;

UART0_nStatus UART0_vInit(unsigned long u32BaudRate)
{
    UART0_nStatus enStatus= UART0_enOK;
    TIMER1_nStatus enStatusTim= TIMER1_enOK;

    /*
     * Initializing GPIO for UART0 (P0.4 TX0, P0.5 RX0)
     */

	/*RX and TX configured as Digital Input*/
	P0MDIN|=0x30;

	/*RX configured as Open Drain Output*/
	P0MDOUT&=~(0x20);
	P0|=(0x20);

	/*TX configured as push-pull Output*/
	P0MDOUT|=0x10;

	/*TX and RX is not skipped from CrossBar*/
	P0SKIP&=~0x30;


	/* Activate UART crossbar*/
	XBR0|=0x1;

	/*CrossBar enable*/
	XBR1|=0x40;

	enStatusTim =TIMER1_vInit(u32BaudRate);
	if(enStatusTim == TIMER1_enERROR)
		return UART0_enERROR;

	/* UART0 configuration
	 * 8-bit
	 * Multiprocessor disable
	 * UART0 reception enable
	 */
	SCON0=0x40; //inital value
	SCON0|=0x10;

	return UART0_enOK;
}

void UART0_vSend(unsigned char u8Value)
{
	SBUF0=u8Value;
	while((SCON0&0x2)==0);
	SCON0&=~0x2;
}

TIMER1_nStatus TIMER1_vInit(unsigned long u32BaudRate)
{
	float fCont=500000.0; //500Khz 1MHz/2
	uint8_t u8Cont=0; //500Khz 1MHz/2
	float fCont24=24000000.0; //24Mhz 48MHz/2
	uint8_t u8Cont24=0; //500Khz 1MHz/2
	float fError=0.0;
	float fError24=0.0;

	uint8_t u8Value=0;

	if(u32BaudRate<94000)
	{
		fCont/=(float)u32BaudRate;
		fCont+=0.5;
		u8Cont= (uint8_t)fCont;
		u8Value=256-(uint8_t)u8Cont;
		CKCON&=~0x8; //TIM1 clk = sysclk/div
	}
	else if(u32BaudRate<500000)
	{
		fCont/=(float)u32BaudRate;
		u8Cont= (uint8_t)fCont;
		fError= fCont- (float)u8Cont;

		fCont24/=(float)u32BaudRate;
		u8Cont24= (uint8_t)fCont24;
		fError24= fCont24- (float)u8Cont24;

		if(fError < fError24)
		{
			fCont+=0.5;
			u8Cont= (uint8_t)fCont;
			CKCON&=~0x8; //TIM1 clk = sysclk/div
		}
		else
		{
			fCont24+=0.5;
			u8Cont= (uint8_t)fCont24;

			CKCON|=0x8; //TIM1 clk = sysclk
		}


	}
	else if(u32BaudRate<=1000000)
	{
		fCont24/=(float)u32BaudRate;
		fCont24+=0.5;
		u8Cont= (uint8_t)fCont24;
		CKCON|=0x8; //TIM1 clk = sysclk
	}
	else return TIMER1_enERROR;


	u8Value=256-(uint8_t)u8Cont;

	CKCON&=~0x3;
	CKCON|=2;	//sysclk/48= 1MHz

	TMOD&=~0x30;
	TMOD|=0x20; //TIM1 autoreload
	TMOD&=~0x40; //TIM1 timer function
	TMOD&=~0x80; //timer1 active without external pin


	TH1=u8Value;
	TL1=0;

	TCON|=0x40; //enable TIM1

	return TIMER1_enOK;
}
