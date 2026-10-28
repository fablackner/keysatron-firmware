#!/usr/bin/env bash
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BIN="$DIR/build/keysatron-firmware.bin"
ELF="$DIR/build/keysatron-firmware.elf"

if [ ! -f "$BIN" ]; then
    echo "==> Binary not found. Building firmware first..."
    make -C "$DIR"
fi

echo "=================================================="
echo " Flashing Keysatron Firmware to STM32F405"
echo "=================================================="

# Try OpenOCD first
if command -v openocd >/dev/null 2>&1; then
    echo "==> Using OpenOCD..."
    openocd -f "$DIR/openocd.cfg" -c "program $BIN reset exit 0x08000000" && exit 0
fi

# Try probe-rs
if command -v probe-rs >/dev/null 2>&1; then
    echo "==> Using probe-rs..."
    probe-rs download --chip STM32F405RG "$BIN" --binary-format bin --base-address 0x08000000 --reset-after-flashing && exit 0
fi

# Try st-flash
if command -v st-flash >/dev/null 2>&1; then
    echo "==> Using st-flash..."
    st-flash --reset write "$BIN" 0x08000000 && exit 0
fi

echo "Error: No supported flashing tool found (openocd, probe-rs, or st-flash)."
exit 1
