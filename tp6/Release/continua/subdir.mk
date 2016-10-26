################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../continua/Example.c \
../continua/PWM.c 

OBJS += \
./continua/Example.o \
./continua/PWM.o 

C_DEPS += \
./continua/Example.d \
./continua/PWM.d 


# Each subdirectory must supply rules for building sources it contributes
continua/%.o: ../continua/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=14745600UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


