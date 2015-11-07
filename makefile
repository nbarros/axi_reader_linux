
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
SIZEAPP := $(CROSS_COMPILE)size

RM := rm -rf

EXTRA_INCLUDES :=
EXTRA_LIBS :=
CC_SRCS :=
CC_DEPS :=
OBJS := 
ELFSIZE := 
USER_OBJS :=
USER_LIBS := 

CC_SRCS += \
./src/axi_reader_linux.cc 

CC_DEPS += \
.build/axi_reader_linux.d 

OBJS += \
.build/axi_reader_linux.o 


# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
axi_reader_linux.elf.size \


# All Target
all: builddir axi_reader_linux.elf secondary-outputs

builddir:
	-mkdir -p .build
	
# Tool invocations
axi_reader_linux.elf: $(OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linux g++ linker'
	$(CC) -std=c++11 $(EXTRA_LIBS) -o "axi_reader_linux.elf" $(OBJS) $(USER_OBJS) $(USER_LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

axi_reader_linux.elf.size: axi_reader_linux.elf
	@echo 'Invoking: ARM Linux Print Size'
	$(SIZEAPP) axi_reader_linux.elf  |tee "axi_reader_linux.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(ELFSIZE) axi_reader_linux.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE)


# Each subdirectory must supply rules for building sources it contributes
.build/%.o: ./src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Linux g++ compiler'
	$(CXX) -std=c++11 -Wall -O0 -g3 $(EXTRA_INCLUDES) -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


.PHONY: all clean dependents
.SECONDARY:

