################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Ej1/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
tp1.lss \

FLASH_IMAGE += \
tp1.hex \

EEPROM_IMAGE += \
tp1.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: tp1.elf secondary-outputs

# Tool invocations
tp1.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,tp1.map -mmcu=atmega644 -o "tp1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

tp1.lss: tp1.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S tp1.elf  >"tp1.lss"
	@echo 'Finished building: $@'
	@echo ' '

tp1.hex: tp1.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex tp1.elf  "tp1.hex"
	@echo 'Finished building: $@'
	@echo ' '

tp1.eep: tp1.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex tp1.elf  "tp1.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: tp1.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega644 tp1.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) tp1.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
