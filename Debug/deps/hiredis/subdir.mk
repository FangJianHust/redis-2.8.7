################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../deps/hiredis/async.o \
../deps/hiredis/hiredis.o \
../deps/hiredis/net.o \
../deps/hiredis/sds.o 

C_SRCS += \
../deps/hiredis/async.c \
../deps/hiredis/dict.c \
../deps/hiredis/example-ae.c \
../deps/hiredis/example-libev.c \
../deps/hiredis/example-libevent.c \
../deps/hiredis/example.c \
../deps/hiredis/hiredis.c \
../deps/hiredis/net.c \
../deps/hiredis/sds.c \
../deps/hiredis/test.c 

OBJS += \
./deps/hiredis/async.o \
./deps/hiredis/dict.o \
./deps/hiredis/example-ae.o \
./deps/hiredis/example-libev.o \
./deps/hiredis/example-libevent.o \
./deps/hiredis/example.o \
./deps/hiredis/hiredis.o \
./deps/hiredis/net.o \
./deps/hiredis/sds.o \
./deps/hiredis/test.o 

C_DEPS += \
./deps/hiredis/async.d \
./deps/hiredis/dict.d \
./deps/hiredis/example-ae.d \
./deps/hiredis/example-libev.d \
./deps/hiredis/example-libevent.d \
./deps/hiredis/example.d \
./deps/hiredis/hiredis.d \
./deps/hiredis/net.d \
./deps/hiredis/sds.d \
./deps/hiredis/test.d 


# Each subdirectory must supply rules for building sources it contributes
deps/hiredis/%.o: ../deps/hiredis/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


