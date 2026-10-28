# Keysatron Firmware

Firmware for the **Keysatron** inline USB-to-USB hardware adapter. Keysatron intercepts input from any standard USB keyboard plugged into `USB_IN` (J2) and translates keystrokes in real-time before sending them to your computer via `USB_PC` (J3).

This firmware implements the **FAMAK** multi-layer keyboard layout with full support for both **Linux (`keyd` configuration)** and **Windows (`AutoHotkey` configuration)** host environments.

---

## Dual Host Profiles (Linux & Windows)

Keysatron supports two built-in profiles that can be switched on the fly:

1. **Linux Profile (`keyd`) [Default]**:
   - Matches the Linux `keyd` daemon configuration.
   - Emits correct scancodes for Linux (`102nd = y`, `p = z`).
   - Uses `Meta` (Super) shortcuts for Nav navigation (`Super + 1`..`Super + 9`, `Super + Alt + 0`..`2`).
   - Uses terminal shortcuts in Exo layer (`Ctrl + Shift + C` for copy, `Ctrl + Shift + V` for paste, `Ctrl + Super + Esc` for kill).
2. **Windows Profile (`AutoHotkey`)**:
   - Matches the Windows AutoHotkey layout specification.
   - Uses `Alt` shortcuts for Nav navigation (`Alt + 1`..`Alt + 9`).

### Hotkeys:
* `Win + Enter`: **Cycle Profile** (Linux &harr; Windows).
* `Win + Escape`: **Stop Keymap** (transparent raw passthrough).
* `Win + Backspace`: **Start Keymap** (FAMAK active).

### Status LED Indications (`PA0` / `D3`):
* **On Every Keypress**: Toggles live with each received keystroke for immediate physical confirmation.
* **1 Blink**: Switched to **Linux (`keyd`) Profile**.
* **2 Blinks**: Switched to **Windows (`AutoHotkey`) Profile**.
* **2 Fast Blinks**: Keymap **Active**.
* **1 Long Pulse**: Keymap **Stopped** (Passthrough).
* **Heartbeat**: 1000 ms when operational; 250 ms fast flash when waiting for a keyboard to be plugged in.

---

## The FAMAK Layout (4 Layers)

```
Normal (Base)  <--  [#] key  -->  Sym Layer
               <-- [AltGr]  -->  Nav Layer
               <--  [Tab]   -->  Exo Layer
```

### 1. Normal Layer (Base)
* **Alpha rows (FAMAK):**
  * Row 2: `q  w  c  p  b  [VolDown]  j  l  u  z  [BS]`
  * Row 3: `a  r  s  t  g  [C-A-h]    m  n  e  i  o`
  * Row 4: `y  ;  f  d  v  x  [LWin]  k  h  [  '`
* **Number row shortcuts:**
  * `1` &rarr; `Alt + Left` (Browser Back)
  * `2` &rarr; `Alt + Right` (Browser Forward)
  * `3` &rarr; `Ctrl + y` (Linux: `C-y` / Windows: `^y`)
  * `4` &rarr; `Ctrl + z` (Linux: `C-z` / Windows: `^z`)
  * `5`..`9` &rarr; `F5`..`F9`
  * `0` &rarr; `Page Down`
  * `ß` &rarr; `Page Up`
  * `´` &rarr; `Alt + Shift + b`
* **Modifiers & Helpers:**
  * `CapsLock` &rarr; Remapped to **Left Control**
  * `+` key &rarr; **Shift Layer** (capitalizes letters; pressing `Space` while holding `+` sends `?`)
  * `Ü` &rarr; `Backspace`
  * `#` key &rarr; Hold for **Sym Layer**
  * `Tab` key &rarr; Hold for **Exo Layer**
  * `AltGr` &rarr; Hold for **Nav Layer**

---

### 2. Sym Layer (Hold `#`)
Instant access to symbols and program shortcuts:
* `1`..`0`, `ß`, `´` &rarr; `Ctrl + 1` through `Ctrl + 12`
* `Q` &rarr; `~` (Tilde, `AltGr + +`)
* `W` &rarr; `!` (Exclamation mark, `Shift + 1`)
* `E` &rarr; `/` (Slash, `Shift + 7`)
* `R` &rarr; `|` (Pipe, `AltGr + <`)
* `T` &rarr; `&` (Ampersand, `Shift + 6`)
* `A` &rarr; `/`
* `S` &rarr; `]` (AltGr + 9)
* `D` &rarr; `*` (Shift + +)
* `F` &rarr; `.`
* `G` &rarr; `,`
* `H` &rarr; `\` (AltGr + ß)
* `J` &rarr; `=` (Shift + 0)
* `K` &rarr; `\`
* `L` &rarr; `` ` `` (Backtick, Shift + ´)
* `<` &rarr; `<`
* `Y` &rarr; `\`
* `X` &rarr; `>` (Shift + <)
* `C` &rarr; `=`
* `V` &rarr; `;`
* `B` &rarr; `_`
* `,` &rarr; `%` (Shift + 5)
* `Space` &rarr; `>`
* `AltGr` in Sym &rarr; Transitions to **Exo Layer**

---

### 3. Nav Layer (Hold `AltGr`)
Full navigation and editing cluster:
* `1`..`9` &rarr; Linux: `Super + 1`..`9` / Windows: `Alt + 1`..`9`
* `0`, `-`, `=` &rarr; Linux: `Super + Alt + 0`..`2` / Windows: `Alt + 0`..`2`
* `Backspace` &rarr; `Alt + F4` (Close window)
* `Q` &rarr; `Ctrl + Alt + w`
* `W`, `E`, `R`, `D` &rarr; `Left`, `Up`, `Right`, `Down` (Inverted-T arrow cluster)
* `T` &rarr; `Ctrl + Alt + t` (Terminal launcher)
* `Y` &rarr; `Mute`
* `U` &rarr; `Brightness Down` (`F14`)
* `I` &rarr; `Brightness Up` (`F15`)
* `O` &rarr; `[`
* `P` &rarr; `]`
* `Ü` &rarr; `Escape`
* `A` &rarr; `Home`
* `S` &rarr; `Ctrl + Left` (Word back)
* `F` &rarr; `Ctrl + Right` (Word forward)
* `G` &rarr; `End`
* `K` &rarr; `(` (Shift + 8)
* `L` &rarr; `)` (Shift + 9)
* `Ö` &rarr; `Ctrl + l`
* `Ä` &rarr; `Delete`
* `<` &rarr; `$` (Shift + 4)
* `Y` &rarr; `Insert`
* `X` &rarr; `?` (Shift + ß)
* `C` &rarr; `Alt + PageDown`
* `V` &rarr; `Alt + PageUp`
* `B` &rarr; `"` (Shift + 2)
* `M` &rarr; `{` (AltGr + 7)
* `,` &rarr; `}` (AltGr + 0)
* `Space` &rarr; `Tab`
* `#` in Nav &rarr; Transitions to **Exo Layer**

---

### 4. Exo Layer (Hold `Tab`)
System control, function keys, and numpad:
* `1`..`2` &rarr; `Shift + Ctrl + 1`..`2`
* `3` &rarr; `Shift + Ctrl + C` (Terminal Copy)
* `4` &rarr; `Shift + Ctrl + V` (Terminal Paste)
* `5`..`9` &rarr; `F2`, `F3`, `F4`, `F10`, `F11`
* `0` &rarr; `PageDown` / Scroll Down
* `-` &rarr; `PageUp` / Scroll Up
* `=` &rarr; `Shift + F10`
* `Backspace` &rarr; Linux: `Ctrl + Super + Esc` / Windows: `Ctrl + Alt + Esc`
* `Q` &rarr; Linux: `Ctrl + Super + Left` / Windows: `Ctrl + Alt + Left`
* `W` &rarr; Linux: `Ctrl + Super + Right` / Windows: `Ctrl + Alt + Right`
* `E` &rarr; `Ctrl + Alt + Up`
* `R` &rarr; `Ctrl + PageUp` (Prev tab)
* `T` &rarr; `Ctrl + PageDown` (Next tab)
* `Y` &rarr; `Volume Up`
* `U` &rarr; `@` (AltGr + q)
* `I`, `O`, `P` &rarr; `7`, `8`, `9` (Numpad top row)
* `K`, `L`, `Ö`, `Ä` &rarr; `4`, `5`, `6`, `0` (Numpad middle row)
* `M`, `,`, `.`, `-` &rarr; `1`, `2`, `3`, `-` (Numpad bottom row)
* `J` &rarr; `.`
* `A` &rarr; `Ctrl + Alt + Home`
* `S` &rarr; `Alt + Home`
* `D` &rarr; `Ctrl + Alt + Down`
* `F` &rarr; `Alt + End`
* `G` &rarr; `Ctrl + Alt + End`
* `<` &rarr; `Sleep` (`Power` key)
* `C` &rarr; `Ctrl + Alt + PageDown`
* `V` &rarr; `Ctrl + Alt + PageUp`
* `B` &rarr; `Delete`
* `Space` &rarr; Linux: `Super + Alt + w` / Windows: `Alt + w`

---

## Customizing Key Mappings

All key mappings are defined in clean C lookup tables:
* [`src/famak_config.h`](src/famak_config.h): Structs, layer enums, and profile declarations.
* [`src/famak_config.c`](src/famak_config.c): Table definitions for each profile and layer.

To change any key, simply edit the entry for that key in [`src/famak_config.c`](src/famak_config.c), then build and flash:

```bash
./docker-run.sh build
./docker-run.sh flash
```

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

## Building and Flashing via Docker

All tools run inside a container (`keysatron-dev`). No packages are installed on your host system:

```bash
# Build firmware
./docker-run.sh build

# Flash firmware via ST-LINK
./docker-run.sh flash

# Clean build artifacts
./docker-run.sh clean
```
