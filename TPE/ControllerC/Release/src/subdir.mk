################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CommandProtocolHandler.cpp \
../src/CommunicationManager.cpp \
../src/DigitalPinSensor.cpp \
../src/EthernetInformationProtocolHandler.cpp \
../src/InformationProtocolHandler.cpp \
../src/InformationProtocolTranslator.cpp \
../src/Sensor.cpp \
../src/SensorManager.cpp \
../src/SensorModule.cpp \
../src/commandModule.cpp \
../src/infoModule.cpp \
../src/main.cpp 

OBJS += \
./src/CommandProtocolHandler.o \
./src/CommunicationManager.o \
./src/DigitalPinSensor.o \
./src/EthernetInformationProtocolHandler.o \
./src/InformationProtocolHandler.o \
./src/InformationProtocolTranslator.o \
./src/Sensor.o \
./src/SensorManager.o \
./src/SensorModule.o \
./src/commandModule.o \
./src/infoModule.o \
./src/main.o 

CPP_DEPS += \
./src/CommandProtocolHandler.d \
./src/CommunicationManager.d \
./src/DigitalPinSensor.d \
./src/EthernetInformationProtocolHandler.d \
./src/InformationProtocolHandler.d \
./src/InformationProtocolTranslator.d \
./src/Sensor.d \
./src/SensorManager.d \
./src/SensorModule.d \
./src/commandModule.d \
./src/infoModule.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/usr/share/arduino/hardware/arduino/cores/arduino -I"/home/jpose/Dropbox/ITBA/embebidos/embededClient/newSensecar/hdr" -I/home/jpose/Dropbox/ITBA/embebidos/workspace/sensecar/controller/hdr -I/usr/share/arduino/libraries/Ethernet/utility -I/usr/share/arduino/libraries/Ethernet -I/usr/share/arduino/libraries/SPI -I"/home/jpose/Dropbox/ITBA/embebidos/embededClient/newSensecar" -I/usr/share/arduino/hardware/arduino/variants/standard -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


