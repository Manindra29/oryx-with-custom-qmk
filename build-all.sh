#!/bin/zsh
REPO="Manindra29/oryx-with-custom-qmk"
LAYOUT="X3ogP"

# Build 1: ST (home keyboard)
echo "Building for ErgoDox EZ ST..."
gh workflow run "Fetch and build layout" --repo $REPO -f layout_geometry=ergodox_ez/stm32

echo "Waiting for workflow to register..."
sleep 15
gh run watch --repo $REPO --exit-status

if [ $? -eq 0 ]; then
  echo "Downloading ST firmware..."
  gh run download --repo $REPO --name "ergodox_ez_stm32_${LAYOUT}" --dir "ergodox_ez_stm32_${LAYOUT}"
  echo "ST firmware saved to ergodox_ez_stm32_${LAYOUT}/"
else
  echo "ST build failed, skipping download."
  exit 1
fi

# Build 2: Teensy (office keyboard)
echo "Building for ErgoDox EZ Teensy..."
gh workflow run "Fetch and build layout" --repo $REPO -f layout_geometry=ergodox_ez

echo "Waiting for workflow to register..."
sleep 15
gh run watch --repo $REPO --exit-status

if [ $? -eq 0 ]; then
  echo "Downloading Teensy firmware..."
  gh run download --repo $REPO --name "ergodox_ez_${LAYOUT}" --dir "ergodox_ez_${LAYOUT}"
  echo "Teensy firmware saved to ergodox_ez_${LAYOUT}/"
else
  echo "Teensy build failed, skipping download."
  exit 1
fi

echo "Both builds complete! Firmware downloaded:"
echo "  Home (ST):     ergodox_ez_stm32_${LAYOUT}/"
echo "  Office (Teensy): ergodox_ez_${LAYOUT}/"
