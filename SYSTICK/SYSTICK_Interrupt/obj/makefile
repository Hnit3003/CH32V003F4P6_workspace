################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
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
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
SYSTICK_Interrupt.hex \

SECONDARY_LIST += \
SYSTICK_Interrupt.lst \

SECONDARY_SIZE += \
SYSTICK_Interrupt.siz \


# All Target
all: SYSTICK_Interrupt.elf secondary-outputs

# Tool invocations
SYSTICK_Interrupt.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "D:\CH32V003F4P6_Workspace\SYSTICK\SYSTICK_Interrupt\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"SYSTICK_Interrupt.map" --specs=nano.specs --specs=nosys.specs -o "SYSTICK_Interrupt.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintf
	@	@
SYSTICK_Interrupt.hex: SYSTICK_Interrupt.elf
	@	riscv-none-embed-objcopy -O ihex "SYSTICK_Interrupt.elf"  "SYSTICK_Interrupt.hex"
	@	@
SYSTICK_Interrupt.lst: SYSTICK_Interrupt.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "SYSTICK_Interrupt.elf" > "SYSTICK_Interrupt.lst"
	@	@
SYSTICK_Interrupt.siz: SYSTICK_Interrupt.elf
	@	riscv-none-embed-size --format=berkeley "SYSTICK_Interrupt.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) SYSTICK_Interrupt.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
