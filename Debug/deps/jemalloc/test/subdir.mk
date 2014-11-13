################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../deps/jemalloc/test/ALLOCM_ARENA.c \
../deps/jemalloc/test/aligned_alloc.c \
../deps/jemalloc/test/allocated.c \
../deps/jemalloc/test/allocm.c \
../deps/jemalloc/test/bitmap.c \
../deps/jemalloc/test/mremap.c \
../deps/jemalloc/test/posix_memalign.c \
../deps/jemalloc/test/rallocm.c \
../deps/jemalloc/test/thread_arena.c \
../deps/jemalloc/test/thread_tcache_enabled.c 

OBJS += \
./deps/jemalloc/test/ALLOCM_ARENA.o \
./deps/jemalloc/test/aligned_alloc.o \
./deps/jemalloc/test/allocated.o \
./deps/jemalloc/test/allocm.o \
./deps/jemalloc/test/bitmap.o \
./deps/jemalloc/test/mremap.o \
./deps/jemalloc/test/posix_memalign.o \
./deps/jemalloc/test/rallocm.o \
./deps/jemalloc/test/thread_arena.o \
./deps/jemalloc/test/thread_tcache_enabled.o 

C_DEPS += \
./deps/jemalloc/test/ALLOCM_ARENA.d \
./deps/jemalloc/test/aligned_alloc.d \
./deps/jemalloc/test/allocated.d \
./deps/jemalloc/test/allocm.d \
./deps/jemalloc/test/bitmap.d \
./deps/jemalloc/test/mremap.d \
./deps/jemalloc/test/posix_memalign.d \
./deps/jemalloc/test/rallocm.d \
./deps/jemalloc/test/thread_arena.d \
./deps/jemalloc/test/thread_tcache_enabled.d 


# Each subdirectory must supply rules for building sources it contributes
deps/jemalloc/test/%.o: ../deps/jemalloc/test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


