// SPDX-FileCopyrightText: 2026 Maxim Dokukin (maxdokukin.com)
// SPDX-License-Identifier: GPL-3.0-only
// xewe-os-module-buttons/xewe-os-module-buttons.ino
//
// Validation firmware for the Buttons module: the XeWeOS framework plus this module.
// Build it with scripts/validate.sh rather than opening this sketch directly.

#include <XeWeOS.h>

#include "src/Buttons/Buttons.h"


xewe::os::ModuleController os({
    .project_name    = "xewe-os-module-buttons",
    .version         = "0.1.0",
    .build_timestamp = __DATE__ " " __TIME__,
    .url             = "https://github.com/xewe-labs/xewe-os-module-buttons",
});

Buttons buttons (os);


void setup() {
    os.begin();
}

void loop() {
    os.loop();
}
