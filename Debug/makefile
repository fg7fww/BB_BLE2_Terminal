################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
BB_BLE2_Terminal.hex \


# All Target
all: BB_BLE2_Terminal.elf secondary-outputs

# Tool invocations
BB_BLE2_Terminal.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -T "C:\Program Files (x86)\ON Semiconductor\RSL10 SDK\eclipse\../configuration/sections.ld" -nostartfiles -Xlinker --gc-sections -L"C:/Users/fg7fww/_Install/App/DemoBoards/RSL10/Packages_RSL10_2.0/ONSemiconductor/RSL10/2.0.0//lib/release" -L"C:/Users/fg7fww/_Install/App/DemoBoards/RSL10/Packages_RSL10_2.0/ONSemiconductor/RSL10/2.0.0//lib/ble_core/release" -L"C:/Users/fg7fww/_Install/App/DemoBoards/RSL10/Packages_RSL10_2.0/ONSemiconductor/RSL10/2.0.0//lib/ble_profiles/release" -Wl,-Map,"BB_BLE2_Terminal.map" --specs=nano.specs -o "BB_BLE2_Terminal.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BB_BLE2_Terminal.hex: BB_BLE2_Terminal.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "BB_BLE2_Terminal.elf"  "BB_BLE2_Terminal.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) BB_BLE2_Terminal.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH)

.PHONY: all clean dependents

-include ../makefile.targets
