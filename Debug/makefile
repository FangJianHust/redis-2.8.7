################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include deps/lua/src/subdir.mk
-include deps/lua/etc/subdir.mk
-include deps/linenoise/subdir.mk
-include deps/jemalloc/test/subdir.mk
-include deps/jemalloc/src/subdir.mk
-include deps/hiredis/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: redis-2.8.7

# Tool invocations
redis-2.8.7: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o "redis-2.8.7" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) redis-2.8.7
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
