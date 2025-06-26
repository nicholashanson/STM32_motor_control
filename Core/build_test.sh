#!/bin/bash
set -e

# Paths for the project directories
CORE_INC="../Core/Inc"
HAL_DRIVER_INC="../Drivers/STM32F4xx_HAL_Driver/Inc"
HAL_DRIVER_SRC="../Drivers/STM32F4xx_HAL_Driver/Src"
CMSIS_DEVICE_INC="../Drivers/CMSIS/Device/ST/STM32F4xx/Include"
CMSIS_INC="../Drivers/CMSIS/Include"

# Startup file and linker script
STARTUP_FILE="Startup/startup_stm32f407vgtx.s"
LINKER_SCRIPT="../STM32F407VGTX_FLASH.ld"

# Output
BUILD_DIR="build"
OUTPUT_ELF="$BUILD_DIR/firmware_test.elf"
SPEC_FLAGS="-specs=nosys.specs -u _printf_float"  # disable semihosting

# Compiler flags
CFLAGS="-g -O0 -mcpu=cortex-m4 -mthumb"
INCLUDES="-I$CORE_INC -I$HAL_DRIVER_INC -I$CMSIS_DEVICE_INC -I$CMSIS_INC"

# Ensure build directory exists
mkdir -p "$BUILD_DIR"

echo "1) Compiling HAL driver sources..."
HAL_OBJECT_FILES=
for file in "$HAL_DRIVER_SRC"/*.c; do
    obj="$BUILD_DIR/$(basename "${file%.c}.o")"
    arm-none-eabi-gcc $CFLAGS $INCLUDES -DSTM32F407xx \
      -c "$file" -o "$obj"
    HAL_OBJECT_FILES+=" $obj"
done

echo "2) Compiling system, IRQ handlers, MSP init..."
# CMSIS system file
arm-none-eabi-gcc $CFLAGS $INCLUDES -DSTM32F407xx \
  -c Src/system_stm32f4xx.c -o "$BUILD_DIR/system.o"
# IRQ handlers
arm-none-eabi-gcc $CFLAGS $INCLUDES -DSTM32F407xx \
  -c Src/stm32f4xx_it.c -o "$BUILD_DIR/it.o"
# HAL MSP init
arm-none-eabi-gcc $CFLAGS $INCLUDES -DSTM32F407xx \
  -c Src/stm32f4xx_hal_msp.c -o "$BUILD_DIR/msp.o"

echo "3) Compiling application sources..."
arm-none-eabi-gcc $CFLAGS $INCLUDES -DSTM32F407xx \
  -c ../Test/test_main.c -o "$BUILD_DIR/test_main.o"

echo "4) Compiling syscall and sysmem support..."
arm-none-eabi-gcc $CFLAGS $INCLUDES -DSTM32F407xx \
  -c Src/syscalls.c -o "$BUILD_DIR/syscalls.o"
arm-none-eabi-gcc $CFLAGS $INCLUDES -DSTM32F407xx \
  -c Src/sysmem.c -o "$BUILD_DIR/sysmem.o"

echo "5) Compiling unity..."
arm-none-eabi-gcc $CFLAGS $INCLUDES -DSTM32F407xx \
  -c ../Unity/unity.c -o "$BUILD_DIR/unity.o"

echo "6) Linking all objects into ELF..."
arm-none-eabi-gcc $CFLAGS $SPEC_FLAGS \
  "$STARTUP_FILE" \
  "$BUILD_DIR/system.o" \
  "$BUILD_DIR/it.o" \
  "$BUILD_DIR/msp.o" \
  "$BUILD_DIR/test_main.o" \
  "$BUILD_DIR/syscalls.o" \
  "$BUILD_DIR/sysmem.o" \
   "$BUILD_DIR/unity.o" \
  $HAL_OBJECT_FILES \
  -T"$LINKER_SCRIPT" \
  -Wl,--no-gc-sections \
  -o "$OUTPUT_ELF"

echo "Build complete: $OUTPUT_ELF"