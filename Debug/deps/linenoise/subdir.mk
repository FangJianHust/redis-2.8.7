################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../deps/linenoise/linenoise.o 

C_SRCS += \
../deps/linenoise/example.c \
../deps/linenoise/linenoise.c 

OBJS += \
./deps/linenoise/example.o \
./deps/linenoise/linenoise.o 

C_DEPS += \
./deps/linenoise/example.d \
./deps/linenoise/linenoise.d 


# Each subdirectory must supply rules for building sources it contributes
deps/linenoise/%.o: ../deps/linenoise/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


