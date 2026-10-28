cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE arm-none-eabi-size)

project(keysatron-firmware C ASM)

set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CMAKE_C_FLAGS "${MCU_FLAGS} -O2 -Wall -fdata-sections -ffunction-sections")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp")

set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -T${CMAKE_CURRENT_SOURCE_DIR}/linker/STM32F405RGTx_FLASH.ld -specs=nano.specs -Wl,-Map=${PROJECT_NAME}.map,--cref -Wl,--gc-sections")

add_definitions(
    -DSTM32F405xx
    -DCFG_TUSB_MCU=OPT_MCU_STM32F4
    -DHSE_VALUE=16000000
)

include_directories(
    src
    lib/cmsis
    lib/stm32f4
    lib/tinyusb/src
    lib/tinyusb/src/common
    lib/tinyusb/src/device
    lib/tinyusb/src/host
    lib/tinyusb/src/class/hid
    lib/tinyusb/src/portable/synopsys/dwc2
)

set(SOURCES
    src/main.c
    src/board_keysatron.c
    src/layout_engine.c
    src/usb_descriptors.c
    src/system_stm32f4xx.c
    src/startup_stm32f405xx.s
    lib/tinyusb/src/tusb.c
    lib/tinyusb/src/common/tusb_fifo.c
    lib/tinyusb/src/device/usbd.c
    lib/tinyusb/src/class/hid/hid_device.c
    lib/tinyusb/src/host/usbh.c
    lib/tinyusb/src/host/hub.c
    lib/tinyusb/src/class/hid/hid_host.c
    lib/tinyusb/src/portable/synopsys/dwc2/dcd_dwc2.c
    lib/tinyusb/src/portable/synopsys/dwc2/hcd_dwc2.c
    lib/tinyusb/src/portable/synopsys/dwc2/dwc2_common.c
)

add_executable(${PROJECT_NAME}.elf ${SOURCES})

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
    COMMENT "Building ${PROJECT_NAME}.bin, ${PROJECT_NAME}.hex and showing size"
)
