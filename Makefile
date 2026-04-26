# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

# Target executable name
TARGET = deadzone_firmware

# Source files
SRC = main.cpp

# Default rule when you type 'make'
all: $(TARGET)

# Build the executable
$(TARGET): $(SRC)
	@echo "🛠️  Compiling Firmware..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@echo "✅ Build complete: $(TARGET)"

# Clean up build artifacts
clean:
	@echo "🧹 Cleaning up..."
	rm -f $(TARGET)
	@echo "✅ Clean complete."

# Run the firmware
run: $(TARGET)
	@echo "🚀 Executing Firmware..."
	./$(TARGET)
