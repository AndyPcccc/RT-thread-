################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../applications/fmq.c \
../applications/hcsr04.c \
../applications/main.c \
../applications/movement.c \
../applications/pwm.c \
../applications/sensor.c \
../applications/serial_comm_openmv.c \
../applications/serial_comm_screen.c \
../applications/serial_comm_voice.c \
../applications/stepping.c \
../applications/syscall.c 

OBJS += \
./applications/fmq.o \
./applications/hcsr04.o \
./applications/main.o \
./applications/movement.o \
./applications/pwm.o \
./applications/sensor.o \
./applications/serial_comm_openmv.o \
./applications/serial_comm_screen.o \
./applications/serial_comm_voice.o \
./applications/stepping.o \
./applications/syscall.o 

C_DEPS += \
./applications/fmq.d \
./applications/hcsr04.d \
./applications/main.d \
./applications/movement.d \
./applications/pwm.d \
./applications/sensor.d \
./applications/serial_comm_openmv.d \
./applications/serial_comm_screen.d \
./applications/serial_comm_voice.d \
./applications/stepping.d \
./applications/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
applications/%.o: ../applications/%.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DSOC_FAMILY_STM32 -DSOC_SERIES_STM32F4 -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:\RT-ThreadStudio\workspace\warehouse_car\drivers" -I"D:\RT-ThreadStudio\workspace\warehouse_car\drivers\include" -I"D:\RT-ThreadStudio\workspace\warehouse_car\drivers\include\config" -I"D:\RT-ThreadStudio\workspace\warehouse_car\libraries\CMSIS\Device\ST\STM32F4xx\Include" -I"D:\RT-ThreadStudio\workspace\warehouse_car\libraries\CMSIS\Include" -I"D:\RT-ThreadStudio\workspace\warehouse_car\libraries\CMSIS\RTOS\Template" -I"D:\RT-ThreadStudio\workspace\warehouse_car\libraries\STM32F4xx_HAL_Driver\Inc" -I"D:\RT-ThreadStudio\workspace\warehouse_car\libraries\STM32F4xx_HAL_Driver\Inc\Legacy" -I"D:\RT-ThreadStudio\workspace\warehouse_car" -I"D:\RT-ThreadStudio\workspace\warehouse_car\applications" -I"D:\RT-ThreadStudio\workspace\warehouse_car" -I"D:\RT-ThreadStudio\workspace\warehouse_car\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\warehouse_car\rt-thread\components\finsh" -I"D:\RT-ThreadStudio\workspace\warehouse_car\rt-thread\components\libc\compilers\common" -I"D:\RT-ThreadStudio\workspace\warehouse_car\rt-thread\components\utilities\ulog" -I"D:\RT-ThreadStudio\workspace\warehouse_car\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\warehouse_car\rt-thread\libcpu\arm\common" -I"D:\RT-ThreadStudio\workspace\warehouse_car\rt-thread\libcpu\arm\cortex-m4" -include"D:\RT-ThreadStudio\workspace\warehouse_car\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

