################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
../SILABS_STARTUP.A51 

C_SRCS += \
../main.c 

OBJS += \
./SILABS_STARTUP.OBJ \
./main.OBJ 


# Each subdirectory must supply rules for building sources it contributes
%.OBJ: ../%.A51
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	wine "/home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/BIN/AX51" "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

%.OBJ: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine "/home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/BIN/C51" "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

main.OBJ: /home/vyldram/SimplicityStudio_v4/developer/Device/C8051F340/inc/c8051F340.h /home/vyldram/SimplicityStudio_v4/developer/Device/shared/si8051Base/si_toolchain.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/INTRINS.H /home/vyldram/SimplicityStudio_v4/developer/Device/shared/si8051Base/stdint.h /home/vyldram/SimplicityStudio_v4/developer/Device/shared/si8051Base/stdbool.h


