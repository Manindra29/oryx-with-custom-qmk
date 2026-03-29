#!/bin/zsh
REPO="Manindra29/oryx-with-custom-qmk"

# Build 1: ST (home keyboard)
echo "Building for ErgoDox EZ ST..."
gh workflow run "Fetch and build layout" --repo $REPO -f layout_geometry=ergodox_ez/stm32

# Wait for it to start, then watch until complete
echo "Waiting for workflow to register..."
sleep 15
gh run watch --repo $REPO --exit-status

# Build 2: Teensy (office keyboard)
echo "Building for ErgoDox EZ Teensy..."
gh workflow run "Fetch and build layout" --repo $REPO -f layout_geometry=ergodox_ez

echo "Waiting for workflow to register..."
sleep 15
gh run watch --repo $REPO --exit-status

echo "Both builds complete!"
