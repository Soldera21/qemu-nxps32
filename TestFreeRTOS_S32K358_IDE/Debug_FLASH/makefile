################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include FreeRTOS/Source/portable/MemMang/subdir.mk
-include FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/subdir.mk
-include FreeRTOS/Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_SIZE += \
TestFreeRTOS_S32K358_IDE.siz \


# All Target
all: TestFreeRTOS_S32K358_IDE.elf secondary-outputs

# Tool invocations
TestFreeRTOS_S32K358_IDE.elf: $(OBJS) D:/Programmazione/S32K3/TestFreeRTOS_S32K358_IDE/Project_Settings/Linker_Files/linker_flash_s32k358.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "TestFreeRTOS_S32K358_IDE.elf" "@TestFreeRTOS_S32K358_IDE.args"  $(USER_OBJS)  -lc -lm -lgcc
	@echo 'Finished building target: $@'
	@echo ' '

TestFreeRTOS_S32K358_IDE.siz: TestFreeRTOS_S32K358_IDE.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley TestFreeRTOS_S32K358_IDE.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
