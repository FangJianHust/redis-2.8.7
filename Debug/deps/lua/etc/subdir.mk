################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../deps/lua/etc/all.c \
../deps/lua/etc/min.c \
../deps/lua/etc/noparser.c 

OBJS += \
./deps/lua/etc/all.o \
./deps/lua/etc/min.o \
./deps/lua/etc/noparser.o 

C_DEPS += \
./deps/lua/etc/all.d \
./deps/lua/etc/min.d \
./deps/lua/etc/noparser.d 


# Each subdirectory must supply rules for building sources it contributes
deps/lua/etc/%.o: ../deps/lua/etc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


