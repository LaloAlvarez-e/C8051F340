/*
 * EMIF.c
 *
 *  Created on: 16/02/2020
 *      Author: vyldram
 */


#include "EMIF.h"

void EMIF_vInit (void)
{
	short i=0;

	/* External Memory Configuration
	 * USBFA: SRAM USB FIFO cannot be accessible
	 * EMD2: SRAM not multiplexed
	 * EMD0-1: Split mode without bank select
	 */
   	EMI0CF =(0x10)|(0x4);// 0x14;

   	/* HM6264LP-70 from Hitachi has a 70ns of time access (aporx 14 MHz)
   	 *
   	 * Address setup time (read): minimum value is not determined but maximum value is 70ns (14Mhz)
   	 * Address setup time (write): minimum value is 0 and maximum value is 70ns (14Mhz)
   	 * tAA = 0 SYSCLK
   	 * Write pulse width: 3 SYSCLK (62ns)
   	 * Address hold tiome = 1SYSCLK
   	 *
   	 */
   	EMI0TC =(0x8)|(0x1);


   	/*
   	 * EMIF control pins skip from Crossbar and configured as Output push-pull
   	 * All other pins are confifred as push-pull
   	 */

   	P1MDIN|=0xC0; //P1.6 (RD) and P1.7 (WR) as Digital input
   	P2MDIN|=0x1F; // P2.0-P2.4 configured as Digital input (A8-A12)
   	P3MDIN=0xFF;  //P3 configured as Digital Input (A0-A7)
   	P4MDIN=0xFF;  //P4 configured as Digital Input (D0-D7)

   	P1MDOUT|=0xC0; //P1.6 (RD) and P1.7 (WR) as Push-Pull Output
   	P2MDOUT|=0x1F; // P2.0-P2.4 configured as Push-Pull Output (A8-A12)
   	P3MDOUT=0xFF;  //P3 configured as Push-Pull Output (A0-A7)
   	P4MDOUT=0xFF;  //P4 configured as Push-Pull Output (D0-D7)

   	P1SKIP|=0xC0; //P1.6 (RD) and P1.7 (WR) are s kipped from crossbar

   	P1|=0xC0; //P1.6 (RD) and P1.7 (WR) as High Output
   	P2|=0x1F; // P2.0-P2.4 as High Output (A8-A12)
   	P3=0xFF;  //P3 as High Output (A0-A7)
   	P4=0xFF;  //P4 as High Output (D0-D7)

	/*CrossBar enable*/
	XBR1|=0x40;
	//retardo para estabilizar la configuracion
	for (i=0; i<30000; i++);
}
