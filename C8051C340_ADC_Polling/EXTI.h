/*
 * EXTI.h
 *
 *  Created on: 09/02/2020
 *      Author: vyldram
 */

#ifndef EXTI_H_
#define EXTI_H_

#include <SiLABS\c8051F340.h>
#include <SiLABS\shared\si8051Base\compiler_defs.h>
#include <si_toolchain.h>
#include <INTRINS.H>
#include <Cygnal\c8051F340.h>

INTERRUPT_PROTO(EXT0_ISR, INTERRUPT_INT0);
INTERRUPT_PROTO(EXT1_ISR, INTERRUPT_INT1);

void EXT0_vInit(void);
void EXT1_vInit(void);

#endif /* EXTI_H_ */
