################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AStar.cpp \
../ConfigurationManger.cpp \
../LocalizationManager.cpp \
../Location.cpp \
../Manager.cpp \
../Particle.cpp \
../Point.cpp \
../Robot.cpp \
../main.cpp 

OBJS += \
./AStar.o \
./ConfigurationManger.o \
./LocalizationManager.o \
./Location.o \
./Manager.o \
./Particle.o \
./Point.o \
./Robot.o \
./main.o 

CPP_DEPS += \
./AStar.d \
./ConfigurationManger.d \
./LocalizationManager.d \
./Location.d \
./Manager.d \
./Particle.d \
./Point.d \
./Robot.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


