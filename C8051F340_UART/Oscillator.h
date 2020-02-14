/*
 * Oscillator.h
 *
 *  Created on: 21/01/2020
 *      Author: vyldram
 */

#ifndef OSCILLATOR_H_
#define OSCILLATOR_H_

#include <SiLABS\c8051F340.h>

typedef enum
{
	Oscillator_enDiv8 = 0,
	Oscillator_enDiv4 = 1,
	Oscillator_enDiv2 = 2,
	Oscillator_enDiv1 = 3,
}Oscillator_nDiv;

typedef enum
{
	Oscillator_enMultSourceIOSC = 0,
	Oscillator_enMultSourceEOSC = 1,
	Oscillator_enMultSourceEOSC2 = 2,
}Oscillator_nMultSource;

typedef enum
{
	Oscillator_enSYSCLKSourceIOSC = 0,
	Oscillator_enSYSCLKSourceEOSC = 1,
	Oscillator_enSYSCLKSourceMult2 = 2,
	Oscillator_enSYSCLKSourceMult4 = 3,
	Oscillator_enSYSCLKSourceLF = 4,
}Oscillator_nSYSCLKSource;

void Oscillator_vInit (Oscillator_nSYSCLKSource nSource);
void Oscillator_vLowFrecInit (Oscillator_nDiv nDiv);
void Oscillator_vHighFrecInit (Oscillator_nDiv nDiv);
void Oscillator_vMultiplierFrecInit (Oscillator_nMultSource nSource);

#endif /* OSCILLATOR_H_ */
