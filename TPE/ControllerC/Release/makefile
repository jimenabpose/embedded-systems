################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
newSensecar.lss \

FLASH_IMAGE += \
newSensecar.hex \

EEPROM_IMAGE += \
newSensecar.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: newSensecar.elf secondary-outputs

# Tool invocations
newSensecar.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Os -Wl,-gc-sections -o"newSensecar.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm -Wl,-Map,newSensecar.map,--cref -L"/home/jpose/Dropbox/ITBA/embebidos/embededClient/ArduinoCore/Release" -mmcu=atmega328p
	@echo 'Finished building target: $@'
	@echo ' '

newSensecar.lss: newSensecar.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S newSensecar.elf  >"newSensecar.lss"
	@echo 'Finished building: $@'
	@echo ' '

newSensecar.hex: newSensecar.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex newSensecar.elf  "newSensecar.hex"
	@echo 'Finished building: $@'
	@echo ' '

newSensecar.eep: newSensecar.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex newSensecar.elf  "newSensecar.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: newSensecar.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p newSensecar.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) newSensecar.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
