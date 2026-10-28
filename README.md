# Keysatron Firmware

Firmware for the **Keysatron** USB-to-USB hardware adapter. Keysatron intercepts input from any standard USB keyboard plugged into `USB_IN` (J2) and translates keystrokes in real-time before sending them to your computer via `USB_PC` (J3).

This firmware implements hardware translation from **German ISO (QWERTZ)** to **Colemak ISO** layout.

---

## Features

- **Dual USB Stacks**:
  - **USB Host (OTG_FS, PA11/PA12, `USB_IN`)**: Enumerates connected USB keyboards, reads standard 6KRO boot and report protocol packets.
  - **USB Device (OTG_HS in FS PHY mode, PB14/PB15, `USB_PC`)**: Emulates a USB HID keyboard connected to the PC host.
- **Bi-Directional LED Sync**: Host PC CapsLock and NumLock status changes are forwarded directly to the physical keyboard.
- **Multi-Mode Layout Engine**:
  - **Mode 1: Colemak for German Host OS (Colemak-DE)** *(Default)*: Designed for host computers configured with German layout. Keystrokes are translated so that the German OS generates the correct Colemak characters.
  - **Mode 2: Standard Colemak for US Host OS**: Designed for host computers configured with standard US layout. Keystrokes are translated directly into Colemak scancodes.
  - **Mode 3: Transparent Passthrough**: Raw German ISO QWERTZ passthrough without any remapping.
- **On-the-Fly Hotkey Switching**:
  - Press `Ctrl + Alt + C` anytime to cycle between layout modes.
  - The onboard green LED (`D3`) blinks 1, 2, or 3 times to confirm the active mode.
- **Status LED Feedback (`D3`, PA0)**:
  - Slow heartbeat (1 Hz) when a keyboard is mounted and operational.
  - Fast flash (4 Hz) while waiting for a keyboard to be connected.
  - Distinct pulse count on mode switch.

---

## Hardware Pinout & Architecture

| Peripheral | STM32F405 Pin | Function |
| :--- | :--- | :--- |
| **USB_IN (Host)** | `PA11` (DM), `PA12` (DP) | USB OTG FS connected to keyboard |
| **USB_PC (Device)** | `PB14` (DM), `PB15` (DP) | USB OTG HS with embedded FS PHY to computer |
| **Status LED** | `PA0` (active high) | Green LED `D3` |
| **Crystal (HSE)** | `PH0` (IN), `PH1` (OUT) | 16 MHz external crystal |
| **SWD Debug Header** | `PA13` (SWDIO), `PA14` (SWCLK) | Header `J1` |

---

## Building

### Requirements
- ARM GNU Toolchain (`arm-none-eabi-gcc`, `arm-none-eabi-binutils`)
- `make` or `cmake`

### Build with Make
```bash
make
```

Outputs will be generated in `build/`:
- `build/keysatron-firmware.elf`
- `build/keysatron-firmware.bin`
- `build/keysatron-firmware.hex`

---

## Flashing with ST-Link

### Quick Flash
```bash
# Using OpenOCD (recommended):
make flash

# Or using probe-rs:
make flash-probe-rs

# Or run the automatic flashing script:
./flash.sh
```

---

## ST-Link & Nucleo Connection Guide

The SWD header `J1` on Keysatron has the following pinout:

```
[ Pin 1: GND ] [ Pin 2: NRST ] [ Pin 3: CLK ] [ Pin 4: IO ] [ Pin 5: 3.3V ]
```

When using an ST-LINK/V2-1 from an STM32 Nucleo board (header `CN4`):

> [!IMPORTANT]
> 1. **Remove both jumpers on `CN2` (marked "STLK")** on the Nucleo board. If left attached, the ST-Link remains connected to the Nucleo's own microcontroller and cannot communicate with Keysatron.
> 2. **Power the board**: Pin 1 (`VDD_TARGET`) on Nucleo `CN4` is only a voltage sensor. Make sure Keysatron is powered via a 5V USB cable or connect `3V3` from the Nucleo power header (`CN6` Pin 4) to Keysatron `J1` Pin 5.

### Wiring Table

| Nucleo CN4 Pin | Signal | Wire to Keysatron `J1` Pin | Label |
| :---: | :---: | :---: | :---: |
| Pin 1 | `VDD_TARGET` | **Pin 5** | `3.3V` |
| Pin 2 | `SWCLK` | **Pin 3** | `CLK` |
| Pin 3 | `GND` | **Pin 1** | `GND` |
| Pin 4 | `SWDIO` | **Pin 4** | `IO` |
| Pin 5 | `NRST` | **Pin 2** | `NRST` |

---

## Related Projects

- Hardware KiCad PCB project: [keysatron](https://github.com/fablackner/keysatron)
