################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../deps/lua/src/lapi.o \
../deps/lua/src/lauxlib.o \
../deps/lua/src/lbaselib.o \
../deps/lua/src/lcode.o \
../deps/lua/src/ldblib.o \
../deps/lua/src/ldebug.o \
../deps/lua/src/ldo.o \
../deps/lua/src/ldump.o \
../deps/lua/src/lfunc.o \
../deps/lua/src/lgc.o \
../deps/lua/src/linit.o \
../deps/lua/src/liolib.o \
../deps/lua/src/llex.o \
../deps/lua/src/lmathlib.o \
../deps/lua/src/lmem.o \
../deps/lua/src/loadlib.o \
../deps/lua/src/lobject.o \
../deps/lua/src/lopcodes.o \
../deps/lua/src/loslib.o \
../deps/lua/src/lparser.o \
../deps/lua/src/lstate.o \
../deps/lua/src/lstring.o \
../deps/lua/src/lstrlib.o \
../deps/lua/src/ltable.o \
../deps/lua/src/ltablib.o \
../deps/lua/src/ltm.o \
../deps/lua/src/lua.o \
../deps/lua/src/lua_cjson.o \
../deps/lua/src/lua_cmsgpack.o \
../deps/lua/src/lua_struct.o \
../deps/lua/src/luac.o \
../deps/lua/src/lundump.o \
../deps/lua/src/lvm.o \
../deps/lua/src/lzio.o \
../deps/lua/src/print.o \
../deps/lua/src/strbuf.o 

C_SRCS += \
../deps/lua/src/lapi.c \
../deps/lua/src/lauxlib.c \
../deps/lua/src/lbaselib.c \
../deps/lua/src/lcode.c \
../deps/lua/src/ldblib.c \
../deps/lua/src/ldebug.c \
../deps/lua/src/ldo.c \
../deps/lua/src/ldump.c \
../deps/lua/src/lfunc.c \
../deps/lua/src/lgc.c \
../deps/lua/src/linit.c \
../deps/lua/src/liolib.c \
../deps/lua/src/llex.c \
../deps/lua/src/lmathlib.c \
../deps/lua/src/lmem.c \
../deps/lua/src/loadlib.c \
../deps/lua/src/lobject.c \
../deps/lua/src/lopcodes.c \
../deps/lua/src/loslib.c \
../deps/lua/src/lparser.c \
../deps/lua/src/lstate.c \
../deps/lua/src/lstring.c \
../deps/lua/src/lstrlib.c \
../deps/lua/src/ltable.c \
../deps/lua/src/ltablib.c \
../deps/lua/src/ltm.c \
../deps/lua/src/lua.c \
../deps/lua/src/lua_cjson.c \
../deps/lua/src/lua_cmsgpack.c \
../deps/lua/src/lua_struct.c \
../deps/lua/src/luac.c \
../deps/lua/src/lundump.c \
../deps/lua/src/lvm.c \
../deps/lua/src/lzio.c \
../deps/lua/src/print.c \
../deps/lua/src/strbuf.c 

OBJS += \
./deps/lua/src/lapi.o \
./deps/lua/src/lauxlib.o \
./deps/lua/src/lbaselib.o \
./deps/lua/src/lcode.o \
./deps/lua/src/ldblib.o \
./deps/lua/src/ldebug.o \
./deps/lua/src/ldo.o \
./deps/lua/src/ldump.o \
./deps/lua/src/lfunc.o \
./deps/lua/src/lgc.o \
./deps/lua/src/linit.o \
./deps/lua/src/liolib.o \
./deps/lua/src/llex.o \
./deps/lua/src/lmathlib.o \
./deps/lua/src/lmem.o \
./deps/lua/src/loadlib.o \
./deps/lua/src/lobject.o \
./deps/lua/src/lopcodes.o \
./deps/lua/src/loslib.o \
./deps/lua/src/lparser.o \
./deps/lua/src/lstate.o \
./deps/lua/src/lstring.o \
./deps/lua/src/lstrlib.o \
./deps/lua/src/ltable.o \
./deps/lua/src/ltablib.o \
./deps/lua/src/ltm.o \
./deps/lua/src/lua.o \
./deps/lua/src/lua_cjson.o \
./deps/lua/src/lua_cmsgpack.o \
./deps/lua/src/lua_struct.o \
./deps/lua/src/luac.o \
./deps/lua/src/lundump.o \
./deps/lua/src/lvm.o \
./deps/lua/src/lzio.o \
./deps/lua/src/print.o \
./deps/lua/src/strbuf.o 

C_DEPS += \
./deps/lua/src/lapi.d \
./deps/lua/src/lauxlib.d \
./deps/lua/src/lbaselib.d \
./deps/lua/src/lcode.d \
./deps/lua/src/ldblib.d \
./deps/lua/src/ldebug.d \
./deps/lua/src/ldo.d \
./deps/lua/src/ldump.d \
./deps/lua/src/lfunc.d \
./deps/lua/src/lgc.d \
./deps/lua/src/linit.d \
./deps/lua/src/liolib.d \
./deps/lua/src/llex.d \
./deps/lua/src/lmathlib.d \
./deps/lua/src/lmem.d \
./deps/lua/src/loadlib.d \
./deps/lua/src/lobject.d \
./deps/lua/src/lopcodes.d \
./deps/lua/src/loslib.d \
./deps/lua/src/lparser.d \
./deps/lua/src/lstate.d \
./deps/lua/src/lstring.d \
./deps/lua/src/lstrlib.d \
./deps/lua/src/ltable.d \
./deps/lua/src/ltablib.d \
./deps/lua/src/ltm.d \
./deps/lua/src/lua.d \
./deps/lua/src/lua_cjson.d \
./deps/lua/src/lua_cmsgpack.d \
./deps/lua/src/lua_struct.d \
./deps/lua/src/luac.d \
./deps/lua/src/lundump.d \
./deps/lua/src/lvm.d \
./deps/lua/src/lzio.d \
./deps/lua/src/print.d \
./deps/lua/src/strbuf.d 


# Each subdirectory must supply rules for building sources it contributes
deps/lua/src/%.o: ../deps/lua/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


