################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v00x_it.c \
../User/dma.c \
../User/main.c \
../User/ring_buffer.c \
../User/system_ch32v00x.c \
../User/uart.c 

OBJS += \
./User/ch32v00x_it.o \
./User/dma.o \
./User/main.o \
./User/ring_buffer.o \
./User/system_ch32v00x.o \
./User/uart.o 

C_DEPS += \
./User/ch32v00x_it.d \
./User/dma.d \
./User/main.d \
./User/ring_buffer.d \
./User/system_ch32v00x.d \
./User/uart.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\CH32V003F4P6_Workspace\UART_DMA\Debug" -I"D:\CH32V003F4P6_Workspace\UART_DMA\Core" -I"D:\CH32V003F4P6_Workspace\UART_DMA\User" -I"D:\CH32V003F4P6_Workspace\UART_DMA\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

