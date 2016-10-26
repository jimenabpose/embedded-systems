################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
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
libUSART.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: libUSART.a secondary-outputs

# Tool invocations
libUSART.a: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR Archiver'
	avr-ar -r  "libUSART.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

libUSART.lss: libUSART.a
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S libUSART.a  >"libUSART.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: libUSART.a
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t libUSART.a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(ARCHIVES)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) libUSART.a
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
