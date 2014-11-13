################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/adlist.o \
../src/ae.o \
../src/anet.o 

C_SRCS += \
../src/adlist.c \
../src/ae.c \
../src/ae_epoll.c \
../src/anet.c \
../src/aof.c \
../src/bio.c \
../src/bitops.c \
../src/config.c \
../src/crc64.c \
../src/db.c \
../src/debug.c \
../src/dict.c \
../src/endianconv.c \
../src/intset.c \
../src/lzf_c.c \
../src/lzf_d.c \
../src/memtest.c \
../src/migrate.c \
../src/multi.c \
../src/networking.c \
../src/notify.c \
../src/object.c \
../src/pqsort.c \
../src/pubsub.c \
../src/rand.c \
../src/rdb.c \
../src/redis-benchmark.c \
../src/redis-check-aof.c \
../src/redis-check-dump.c \
../src/redis-cli.c \
../src/redis.c \
../src/release.c \
../src/replication.c \
../src/rio.c \
../src/scripting.c \
../src/sds.c \
../src/sentinel.c \
../src/setproctitle.c \
../src/sha1.c \
../src/slowlog.c \
../src/sort.c \
../src/syncio.c \
../src/t_hash.c \
../src/t_list.c \
../src/t_set.c \
../src/t_string.c \
../src/t_zset.c \
../src/util.c \
../src/ziplist.c \
../src/zipmap.c \
../src/zmalloc.c 

OBJS += \
./src/adlist.o \
./src/ae.o \
./src/ae_epoll.o \
./src/anet.o \
./src/aof.o \
./src/bio.o \
./src/bitops.o \
./src/config.o \
./src/crc64.o \
./src/db.o \
./src/debug.o \
./src/dict.o \
./src/endianconv.o \
./src/intset.o \
./src/lzf_c.o \
./src/lzf_d.o \
./src/memtest.o \
./src/migrate.o \
./src/multi.o \
./src/networking.o \
./src/notify.o \
./src/object.o \
./src/pqsort.o \
./src/pubsub.o \
./src/rand.o \
./src/rdb.o \
./src/redis-benchmark.o \
./src/redis-check-aof.o \
./src/redis-check-dump.o \
./src/redis-cli.o \
./src/redis.o \
./src/release.o \
./src/replication.o \
./src/rio.o \
./src/scripting.o \
./src/sds.o \
./src/sentinel.o \
./src/setproctitle.o \
./src/sha1.o \
./src/slowlog.o \
./src/sort.o \
./src/syncio.o \
./src/t_hash.o \
./src/t_list.o \
./src/t_set.o \
./src/t_string.o \
./src/t_zset.o \
./src/util.o \
./src/ziplist.o \
./src/zipmap.o \
./src/zmalloc.o 

C_DEPS += \
./src/adlist.d \
./src/ae.d \
./src/ae_epoll.d \
./src/anet.d \
./src/aof.d \
./src/bio.d \
./src/bitops.d \
./src/config.d \
./src/crc64.d \
./src/db.d \
./src/debug.d \
./src/dict.d \
./src/endianconv.d \
./src/intset.d \
./src/lzf_c.d \
./src/lzf_d.d \
./src/memtest.d \
./src/migrate.d \
./src/multi.d \
./src/networking.d \
./src/notify.d \
./src/object.d \
./src/pqsort.d \
./src/pubsub.d \
./src/rand.d \
./src/rdb.d \
./src/redis-benchmark.d \
./src/redis-check-aof.d \
./src/redis-check-dump.d \
./src/redis-cli.d \
./src/redis.d \
./src/release.d \
./src/replication.d \
./src/rio.d \
./src/scripting.d \
./src/sds.d \
./src/sentinel.d \
./src/setproctitle.d \
./src/sha1.d \
./src/slowlog.d \
./src/sort.d \
./src/syncio.d \
./src/t_hash.d \
./src/t_list.d \
./src/t_set.d \
./src/t_string.d \
./src/t_zset.d \
./src/util.d \
./src/ziplist.d \
./src/zipmap.d \
./src/zmalloc.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


