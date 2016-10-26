################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include continua/subdir.mk
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
CrumbTest.lss \

FLASH_IMAGE += \
CrumbTest.hex \

EEPROM_IMAGE += \
CrumbTest.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: CrumbTest.elf secondary-outputs

# Tool invocations
CrumbTest.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,CrumbTest.map -mmcu=atmega128 -o "CrumbTest.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

CrumbTest.lss: CrumbTest.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S CrumbTest.elf  >"CrumbTest.lss"
	@echo 'Finished building: $@'
	@echo ' '

CrumbTest.hex: CrumbTest.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex CrumbTest.elf  "CrumbTest.hex"
	@echo 'Finished building: $@'
	@echo ' '

CrumbTest.eep: CrumbTest.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex CrumbTest.elf  "CrumbTest.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: CrumbTest.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t CrumbTest.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) CrumbTest.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
