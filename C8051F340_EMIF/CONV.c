/*
 * CONV.c
 *
 *  Created on: 8 mar. 2018
 *      Author: InDev
 */

#include "CONV.h"


uint8_t CONV__u8IntToString(long s64Number, char* pcConv)
{
	xdata char 	pcConvTemp[INT2STRINGMAX]={0}; //longitud maxima de long 12 digitos con signo
	xdata char 	*pcPointerActual = &pcConvTemp[INT2STRINGMAX-1]; //empezamos llenando desde la ultima posicion;
	xdata int32_t s32Num=0;
	xdata int8_t 	s8I=0;
	xdata long s64NumberReg = s64Number;//paso el s32Numero a un registro para aumentar rendimiento
	xdata int8_t 	s8FlagSign=0;

    *pcPointerActual = 0; //guarda el fin de cadena en la ultima posicion
    if( s64NumberReg < 0)
    {
        s64NumberReg*=-1;
        s8FlagSign=1;
    }

    do {
        pcPointerActual--;//se decrementa la posicion donse guardara el valor
        s32Num=s64NumberReg % 10; //obtiene el digito de menor peso
        *pcPointerActual = s32Num  + '0'; //pcConvierte el valor en caracter
        s64NumberReg /= 10;
    }   while((s64NumberReg!=0)&&(pcPointerActual>(pcConvTemp+s8FlagSign))); //mientras exista un digito sigue el ciclo

    if (s8FlagSign==1)
    {
        pcPointerActual--;
        *pcPointerActual = '-';//si el s32Numero es negativo guarda el signo negativo
    }

    s64NumberReg=pcConvTemp+INT2STRINGMAX-1-pcPointerActual;//realiza la resta de cuantos caracteres se utilizaron
    for (s8I = s64NumberReg; s8I>=0; s8I--) //hace un ciclo burbuja optimizado
    {
        ((char *)pcConv)[(uint8_t)s8I] = ((const char *)pcPointerActual)[(uint8_t)s8I];
    }

    return s64NumberReg;
}



uint8_t CONV__u8IntToStringCeros(long s64Number,int8_t s8CerosLeft, char* pcConv)
{
	xdata char 	pcConvTemp[INT2STRINGMAX]={0}; //longitud maxima de long 12 digitos con signo
	xdata char 	*pcPointerActual = &pcConvTemp[INT2STRINGMAX - 1]; //empezamos llenando desde la ultima posicion
	xdata int32_t s32Num=0;
	xdata int8_t 	s8I=0;
	xdata long s64NumberReg = s64Number;//paso el s32Numero a un registro para aumentar rendimiento
	xdata int8_t 	s8FlagSign=0;

    if(s8CerosLeft>(INT2STRINGMAX-2))
    {
        s8CerosLeft=(INT2STRINGMAX-2);
    }

    *pcPointerActual = 0; //guarda el fin de cadena en la ultima posicion
    if( s64NumberReg < 0)
    {
        s64NumberReg*=-1;
        s8FlagSign=1;
    }

    do {
        pcPointerActual--;//se decrementa la posicion donse guardara el valor
        s32Num=s64NumberReg % 10; //obtiene el digito de menor peso
        *pcPointerActual = s32Num  + '0'; //pcConvierte el valor en caracter
        s8CerosLeft--;
        s64NumberReg /= 10;
    }  while((s64NumberReg!=0)&&(pcPointerActual>(pcConvTemp+s8FlagSign))); //mientras exista un digito sigue el ciclo

    while((pcPointerActual>(pcConvTemp+s8FlagSign)) && (s8CerosLeft>0))
    {
        pcPointerActual--;
        *pcPointerActual ='0';
        s8CerosLeft--;
    }
    if (s8FlagSign==1)
    {
        pcPointerActual--;
        *pcPointerActual = '-';//si el s32Numero es negativo guarda el signo negativo
    }
    s64NumberReg=pcConvTemp+INT2STRINGMAX-1-pcPointerActual;//realiza la resta de cuantos caracteres se utilizaron
    for (s8I = s64NumberReg; s8I>=0; s8I--) //hace un ciclo burbuja optimizado
    {
        ((char *)pcConv)[(uint8_t)s8I] = ((const char *)pcPointerActual)[(uint8_t)s8I];
    }

    return s64NumberReg;

}

uint8_t CONV__u8UIntToString(unsigned long u64Number, char* pcConv)
{
	xdata volatile char 		pcConvTemp[INT2STRINGMAX]={0}; //longitud maxima de long 12 digitos con signo
	xdata volatile char 		*pcPointerActual = &pcConvTemp[INT2STRINGMAX - 1]; //empezamos llenando desde la ultima posicion
	xdata volatile int32_t 	s32Num=0;
	xdata volatile int8_t 		s8I=0;
	xdata volatile unsigned long 	u64NumberReg = u64Number;//paso el s32Numero a un registro para aumentar rendimiento

    *pcPointerActual = 0; //guarda el fin de cadena en la ultima posicion
    do {
        pcPointerActual--;//se decrementa la posicion donse guardara el valor
        s32Num=(unsigned long)u64NumberReg % (unsigned long)10ul; //obtiene el digito de menor peso
        *pcPointerActual = (uint8_t)s32Num  + '0'; //pcConvierte el valor en caracter
    }  while((u64NumberReg /= (unsigned long)10ul)); //mientras exista un digito sigue el ciclo

    u64NumberReg=pcConvTemp+INT2STRINGMAX-1-pcPointerActual;//realiza la resta de cuantos caracteres se utilizaron
    for (s8I = (int8_t)u64NumberReg; s8I>=0; s8I--) //hace un ciclo burbuja optimizado
    {
        ((char *)pcConv)[(uint8_t)s8I] = ((char *)pcPointerActual)[(uint8_t)s8I];
    }

    return u64NumberReg;
}



const int8_t ps8HEXA[16]=
{
 '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};
uint8_t CONV__u8HEXToString(unsigned long u64Number, char* pcConv)
{
	xdata uint8_t  pcConvTemp[HEX2STRINGMAX]={0}; //longitud maxima de long 16 digitos
	xdata uint8_t  *pcPointerActual=&pcConvTemp[HEX2STRINGMAX - 1];
	xdata int32_t  s32Num=0;
	xdata int8_t   s8I=0;
	xdata unsigned long u64NumberReg = (unsigned long) u64Number;//paso el s32Numero a un registro para aumentar rendimiento

    *pcPointerActual = 0; //guarda el fin de cadena en la ultima posicion

    do {
        pcPointerActual--;//se decrementa la posicion donse guardara el valor
        s32Num=u64NumberReg&0xF; //obtiene el digito de menor peso
        *pcPointerActual = ps8HEXA[(uint32_t)s32Num]; //convierte el valor en caracter
        u64NumberReg>>=4;
    }  while((u64NumberReg > 0)); //mientras exista un digito sigue el ciclo

    pcPointerActual--;
    *pcPointerActual = 'x';
    pcPointerActual--;
    *pcPointerActual = '0';
    u64NumberReg=pcConvTemp+HEX2STRINGMAX-1-pcPointerActual;//realiza la resta de cuantos caracteres se utilizaron
    for (s8I = u64NumberReg; s8I>=0 ; s8I--) //hace un ciclo burbuja optimizado
    {
        ((uint8_t *)pcConv)[(uint8_t)s8I] = ((const uint8_t *)pcPointerActual)[(uint8_t)s8I];
    }

    return u64NumberReg;
}


