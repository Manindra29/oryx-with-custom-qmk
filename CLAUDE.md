# CLAUDE.md

## Project Overview

QMK keyboard firmware for two ErgoDox EZ boards, managed via Oryx + custom QMK code. Layout ID: `X3ogP`.

- **ErgoDox EZ (2019)** — Teensy/ATmega32U4, build target `ergodox_ez`, produces `.hex` (office board)
- **ErgoDox EZ ST (2024)** — STM32, build target `ergodox_ez/stm32`, produces `.bin` (home board)

Both share the same `keymap.c` source. Different processors require separate firmware binaries.

## Repository Structure

- `X3ogP/` - Layout source files (keymap, config, rules)
  - `keymap.c` - Key bindings and custom QMK logic (3 layers: Base, Keypad, Media)
  - `config.h` - Keyboard configuration
  - `rules.mk` - Build feature flags
  - `keymap.json` - Oryx-generated layout (do not edit manually)
- `Dockerfile` - QMK build environment
- `qmk_firmware/` - QMK submodule (do not edit)
- `.github/workflows/` - GitHub Action to fetch Oryx changes and build firmware
- `build-all.sh` - Script to build firmware for both boards sequentially

## Key Conventions


- Edit `keymap.c`, `config.h`, and `rules.mk` for custom QMK features
- When keymap.c is updated, update layout.md and layout.html, so the layout stays consistent.
- Never edit `keymap.json` directly — it's overwritten by Oryx on each sync
- Never edit files inside `qmk_firmware/` — it's a submodule managed by the workflow
- Firmware is built via the "Fetch and build layout" GitHub Action
- Run `./build-all.sh` to build for both boards (ST + Teensy) sequentially
- Or trigger a single build: `gh workflow run "Fetch and build layout" --repo Manindra29/oryx-with-custom-qmk -f layout_geometry=ergodox_ez/stm32`

## macOS Globe/Fn Key

The bottom-left row uses `KC_F20` as a placeholder for the Globe/Fn key. Karabiner-Elements remaps F20 to `fn (globe)` on the host machine. See README for setup.

## Upstream

Forked from `poulainpi/oryx-with-custom-qmk`. Sync with `git fetch upstream main && git merge upstream/main`.
