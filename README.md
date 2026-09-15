# xewe-os-module-buttons

Binds commands to physical buttons with software debouncing. A module for [XeWe OS](https://github.com/xewe-labs/xewe-os), built on the
[XeWeOS framework](https://github.com/xewe-labs/xewe-library-os).

## Commands

**Prefix:** `$buttons` · can be disabled

Binds commands to physical buttons with software debouncing.

| Command | Description | Sample Usage |
| :--- | :--- | :--- |
| **`add`** | Add a mapping: `<pin> "<cmd>" <pullup\|pulldown> <on_press\|on_release\|on_change> <debounce_ms>`. | `$buttons add 9 "$system reboot" pullup on_press 50` |
| **`remove`** | Remove a mapping by its id (see `$buttons status`). | `$buttons remove 0` |

## Requirements

| | |
|---|---|
| Modules | none |
| Libraries | XeWeOS (>=0.1.0) and its dependencies (XeWeUtils, XeWeSerial, XeWeNvs, XeWeCli, ArduinoJson) |
| Boards | ESP32-C3, ESP32-C6, ESP32-S3 (arduino-esp32 3.x) |

Metadata and dependencies are declared in [`module.properties`](module.properties).

## Layout

| Path | |
|---|---|
| `src/Buttons/` | the module |
| `xewe-os-module-buttons.ino` | validation firmware: framework + required modules + this module |
| `scripts/validate.sh` | assembles and compiles the validation firmware |

## Validate

Clone the modules this one requires next to this repo, then:

```bash
scripts/validate.sh                         # compile for c3, c6 and s3
scripts/validate.sh -b c3                   # one board
scripts/validate.sh -b c3 -p /dev/ttyACM0   # compile, upload and run on a board
```

The script copies this module and its required modules into `build/xewe-os-module-buttons/` and compiles it with
`arduino-cli`. Environment variables:

* `XEWE_MODULES_DIR` - where required module repos are cloned (default: the folder containing this repo)
* `XEWE_LIBRARIES_DIR` - folder with `xewe-library-*` clones to build against instead of installed libraries

## Use in firmware

Copy `src/Buttons/` (and the required modules' folders) into the sketch's `src/`, then:

```cpp
#include "src/Buttons/Buttons.h"

Buttons buttons(os);
```

Declare required modules before this one.

## License

GPL-3.0. See [LICENSE.txt](LICENSE.txt).
