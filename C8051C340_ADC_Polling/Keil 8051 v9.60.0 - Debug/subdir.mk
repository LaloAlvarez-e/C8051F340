################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC0.c \
../EXTI.c \
../GPIO.c \
../Oscillator.c \
../main.c 

OBJS += \
./ADC0.OBJ \
./EXTI.OBJ \
./GPIO.OBJ \
./Oscillator.OBJ \
./main.OBJ 


# Each subdirectory must supply rules for building sources it contributes
%.OBJ: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine "/home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/BIN/C51" "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

ADC0.OBJ: /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/ADC0.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/Cygnal/c8051F340.h

EXTI.OBJ: /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/EXTI.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/c8051F340.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/compiler_defs.h /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/external_copied_files/si_toolchain.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/INTRINS.H /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/Cygnal/c8051F340.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/stdbool.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/stdint.h /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/external_copied_files/stdint.h /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/external_copied_files/stdbool.h

GPIO.OBJ: /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/GPIO.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/Cygnal/c8051F340.h

Oscillator.OBJ: /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/Oscillator.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/c8051F340.h

main.OBJ: /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/c8051F340.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/compiler_defs.h /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/external_copied_files/si_toolchain.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/INTRINS.H /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/Oscillator.h /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/GPIO.h /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/ADC0.h /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/EXTI.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/stdbool.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/shared/si8051Base/stdint.h /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/external_copied_files/stdint.h /home/vyldram/Git/C8051F340/C8051C340_ADC_Polling/external_copied_files/stdbool.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/Cygnal/c8051F340.h


