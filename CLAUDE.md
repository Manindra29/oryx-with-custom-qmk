# CLAUDE.md

## Project Overview

ErgoDox EZ (STM32) QMK keyboard firmware, managed via Oryx + custom QMK code. Layout ID: `X3ogP`.

## Repository Structure

- `X3ogP/` - Layout source files (keymap, config, rules)
  - `keymap.c` - Key bindings and custom QMK logic (3 layers: Base, Keypad, Media)
  - `config.h` - Keyboard configuration
  - `rules.mk` - Build feature flags
  - `keymap.json` - Oryx-generated layout (do not edit manually)
- `Dockerfile` - QMK build environment
- `qmk_firmware/` - QMK submodule (do not edit)
- `.github/workflows/` - GitHub Action to fetch Oryx changes and build firmware

## Key Conventions

- Edit `keymap.c`, `config.h`, and `rules.mk` for custom QMK features
- Never edit `keymap.json` directly — it's overwritten by Oryx on each sync
- Never edit files inside `qmk_firmware/` — it's a submodule managed by the workflow
- Firmware is built via the "Fetch and build layout" GitHub Action
- Use `gh workflow run "Fetch and build layout" --repo Manindra29/oryx-with-custom-qmk` to trigger builds

## macOS Globe/Fn Key

The bottom-left row uses `KC_F20` as a placeholder for the Globe/Fn key. Karabiner-Elements remaps F20 to `fn (globe)` on the host machine. See README for setup.

## Upstream

Forked from `poulainpi/oryx-with-custom-qmk`. Sync with `git fetch upstream main && git merge upstream/main`.
