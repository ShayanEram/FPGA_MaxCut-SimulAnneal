################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/shera/Documents/MaxCut-Inf8503/Hardware/MaxCutHLS_Test.cpp 

OBJS += \
./testbench/MaxCutHLS_Test.o 

CPP_DEPS += \
./testbench/MaxCutHLS_Test.d 


# Each subdirectory must supply rules for building sources it contributes
testbench/MaxCutHLS_Test.o: C:/Users/shera/Documents/MaxCut-Inf8503/Hardware/MaxCutHLS_Test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -IC:/Logiciels/Xilinx/Vivado/2018.3/include/ap_sysc -IC:/Logiciels/Xilinx/Vivado/2018.3/include/etc -IC:/Logiciels/Xilinx/Vivado/2018.3/win64/tools/auto_cc/include -IC:/Logiciels/Xilinx/Vivado/2018.3/win64/tools/systemc/include -IC:/Users/shera/Documents/MaxCut-Inf8503/Hardware -IC:/Logiciels/Xilinx/Vivado/2018.3/include -O0 -g3 -Wall -Wno-unknown-pragmas -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"testbench/MaxCutHLS_Test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


