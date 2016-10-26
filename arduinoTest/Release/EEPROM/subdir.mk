################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/usr/share/arduino/libraries/EEPROM/EEPROM.cpp 

OBJS += \
./EEPROM/EEPROM.o 

CPP_DEPS += \
./EEPROM/EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
EEPROM/EEPROM.o: /usr/share/arduino/libraries/EEPROM/EEPROM.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../arduinoTest/Arduino_Uno/arduino -I../arduinoTest/Arduino_Uno/standard -I../arduinoTest/arduinoTest -I../arduinoTest/arduinoTest/ETHER_28J60 -I../arduinoTest/arduinoTest/etherShield -I../arduinoTest/arduinoTest/Stepper -I../arduinoTest/arduinoTest/Firmata -I../arduinoTest/arduinoTest/SPI -I../arduinoTest/arduinoTest/LiquidCrystal -I../arduinoTest/arduinoTest/SD -I../arduinoTest/arduinoTest/EEPROM -I../arduinoTest/arduinoTest/Servo -I../arduinoTest/arduinoTest/SoftwareSerial -I/home/jpose/Dropbox/ITBA/embebidos/workspace/arduinoTest/arduinoTest/Wire -I../arduinoTest/Wire -I"/usr/share/arduino/libraries/ETHER_28J60" -I"/usr/share/arduino/libraries/Stepper" -I"/usr/share/arduino/libraries/Firmata" -I"/usr/share/arduino/libraries/SPI" -I"/usr/share/arduino/libraries/LiquidCrystal" -I"/usr/share/arduino/libraries/etherShield" -I"/usr/share/arduino/libraries/SD" -I"/usr/share/arduino/libraries/EEPROM" -I"/usr/share/arduino/libraries/Servo" -I"/usr/share/arduino/libraries/SoftwareSerial" -I"/usr/share/arduino/libraries/Wire" -D__IN_ECLIPSE__=1 -DARDUINO=101 -DUSB_PID= -DUSB_VID= -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


