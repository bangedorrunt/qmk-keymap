# QMK Userspace Codebase Guidelines

This document provides guidelines for AI coding agents working with this QMK userspace repository.

## Repository Structure

```
.
├── keyboards/               # Keyboard-specific keymaps
│   └── keychron/k3_pro/ansi/rgb/keymaps/
│       ├── default/        # Stock keymap
│       └── getreuer/       # Custom keymap (primary)
├── layouts/                # Layout-based keymaps (alternative structure)
├── users/                  # User-specific shared code (alternative structure)
├── features/               # Local copies of custom QMK features
├── modules/                # Git submodules for external feature libraries
├── bangedorrunt.c          # User-specific shared code
├── bangedorrunt.h          # User-specific shared header
├── rules.mk                # Global build configuration
├── qmk.json                # Build targets configuration
└── Makefile                # Build system entry point
```

## Build System

### Build Targets
- Build targets are defined in `qmk.json`
- Current target: `["keychron/k3_pro/ansi/rgb", "getreuer"]`
- Add targets: `qmk userspace-add -kb <keyboard> -km <keymap>`
- List targets: `qmk userspace-list`
- Build all: `qmk userspace-compile`

### Configuration Hierarchy
Settings are applied in priority order (lowest to highest):
1. QMK defaults
2. Keyboard defaults
3. **Root `rules.mk`** (userspace global settings)
4. Keymap `rules.mk`
5. Keymap `config.h`

### Root rules.mk
The root `rules.mk` sets **global defaults** for all keymaps:
```make
KEY_OVERRIDE_ENABLE ?= yes
TAP_DANCE_ENABLE ?= yes
COMBO_ENABLE = yes
REPEAT_KEY_ENABLE = yes
CAPS_WORD_ENABLE ?= yes
NKRO_ENABLE ?= yes
# Disabled features
CONSOLE_ENABLE ?= no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
BOOTMAGIC_ENABLE ?= no
```
- Use `?=` for features that keymaps can override
- Use `=` for features that should be enforced

### Keymap rules.mk
Keymap-specific `rules.mk` must include the root configuration:
```make
ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
include ${ROOT_DIR}../../../../../../../rules.mk
```

## Code Organization Patterns

### Keymap Structure
```c
// keyboards/keychron/k3_pro/ansi/rgb/keymaps/getreuer/keymap.c
#include QMK_KEYBOARD_H
#include "bangedorrunt.c"  // Include shared user code directly

// Layer definitions
enum layers { MAC_BASE, MAC_FN, WIN_BASE, WIN_FN, SYM, NUM };

// Custom keycodes
enum custom_keycodes { LLOCK = SAFE_RANGE, USRNAME };

// Keymap arrays
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { ... };
```

### Shared User Code Pattern
**Instead of using `users/<username>/` directory**, this codebase uses:
- `bangedorrunt.c` - Implementation of shared functions and macros
- `bangedorrunt.h` - Shared declarations, enums, and constants

This pattern is **included directly** in the keymap with `#include "bangedorrunt.c"`.

### Config File Structure
```c
// keyboards/keychron/k3_pro/ansi/rgb/keymaps/getreuer/config.h
#pragma once
#include "bangedorrunt.h"

#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define TAPPING_TERM 240
#define FLOW_TAP_TERM 100
// ... other configuration
```

## Feature Management

### Local Features
The `features/` directory contains local copies of custom QMK features:
- achordion (bilateral combinations)
- autocorrection
- caps_word
- custom_shift_keys
- layer_lock
- repeat_key
- select_word
- sentence_case
- socd_cleaner
- And more...

These are standalone `.c` and `.h` files that can be selectively included.

### External Feature Modules
The `modules/` directory uses git submodules for external feature libraries:
```bash
# modules/getreuer is a submodule
git submodule add https://github.com/getreuer/qmk-modules.git modules/getreuer
```

## Coding Conventions

### Home Row Mods Pattern
```c
// Define short aliases for home row mods
#define HRM_A LT(SYM, KC_A)
#define HRM_S LALT_T(KC_S)
#define HRM_D LCMD_T(KC_D)
#define HRM_F LCTL_T(KC_F)
// ... mirror for right hand
```

### Tap-Hold Configuration
```c
// Always implement per-key configuration
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) { ... }
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) { ... }
```

### Custom Keycode Processing
```c
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (record->event.pressed) {
    switch (keycode) {
      case USRNAME:
        SEND_STRING_DELAY("bangedorrunt", TAP_CODE_DELAY);
        return false;
    }
  }
  return true;
}
```

### Layer Definitions
```c
// Use descriptive enum names
enum layers {
  MAC_BASE,   // Base layer for macOS
  MAC_FN,     // Function layer for macOS
  WIN_BASE,   // Base layer for Windows
  WIN_FN,     // Function layer for Windows
  SYM,        // Symbol layer
  NUM,        // Number pad layer
};
```

### Key Overrides
```c
#ifdef KEY_OVERRIDE_ENABLE
const key_override_t hypr_j_override =
    ko_make_basic(MOD_MASK_CSAG, HRM_J, KC_DOWN);
// Register overrides
const key_override_t* key_overrides[] = { ... };
#endif
```

## Development Workflow

### Building
```bash
# Build specific target
qmk compile -kb keychron/k3_pro/ansi/rgb -km getreuer

# Build all userspace targets
qmk userspace-compile

# Using make directly
make keychron/k3_pro/ansi/rgb:getreuer
```

### Adding a New Keymap
```bash
qmk new-keymap -kb <keyboard> -km <keymap_name>
qmk userspace-add -kb <keyboard> -km <keymap_name>
```

### File Changes
- When modifying keymaps, always check the corresponding `config.h` and `rules.mk`
- When adding features, decide if they belong in `features/`, `modules/`, or shared user files
- Update root `rules.mk` only for global feature defaults

## AI Agent Best Practices

1. **Always read existing files** before making changes to understand current patterns
2. **Check root `rules.mk`** to understand enabled features before using them
3. **Include shared code correctly**: Use `#include "bangedorrunt.c"` pattern, not `users/` directory
4. **Follow tap-hold patterns**: Implement per-key functions when using home row mods
5. **Use feature guards**: Wrap feature-specific code with `#ifdef FEATURE_ENABLE`
6. **Match existing style**: This codebase uses specific naming conventions (HRM_, NAV_, NUM_, etc.)
7. **Test build targets**: Verify changes with `qmk userspace-compile` before committing
8. **Git submodules**: Use `git submodule update --init --recursive` after cloning

## Common Pitfalls

- ❌ Don't create `users/<username>/` directory - use root-level shared files
- ❌ Don't forget to include root `rules.mk` in keymap `rules.mk`
- ❌ Don't enable features in root `rules.mk` without `?=` unless enforcing globally
- ❌ Don't hardcode paths - use `$(dir $(realpath $(lastword $(MAKEFILE_LIST))))` pattern
- ✅ Do use direct includes for shared code: `#include "bangedorrunt.c"`
- ✅ Do use git submodules for external feature libraries
- ✅ Do implement per-key tap-hold functions for home row mods
- ✅ Do use feature guards (`#ifdef`) around optional feature code
