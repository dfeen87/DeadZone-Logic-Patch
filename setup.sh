#!/bin/bash

echo "========================================"
echo "  DEADZONE-PATCH Workspace Setup        "
echo "  Pact for AI for Good                  "
echo "========================================"

# Step 1: Check if g++ compiler is installed
if ! command -v g++ &> /dev/null
then
    echo "❌ ERROR: g++ compiler could not be found."
    echo "Please install it using: sudo apt install g++ (Ubuntu) or brew install gcc (Mac)"
    exit 1
fi

# Step 2: Ensure Makefile and main.cpp exist in the current directory
if [[ ! -f "Makefile" ]] || [[ ! -f "main.cpp" ]]; then
    echo "❌ ERROR: Missing Makefile or main.cpp in the current directory."
    exit 1
fi

# Step 3: Run the Makefile
echo "⚙️  Initiating build process..."
make clean
make

# Step 4: Confirm success and offer next steps
if [ -f "./deadzone_firmware" ]; then
    echo "========================================"
    echo "✅ Setup Successful!"
    echo "You can now run the firmware using:"
    echo "  ./deadzone_firmware  OR  make run"
    echo "========================================"
else
    echo "❌ ERROR: Build failed. Check compiler output."
fi
