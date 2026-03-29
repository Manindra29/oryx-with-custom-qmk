# Oryx with custom QMK

This repository allows combining the convenience of [Oryx’s](https://www.zsa.io/oryx) graphical layout editing with the power of [QMK](https://qmk.fm), allowing you to customize your Oryx layout with advanced QMK features like Achordion and Repeat Key, while automating firmware builds through GitHub Actions.

For a detailed guide, check out the full [blog post here](https://blog.zsa.io/oryx-custom-qmk-features).

## How it works

Each time you run the GitHub Action, the workflow will:
1. Fetch the latest changes made in Oryx.
2. Merge them with any QMK features you've added in the source code.
3. Build the firmware, incorporating modifications from both Oryx and your custom source code.

## How to use

1. Fork this repository (be sure to **uncheck the "Copy the main branch only" option**).
2. To initialize the repository with your layout:
   - Go to the **Actions** tab.
   - Select **Fetch and build layout**.
   - Click **Run workflow**.
   - Input your layout ID and keyboard type (your layout must be public in Oryx), then run the workflow.
   - (To avoid having to input values each time, you can modify the default values at the top of the `.github/workflows/fetch-and-build-layout.yml` file).
3. A folder containing your layout will be generated at the root of the repository.
4. You can now add your custom QMK features to this folder:
   - Edit `config.h`, `keymap.c` and `rules.mk` according to the [QMK documentation](https://github.com/qmk/qmk_firmware/tree/master/docs/features).
   - Commit and push to the **main** branch.
5. You can continue editing your layout through Oryx:
   - Make your changes in Oryx. 
   - Optionally, add a description of your changes in the **Some notes about what you changed** field; if provided, this will be used as commit message.
   - Confirm changes by clicking the **Compile this layout** button.
6. To build the firmware (including both Oryx and code modifications), rerun the GitHub Action. The firmware will be available for download in the action’s artifacts.
7. Flash your downloaded firmware using [Keymapp](https://www.zsa.io/flash#flash-keymap).
8. Enjoy!

## Two keyboards, one layout

This repo targets two ErgoDox EZ boards with different hardware:

| Board | Processor | Build target | Firmware | Location |
|-------|-----------|-------------|----------|----------|
| ErgoDox EZ (2019) | Teensy / ATmega32U4 | `ergodox_ez` | `.hex` | Office |
| ErgoDox EZ ST (2024) | STM32 | `ergodox_ez/stm32` | `.bin` | Home |

Both boards share the same `keymap.c` source — only the build target differs. To build firmware for both in one go:

```bash
./build-all.sh
```

This runs the GitHub Action sequentially for each board and waits for each to complete. You can also build for a single board by selecting the keyboard type when manually triggering the workflow.

## macOS Globe/Fn key via Karabiner-Elements

QMK doesn't natively support the macOS Globe/Fn key (Apple checks the keyboard's VID/PID). As a workaround, the bottom-left row is configured to send `KC_F20` in place of the Fn key, matching the Mac modifier order: **Fn, Ctrl, Alt, Cmd**.

To complete the setup in [Karabiner-Elements](https://karabiner-elements.pqrs.org/):

1. Install Karabiner-Elements if you haven't: `brew install --cask karabiner-elements`
2. Open Karabiner-Elements and grant the required accessibility permissions when prompted.
3. Go to **Settings** > **Simple Modifications**.
4. Select your ErgoDox from the **Target device** dropdown.
5. Click **Add item**, set **From key** to `F20` and **To key** to `fn (globe)`.

Alternatively, you can add the rule directly to your `karabiner.json` (usually at `~/.config/karabiner/karabiner.json`). Add this to the `simple_modifications` array for your ErgoDox profile:

```json
{
  "from": { "key_code": "f20" },
  "to": [{ "apple_vendor_top_case_key_code": "keyboard_fn" }]
}
```

You can verify it's working by opening Karabiner-EventViewer and pressing the key — it should show `fn` instead of `F20`.

## Oryx Chrome extension

To make building even easier, [@nivekmai](https://github.com/nivekmai) created an [Oryx Chrome extension](https://chromewebstore.google.com/detail/oryx-extension/bocjciklgnhkejkdfilcikhjfbmbcjal) to be able to trigger the GitHub Actions from inside Oryx itself.
