################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c 

OBJS += \
./main.OBJ 


# Each subdirectory must supply rules for building sources it contributes
%.OBJ: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine "/home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/BIN/C51" "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

main.OBJ: /home/vyldram/SimplicityStudio_v4/developer/toolchains/keil_8051/9.60/INC/Cygnal/c8051F340.h


