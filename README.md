# Keysatron Firmware

Firmware for the **Keysatron** inline USB-to-USB hardware adapter. Keysatron intercepts input from any standard USB keyboard plugged into `USB_IN` (J2) and translates keystrokes in real-time before sending them to your computer via `USB_PC` (J3).

This firmware implements the **FAMAK** multi-layer keyboard layout (designed for physical German ISO keyboards connected to computers with German OS layout).

---

## The FAMAK Layout (4 Layers)

Keysatron implements four operational layers matching the AutoHotkey specification:

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
  * `3` &rarr; `Ctrl + y` (Redo)
  * `4` &rarr; `Ctrl + z` (Undo)
  * `5`..`9` &rarr; `F5`..`F9`
  * `0` &rarr; `Page Down`
  * `ß` &rarr; `Page Up`
  * `´` &rarr; `Alt + Shift + b`
* **Modifiers & Helpers:**
  * `CapsLock` &rarr; Remapped to **Left Control**
  * `+` key (`SC01B`) &rarr; **Shift Layer** (capitalizes letters; pressing `Space` while holding `+` sends `?`)
  * `Ü` &rarr; `Backspace`
  * `#` key (`SC02B`) &rarr; Hold for **Sym Layer**
  * `Tab` key (`SC00F`) &rarr; Hold for **Exo Layer**
  * `AltGr` (`SC138`) &rarr; Hold for **Nav Layer**

---

### 2. Sym Layer (Hold `#` / `SC02B`)
Instant access to symbols and program shortcuts:
* `1`..`0`, `ß`, `´` &rarr; `Ctrl + 1` through `Ctrl + 12`
* `Q` &rarr; `~` (Tilde)
* `W` &rarr; `!` (Exclamation mark)
* `E` &rarr; `/` (Slash)
* `R` &rarr; `|` (Pipe)
* `T` &rarr; `&` (Ampersand)
* `A` &rarr; `/`
* `S` &rarr; `]`
* `D` &rarr; `*`
* `F` &rarr; `.`
* `G` &rarr; `,`
* `H` &rarr; `\`
* `J` &rarr; `=`
* `K` &rarr; `\`
* `L` &rarr; `` ` `` (Backtick)
* `<` &rarr; `<`
* `Y` &rarr; `\`
* `X` &rarr; `>`
* `C` &rarr; `=`
* `V` &rarr; `;`
* `B` &rarr; `_`
* `,` &rarr; `%`
* `Space` &rarr; `>`
* `AltGr` in Sym &rarr; Transitions to **Exo Layer**

---

### 3. Nav Layer (Hold `AltGr` / `SC138`)
Full navigation and editing cluster:
* `1`..`0` &rarr; `Alt + 1` through `Alt + 0`
* `Backspace` &rarr; `Alt + F4` (Close window)
* `W` / `A` / `S` / `D` cluster:
  * `W` &rarr; `Left Arrow`
  * `E` &rarr; `Up Arrow`
  * `R` &rarr; `Right Arrow`
  * `D` &rarr; `Down Arrow`
  * `S` &rarr; `Ctrl + Left` (Word left)
  * `F` &rarr; `Ctrl + Right` (Word right)
  * `A` &rarr; `Home`
  * `G` &rarr; `End`
* `Q` &rarr; `Ctrl + Alt + w`
* `T` &rarr; `Ctrl + Alt + t`
* `Z` &rarr; `Mute`
* `U` &rarr; `Brightness Down`
* `I` &rarr; `Brightness Up`
* `O` &rarr; `[`
* `P` &rarr; `]`
* `Ü` &rarr; `Escape`
* `K` &rarr; `(`
* `L` &rarr; `)`
* `Ö` &rarr; `Ctrl + l` (Address bar)
* `Ä` &rarr; `Delete`
* `<` &rarr; `$`
* `Y` &rarr; `Insert`
* `C` &rarr; `Alt + PageDown`
* `V` &rarr; `Alt + PageUp`
* `B` &rarr; `"`
* `M` &rarr; `{`
* `,` &rarr; `}`
* `Space` &rarr; `Tab`
* `#` in Nav &rarr; Transitions to **Exo Layer**

---

### 4. Exo Layer (Hold `Tab` / `SC00F`, or `Nav + #`, or `Sym + AltGr`)
Numeric keypad on the right hand and window management on the left hand:
* **Right Hand Numpad:**
  * `I`=`7`, `O`=`8`, `P`=`9`
  * `K`=`4`, `L`=`5`, `Ö`=`6`, `Ä`=`0`
  * `M`=`1`, `,`=`2`, `.`=`3`, `-`=`-`
  * `J`=`.`
  * `U`=`@`
* **Left Hand Management:**
  * `Q` &rarr; `Ctrl + Alt + Left`
  * `W` &rarr; `Ctrl + Alt + Right`
  * `E` &rarr; `Ctrl + Alt + Up`
  * `D` &rarr; `Ctrl + Alt + Down`
  * `R` &rarr; `Ctrl + PageUp` (Previous tab)
  * `T` &rarr; `Ctrl + PageDown` (Next tab)
  * `A` &rarr; `Ctrl + Alt + Home`
  * `S` &rarr; `Alt + Home`
  * `F` &rarr; `Alt + End`
  * `G` &rarr; `Ctrl + Alt + End`
  * `C` &rarr; `Ctrl + Alt + PageDown`
  * `V` &rarr; `Ctrl + Alt + PageUp`
* **Shortcuts:**
  * `1` &rarr; `Ctrl + Shift + 1`
  * `2` &rarr; `Ctrl + Shift + 2`
  * `3` &rarr; `Ctrl + Shift + c`
  * `4` &rarr; `Ctrl + Shift + v`
  * `5`..`7` &rarr; `F2`, `F3`, `F4`
  * `8`, `9` &rarr; `F10`, `F11`
  * `0` &rarr; `PageDown`
  * `ß` &rarr; `PageUp`
  * `´` &rarr; `Shift + F10` (Context menu)
  * `Backspace` &rarr; `Ctrl + Alt + Escape`
  * `Z` &rarr; `Volume Up`
  * `<` &rarr; `System Sleep`
  * `B` &rarr; `Delete`
  * `Space` &rarr; `Alt + w`
* `#` in Exo &rarr; Transitions to **Sym Layer**

---

### Keymap Activation Toggle

You can disable or re-enable the entire famak layout on the fly:
* **`Win + Escape` (`#SC001`):** Deactivates famak and switches to **transparent 1:1 passthrough** (raw German QWERTZ).
* **`Win + Backspace` (`#SC00E`):** Re-activates **famak layout**.

---

## Status LED Indicators (`D3` on `PA0`)

* **Normal Operation (Famak Active):** 1 Hz steady heartbeat.
* **Passthrough Mode (Famak Stopped):** 2 Hz slow pulse.
* **Waiting for Keyboard:** Fast 4 Hz flash.
* **On State Change:** 2 quick flashes when activated, 1 long flash when stopped.

---

## Building & Flashing via Docker (Recommended)

Everything builds inside a container without needing tools on your host machine:

```bash
# Build firmware inside container:
./docker-run.sh build

# Flash firmware to the connected STM32 board via ST-Link:
./docker-run.sh flash

# Clean build artifacts:
./docker-run.sh clean

# Open an interactive container shell:
./docker-run.sh shell
```

---

## Related Projects

- Hardware KiCad PCB project: [keysatron](https://github.com/fablackner/keysatron)
