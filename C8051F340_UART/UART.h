/*
 * UART.h
 *
 *  Created on: 12/02/2020
 *      Author: vyldram
 */

#ifndef UART_H_
#define UART_H_

#include <SiLABS\c8051F340.h>
#include <SiLABS\shared\si8051Base\compiler_defs.h>
#include <SiLABS\shared\si8051Base\si_toolchain.h>
#include <INTRINS.H>
#include <Cygnal\c8051F340.h>

#define UART0_TXMAX (0x4u)
#define UART0_RXMAX (0x4u)

typedef enum{
	TIMER1_enOK,
	TIMER1_enERROR
}TIMER1_nStatus;

typedef enum{
	UART0_enOK,
	UART0_enERROR
}UART0_nStatus;

INTERRUPT_PROTO(UART0_ISR, INTERRUPT_UART0);

UART0_nStatus UART0_vInit(unsigned long u32BaudRate);
void UART0_vSend(unsigned char u8Value);

TIMER1_nStatus TIMER1_vInit(unsigned long u32BaudRate);

#endif /* UART_H_ */
