TARGET = keysatron-firmware

# Build directory
BUILD_DIR = build

# Toolchain
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc -x assembler-with-cpp
CP = arm-none-eabi-objcopy
SZ = arm-none-eabi-size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# MCU flags
MCU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# C defines
C_DEFS = \
	-DSTM32F405xx \
	-DCFG_TUSB_MCU=OPT_MCU_STM32F4 \
	-DHSE_VALUE=16000000

# Include directories
C_INCLUDES = \
	-Isrc \
	-Ilib/cmsis \
	-Ilib/stm32f4 \
	-Ilib/tinyusb/src \
	-Ilib/tinyusb/src/common \
	-Ilib/tinyusb/src/device \
	-Ilib/tinyusb/src/host \
	-Ilib/tinyusb/src/class/hid \
	-Ilib/tinyusb/src/portable/synopsys/dwc2

# C sources
C_SOURCES = \
	src/main.c \
	src/board_keysatron.c \
	src/layout_engine.c \
	src/usb_descriptors.c \
	src/system_stm32f4xx.c \
	lib/tinyusb/src/tusb.c \
	lib/tinyusb/src/common/tusb_fifo.c \
	lib/tinyusb/src/device/usbd.c \
	lib/tinyusb/src/class/hid/hid_device.c \
	lib/tinyusb/src/host/usbh.c \
	lib/tinyusb/src/host/hub.c \
	lib/tinyusb/src/class/hid/hid_host.c \
	lib/tinyusb/src/portable/synopsys/dwc2/dcd_dwc2.c \
	lib/tinyusb/src/portable/synopsys/dwc2/hcd_dwc2.c \
	lib/tinyusb/src/portable/synopsys/dwc2/dwc2_common.c

# ASM sources
ASM_SOURCES = \
	src/startup_stm32f405xx.s

# Linker script
LDSCRIPT = linker/STM32F405RGTx_FLASH.ld

# Compiler flags
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) -O2 -Wall -fdata-sections -ffunction-sections

# Linker flags
LDFLAGS = $(MCU) -T$(LDSCRIPT) -specs=nano.specs -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# Default target
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

# Object files
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "CC $<"
	@$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	@echo "AS $<"
	@$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) | $(BUILD_DIR)
	@echo "LD $@"
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@$(BIN) $< $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

flash: all
	openocd -f openocd.cfg -c "program $(BUILD_DIR)/$(TARGET).bin reset exit 0x08000000"

flash-probe-rs: all
	probe-rs download --chip STM32F405RG $(BUILD_DIR)/$(TARGET).bin --binary-format bin --base-address 0x08000000 --reset-after-flashing

.PHONY: all clean flash flash-probe-rs
