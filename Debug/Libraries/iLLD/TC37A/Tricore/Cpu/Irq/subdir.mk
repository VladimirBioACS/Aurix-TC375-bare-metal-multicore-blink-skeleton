################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC37A/Tricore/Cpu/Irq/IfxCpu_Irq.c 

OBJS += \
./Libraries/iLLD/TC37A/Tricore/Cpu/Irq/IfxCpu_Irq.o 

COMPILED_SRCS += \
./Libraries/iLLD/TC37A/Tricore/Cpu/Irq/IfxCpu_Irq.src 

C_DEPS += \
./Libraries/iLLD/TC37A/Tricore/Cpu/Irq/IfxCpu_Irq.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC37A/Tricore/Cpu/Irq/%.src: ../Libraries/iLLD/TC37A/Tricore/Cpu/Irq/%.c Libraries/iLLD/TC37A/Tricore/Cpu/Irq/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/volod/AURIX-v1.8.0-workspace/blink_multicore/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/iLLD/TC37A/Tricore/Cpu/Irq/%.o: ./Libraries/iLLD/TC37A/Tricore/Cpu/Irq/%.src Libraries/iLLD/TC37A/Tricore/Cpu/Irq/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '

