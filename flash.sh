#!/bin/bash

echo "========================================"
echo "  DEADZONE-PATCH Firmware Flasher       "
echo "  Pact for AI for Good                  "
echo "========================================"

# Step 1: Check if arduino-cli is installed
if ! command -v arduino-cli &> /dev/null
then
    echo "❌ ERROR: arduino-cli could not be found."
    echo "Please install it from: https://arduino.github.io/arduino-cli/latest/installation/"
    echo "Or run: curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh"
    exit 1
fi

SKETCH_DIR="deadzone_patch"
FQBN="arduino:avr:micro" # Change this to match your specific board (e.g., teensy:avr:teensy40)

echo "⚙️  Compiling sketch for $FQBN..."
arduino-cli compile --fqbn $FQBN $SKETCH_DIR

if [ $? -ne 0 ]; then
    echo "❌ ERROR: Compilation failed."
    exit 1
fi

echo "✅ Compilation successful."

echo "🔍 Detecting connected boards..."
arduino-cli board list

echo ""
read -p "Enter the PORT of your device (e.g., /dev/ttyACM0 or COM3): " PORT

if [ -z "$PORT" ]; then
    echo "❌ ERROR: No port specified."
    exit 1
fi

echo "🚀 Flashing firmware to $PORT..."
arduino-cli upload -p $PORT --fqbn $FQBN $SKETCH_DIR

if [ $? -eq 0 ]; then
    echo "========================================"
    echo "✅ Firmware flashed successfully!"
    echo "Your device should now reboot with the new deadzone patch."
    echo "========================================"
else
    echo "❌ ERROR: Flashing failed. Please check the port and connection."
    exit 1
fi
