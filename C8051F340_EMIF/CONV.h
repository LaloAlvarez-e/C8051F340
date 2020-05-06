/*
 * CONV.h
 *
 *  Created on: 8 mar. 2018
 *      Author: InDev
 */

#ifndef CONV_H_
#define CONV_H_

#include <stdint.h>

#define INT2STRINGMAX 	(21)
#define HEX2STRINGMAX 	(19)
#define OCT2STRINGMAX 	(24)
#define BIN2STRINGMAX 	(40)


typedef enum
{
	CONV_enNAN = -1,
	CONV_enOK = 0,
	CONV_enERROR = 1,
}CONV_nStatus;



uint8_t CONV__u8IntToString(long s64Number, char* pcConv);
uint8_t CONV__u8UIntToString(unsigned long u64Number, char* pcConv);
uint8_t CONV__u8HexToString(unsigned long u64Number, char* pcConv);
uint8_t CONV__u8HEXToString(unsigned long u64Number, char* pcConv);
uint8_t CONV__u8OctToString(unsigned long u64Number, char* pcConv);
uint8_t CONV__u8BinToString(unsigned long u64Number, char* pcConv);
uint8_t CONV__u8IntToStringCeros(long s64Number,int8_t s8CerosLeft, char* pcConv);
uint8_t CONV__u8DIntToString(long s64Number,uint8_t u8Positive,uint8_t u8Padding0,uint8_t u8Deci, char* pcConv);



#endif /* CONV_H_ */
