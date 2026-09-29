# xewe-os-module-buttons — bind CLI commands to physical buttons

XeWe OS module · created 2026-09-15 (split out of xewe-os, where it was developed from 2026-01) · Solo: Max Dokukin · Status: Active (0.1.0)

## Overview

Binds commands to physical buttons with software debouncing. A module for
[XeWe OS](https://github.com/xewe-labs/xewe-os), built on the
[XeWeOS framework](https://github.com/xewe-labs/xewe-library-os). Each mapping ties a GPIO pin,
an input mode (pull-up or pull-down), a trigger event (press, release or change) and a debounce
interval to one CLI command, so a button can do anything the command line can — reboot the board,
toggle a pin, run a schedule. Mappings are stored in NVS and restored on boot without any setup
prompt.

## Highlights

- Per-button software debouncing: a state change is accepted only after it has been stable for the mapping's interval (default 50 ms) (`Buttons::loop`)
- Three trigger events (`on_press`, `on_release`, `on_change`) and two input modes (`pullup`, `pulldown`); "pressed" is derived from the input mode
- Mappings are `FlexData` records persisted as one NVS entry; runtime-only debounce state is not stored
- `$buttons status` prints a table of active mappings (ID, pin, command, debounce, type, event)

## How it works

```
$buttons add 9 "$system reboot" pullup on_press 50 → pinMode(INPUT_PULLUP) → ButtonData{id = max+1} → NVS
loop: digitalRead → stable for debounce_ms? → state changed? → event matches? → xewe_cli.execute(command)
```

- **`Buttons` class** (`src/Buttons/`) — a `xewe::os::Module` with id `buttons`; no first-boot setup; can be disabled.
- **API** — `add(pin, command, type, event, debounce)`, `remove(id)`, `load_from_nvs()`, `save_to_nvs()`.

### Commands

**Prefix:** `$buttons` · can be disabled

| Command | Description | Sample Usage |
| :--- | :--- | :--- |
| **`add`** | Add a mapping: `<pin> "<cmd>" <pullup\|pulldown> <on_press\|on_release\|on_change> <debounce_ms>`. | `$buttons add 9 "$system reboot" pullup on_press 50` |
| **`remove`** | Remove a mapping by its id (see `$buttons status`). | `$buttons remove 0` |

### Requirements

| | |
|---|---|
| Modules | none |
| Libraries | XeWeOS (>=0.1.0) and its dependencies (XeWeUtils, XeWeSerial, XeWeNvs, XeWeCli, ArduinoJson) |
| Boards | ESP32-C3, ESP32-C6, ESP32-S3 (arduino-esp32 3.x) |

Metadata and dependencies are declared in [`module.properties`](module.properties).

### Layout

| Path | |
|---|---|
| `src/Buttons/` | the module (`Buttons.h`, `Buttons.cpp`) |
| `xewe-os-module-buttons.ino` | validation firmware: framework + this module |
| `scripts/validate.sh` | assembles and compiles the validation firmware |
| `module.properties` | metadata read by xewe-os `setup.sh` and `validate.sh` |

## Results

| Metric | Value | Baseline / note |
|---|---|---|
| Source | 399 lines (`Buttons.h` 92, `Buttons.cpp` 307) | `wc -l` |
| Commands | 2 | `add`, `remove` |
| Default debounce | 50 ms | per mapping, configurable |

A module has no measured results; the table lists what it provides.

## Getting started

### Use in XeWe OS

Choose `buttons` in xewe-os `setup.sh`.

### Validate

```bash
scripts/validate.sh                         # compile for c3, c6 and s3
scripts/validate.sh -b c3                   # one board
scripts/validate.sh -b c3 -p /dev/ttyACM0   # compile, upload and run on a board
```

The script copies this module into `build/xewe-os-module-buttons/` and compiles it with
`arduino-cli`. Environment variables:

* `XEWE_MODULES_DIR` - where required module repos are cloned (default: the folder containing this repo)
* `XEWE_LIBRARIES_DIR` - folder with `xewe-library-*` clones to build against instead of installed libraries

### Use in firmware

Copy `src/Buttons/` into the sketch's `src/`, then:

```cpp
#include "src/Buttons/Buttons.h"

Buttons buttons(os);
```

## Documents

- [module.properties](module.properties)
- Firmware: [xewe-os](https://github.com/xewe-labs/xewe-os) · registry: [xewe-os-modules](https://github.com/xewe-labs/xewe-os-modules) · framework: [xewe-library-os](https://github.com/xewe-labs/xewe-library-os)
- License: GPL-3.0. See [LICENSE.txt](LICENSE.txt).
