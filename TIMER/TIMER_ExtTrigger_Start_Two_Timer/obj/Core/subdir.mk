################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\CH32V003F4P6_Workspace\TIMER\TIMER_ExtTrigger_Start_Two_Timer\Debug" -I"D:\CH32V003F4P6_Workspace\TIMER\TIMER_ExtTrigger_Start_Two_Timer\Core" -I"D:\CH32V003F4P6_Workspace\TIMER\TIMER_ExtTrigger_Start_Two_Timer\User" -I"D:\CH32V003F4P6_Workspace\TIMER\TIMER_ExtTrigger_Start_Two_Timer\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
