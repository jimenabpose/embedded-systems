################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include ej2/subdir.mk
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
tp5.lss \

FLASH_IMAGE += \
tp5.hex \

EEPROM_IMAGE += \
tp5.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: tp5.elf secondary-outputs

# Tool invocations
tp5.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,tp5.map -Wl,-u,vfprintf -lprintf_flt -lm -mmcu=atmega644 -o "tp5.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

tp5.lss: tp5.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S tp5.elf  >"tp5.lss"
	@echo 'Finished building: $@'
	@echo ' '

tp5.hex: tp5.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex tp5.elf  "tp5.hex"
	@echo 'Finished building: $@'
	@echo ' '

tp5.eep: tp5.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex tp5.elf  "tp5.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: tp5.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t tp5.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) tp5.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
