################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MapLoader/MapInit.cpp \
../MapLoader/MapLoader.cpp \
../MapLoader/lodepng.cpp 

OBJS += \
./MapLoader/MapInit.o \
./MapLoader/MapLoader.o \
./MapLoader/lodepng.o 

CPP_DEPS += \
./MapLoader/MapInit.d \
./MapLoader/MapLoader.d \
./MapLoader/lodepng.d 


# Each subdirectory must supply rules for building sources it contributes
MapLoader/%.o: ../MapLoader/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

MapLoader/MapLoader.o: /home/colman/git/RoboticsFInalOne/RobotProject/MapLoader/MapLoader.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


