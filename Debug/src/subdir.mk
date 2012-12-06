################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MarketDataGenerator.cpp \
../src/generatorTemplate.cpp \
../src/symbol.cpp 

OBJS += \
./src/MarketDataGenerator.o \
./src/generatorTemplate.o \
./src/symbol.o 

CPP_DEPS += \
./src/MarketDataGenerator.d \
./src/generatorTemplate.d \
./src/symbol.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


