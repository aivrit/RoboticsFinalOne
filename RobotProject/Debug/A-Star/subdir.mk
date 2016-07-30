################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../A-Star/AStar.cpp \
../A-Star/Point.cpp \
../A-Star/Position.cpp 

OBJS += \
./A-Star/AStar.o \
./A-Star/Point.o \
./A-Star/Position.o 

CPP_DEPS += \
./A-Star/AStar.d \
./A-Star/Point.d \
./A-Star/Position.d 


# Each subdirectory must supply rules for building sources it contributes
A-Star/%.o: ../A-Star/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


