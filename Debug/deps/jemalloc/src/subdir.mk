################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../deps/jemalloc/src/arena.o \
../deps/jemalloc/src/atomic.o \
../deps/jemalloc/src/base.o \
../deps/jemalloc/src/bitmap.o \
../deps/jemalloc/src/chunk.o \
../deps/jemalloc/src/chunk_dss.o \
../deps/jemalloc/src/chunk_mmap.o \
../deps/jemalloc/src/ckh.o \
../deps/jemalloc/src/ctl.o \
../deps/jemalloc/src/extent.o \
../deps/jemalloc/src/hash.o \
../deps/jemalloc/src/huge.o \
../deps/jemalloc/src/jemalloc.o \
../deps/jemalloc/src/mb.o \
../deps/jemalloc/src/mutex.o \
../deps/jemalloc/src/prof.o \
../deps/jemalloc/src/quarantine.o \
../deps/jemalloc/src/rtree.o \
../deps/jemalloc/src/stats.o \
../deps/jemalloc/src/tcache.o \
../deps/jemalloc/src/tsd.o \
../deps/jemalloc/src/util.o 

C_SRCS += \
../deps/jemalloc/src/arena.c \
../deps/jemalloc/src/atomic.c \
../deps/jemalloc/src/base.c \
../deps/jemalloc/src/bitmap.c \
../deps/jemalloc/src/chunk.c \
../deps/jemalloc/src/chunk_dss.c \
../deps/jemalloc/src/chunk_mmap.c \
../deps/jemalloc/src/ckh.c \
../deps/jemalloc/src/ctl.c \
../deps/jemalloc/src/extent.c \
../deps/jemalloc/src/hash.c \
../deps/jemalloc/src/huge.c \
../deps/jemalloc/src/jemalloc.c \
../deps/jemalloc/src/mb.c \
../deps/jemalloc/src/mutex.c \
../deps/jemalloc/src/prof.c \
../deps/jemalloc/src/quarantine.c \
../deps/jemalloc/src/rtree.c \
../deps/jemalloc/src/stats.c \
../deps/jemalloc/src/tcache.c \
../deps/jemalloc/src/tsd.c \
../deps/jemalloc/src/util.c \
../deps/jemalloc/src/zone.c 

OBJS += \
./deps/jemalloc/src/arena.o \
./deps/jemalloc/src/atomic.o \
./deps/jemalloc/src/base.o \
./deps/jemalloc/src/bitmap.o \
./deps/jemalloc/src/chunk.o \
./deps/jemalloc/src/chunk_dss.o \
./deps/jemalloc/src/chunk_mmap.o \
./deps/jemalloc/src/ckh.o \
./deps/jemalloc/src/ctl.o \
./deps/jemalloc/src/extent.o \
./deps/jemalloc/src/hash.o \
./deps/jemalloc/src/huge.o \
./deps/jemalloc/src/jemalloc.o \
./deps/jemalloc/src/mb.o \
./deps/jemalloc/src/mutex.o \
./deps/jemalloc/src/prof.o \
./deps/jemalloc/src/quarantine.o \
./deps/jemalloc/src/rtree.o \
./deps/jemalloc/src/stats.o \
./deps/jemalloc/src/tcache.o \
./deps/jemalloc/src/tsd.o \
./deps/jemalloc/src/util.o \
./deps/jemalloc/src/zone.o 

C_DEPS += \
./deps/jemalloc/src/arena.d \
./deps/jemalloc/src/atomic.d \
./deps/jemalloc/src/base.d \
./deps/jemalloc/src/bitmap.d \
./deps/jemalloc/src/chunk.d \
./deps/jemalloc/src/chunk_dss.d \
./deps/jemalloc/src/chunk_mmap.d \
./deps/jemalloc/src/ckh.d \
./deps/jemalloc/src/ctl.d \
./deps/jemalloc/src/extent.d \
./deps/jemalloc/src/hash.d \
./deps/jemalloc/src/huge.d \
./deps/jemalloc/src/jemalloc.d \
./deps/jemalloc/src/mb.d \
./deps/jemalloc/src/mutex.d \
./deps/jemalloc/src/prof.d \
./deps/jemalloc/src/quarantine.d \
./deps/jemalloc/src/rtree.d \
./deps/jemalloc/src/stats.d \
./deps/jemalloc/src/tcache.d \
./deps/jemalloc/src/tsd.d \
./deps/jemalloc/src/util.d \
./deps/jemalloc/src/zone.d 


# Each subdirectory must supply rules for building sources it contributes
deps/jemalloc/src/%.o: ../deps/jemalloc/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


