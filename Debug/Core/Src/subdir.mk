################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/clock_setup.c \
../Core/Src/led_blink.c \
../Core/Src/uart.c 

OBJS += \
./Core/Src/clock_setup.o \
./Core/Src/led_blink.o \
./Core/Src/uart.o 

COMPILED_SRCS += \
./Core/Src/clock_setup.src \
./Core/Src/led_blink.src \
./Core/Src/uart.src 

C_DEPS += \
./Core/Src/clock_setup.d \
./Core/Src/led_blink.d \
./Core/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.src: ../Core/Src/%.c Core/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/volod/AURIX-v1.8.0-workspace/blink_multicore/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Core/Src/%.o: ./Core/Src/%.src Core/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


