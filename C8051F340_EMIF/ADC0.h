/*
 * ADC.h
 *
 *  Created on: 09/02/2020
 *      Author: vyldram
 */

#ifndef ADC0_H_
#define ADC0_H_

#include <Cygnal\c8051F340.h>

void ADC0_vInit(void);
unsigned short ADC0_u16Sample(void);


#endif /* ADC0_H_ */
