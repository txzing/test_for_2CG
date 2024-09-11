################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lwip_servers/lwip_common.c \
../src/lwip_servers/tcp_cmd.c \
../src/lwip_servers/tcp_update.c \
../src/lwip_servers/udp_cmd.c \
../src/lwip_servers/udp_update.c 

OBJS += \
./src/lwip_servers/lwip_common.o \
./src/lwip_servers/tcp_cmd.o \
./src/lwip_servers/tcp_update.o \
./src/lwip_servers/udp_cmd.o \
./src/lwip_servers/udp_update.o 

C_DEPS += \
./src/lwip_servers/lwip_common.d \
./src/lwip_servers/tcp_cmd.d \
./src/lwip_servers/tcp_update.d \
./src/lwip_servers/udp_cmd.d \
./src/lwip_servers/udp_update.d 


# Each subdirectory must supply rules for building sources it contributes
src/lwip_servers/%.o: ../src/lwip_servers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v8 gcc compiler'
	aarch64-none-elf-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -IC:/Users/txzing/Desktop/test_for_2cg/golden/vitis/sdk_workspace/system_wrapper/export/system_wrapper/sw/system_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


