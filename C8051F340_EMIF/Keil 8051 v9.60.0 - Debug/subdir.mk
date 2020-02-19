################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC0.c \
../EMIF.c \
../EXTI.c \
../GPIO.c \
../Oscillator.c \
../UART.c \
../main.c 

OBJS += \
./ADC0.OBJ \
./EMIF.OBJ \
./EXTI.OBJ \
./GPIO.OBJ \
./Oscillator.OBJ \
./UART.OBJ \
./main.OBJ 


# Each subdirectory must supply rules for building sources it contributes
%.OBJ: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine "/home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/BIN/C51" "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

ADC0.OBJ: /home/vyldram/Git/C8051F340/C8051F340_EMIF/ADC0.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/Cygnal/c8051F340.h

EMIF.OBJ: /home/vyldram/Git/C8051F340/C8051F340_EMIF/EMIF.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/Cygnal/c8051F340.h

EXTI.OBJ: /home/vyldram/Git/C8051F340/C8051F340_EMIF/EXTI.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/c8051F340.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/compiler_defs.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/si_toolchain.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/INTRINS.H /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/Cygnal/c8051F340.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/stdbool.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/stdint.h

GPIO.OBJ: /home/vyldram/Git/C8051F340/C8051F340_EMIF/GPIO.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/Cygnal/c8051F340.h

Oscillator.OBJ: /home/vyldram/Git/C8051F340/C8051F340_EMIF/Oscillator.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/c8051F340.h

UART.OBJ: /home/vyldram/Git/C8051F340/C8051F340_EMIF/UART.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/c8051F340.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/compiler_defs.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/si_toolchain.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/INTRINS.H /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/Cygnal/c8051F340.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/stdbool.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/stdint.h

main.OBJ: /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/c8051F340.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/compiler_defs.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/si_toolchain.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/INTRINS.H /home/vyldram/Git/C8051F340/C8051F340_EMIF/Oscillator.h /home/vyldram/Git/C8051F340/C8051F340_EMIF/GPIO.h /home/vyldram/Git/C8051F340/C8051F340_EMIF/ADC0.h /home/vyldram/Git/C8051F340/C8051F340_EMIF/EXTI.h /home/vyldram/Git/C8051F340/C8051F340_EMIF/UART.h /home/vyldram/Git/C8051F340/C8051F340_EMIF/EMIF.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/stdbool.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/stdint.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/Cygnal/c8051F340.h


