################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../PololuDCDriver.ino 

CPP_SRCS += \
../.ino.cpp \
../MotorData.cpp \
../MotorModel.cpp 

LINK_OBJ += \
./.ino.cpp.o \
./MotorData.cpp.o \
./MotorModel.cpp.o 

INO_DEPS += \
./PololuDCDriver.ino.d 

CPP_DEPS += \
./.ino.cpp.d \
./MotorData.cpp.d \
./MotorModel.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/krzysztof/Downloads/sloeber/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/krzysztof/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.15/cores/arduino" -I"/home/krzysztof/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.15/variants/mega" -I"/home/krzysztof/Arduino/libraries/ArduinoJson" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '

MotorData.cpp.o: ../MotorData.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/krzysztof/Downloads/sloeber/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/krzysztof/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.15/cores/arduino" -I"/home/krzysztof/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.15/variants/mega" -I"/home/krzysztof/Arduino/libraries/ArduinoJson" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '

MotorModel.cpp.o: ../MotorModel.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/krzysztof/Downloads/sloeber/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/krzysztof/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.15/cores/arduino" -I"/home/krzysztof/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.15/variants/mega" -I"/home/krzysztof/Arduino/libraries/ArduinoJson" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '

PololuDCDriver.o: ../PololuDCDriver.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/krzysztof/Downloads/sloeber/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/krzysztof/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.15/cores/arduino" -I"/home/krzysztof/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.15/variants/mega" -I"/home/krzysztof/Arduino/libraries/ArduinoJson" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


