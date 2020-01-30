################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Oscillator.c \
../main.c 

OBJS += \
./Oscillator.OBJ \
./main.OBJ 


# Each subdirectory must supply rules for building sources it contributes
%.OBJ: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine "/home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/BIN/C51" "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

Oscillator.OBJ: /home/vyldram/Git/C8051F340/C8051F340_Clock/Oscillator.h /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/c8051F340.h

main.OBJ: /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/SiLABS/c8051F340.h /home/vyldram/Git/C8051F340/C8051F340_Clock/Oscillator.h


