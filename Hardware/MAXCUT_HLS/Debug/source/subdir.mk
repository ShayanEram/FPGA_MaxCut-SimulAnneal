################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/shera/Documents/MaxCut-Inf8503/Hardware/MaxCutHLS.cpp 

OBJS += \
./source/MaxCutHLS.o 

CPP_DEPS += \
./source/MaxCutHLS.d 


# Each subdirectory must supply rules for building sources it contributes
source/MaxCutHLS.o: C:/Users/shera/Documents/MaxCut-Inf8503/Hardware/MaxCutHLS.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -IC:/Logiciels/Xilinx/Vivado/2018.3/include/ap_sysc -IC:/Logiciels/Xilinx/Vivado/2018.3/include/etc -IC:/Logiciels/Xilinx/Vivado/2018.3/win64/tools/auto_cc/include -IC:/Logiciels/Xilinx/Vivado/2018.3/win64/tools/systemc/include -IC:/Users/shera/Documents/MaxCut-Inf8503/Hardware -IC:/Logiciels/Xilinx/Vivado/2018.3/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


