#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

/**
 * DEADZONE-PATCH (Firmware Level)
 * Cyber-Physical Calibration Layer
 */

struct StickInput {
    float x; 
    float y; 
};

StickInput applyDeadzone(float rawX, float rawY, float deadzoneThreshold) {
    float magnitude = std::sqrt(rawX * rawX + rawY * rawY);

    // Failsafe & Logic Gate
    if (magnitude <= deadzoneThreshold || magnitude == 0.0f) {
        return {0.0f, 0.0f};
    }

    // Cap magnitude to 1.0 (circular bounds)
    float cappedMagnitude = magnitude;
    if (cappedMagnitude > 1.0f) {
        cappedMagnitude = 1.0f;
    }

    // Normalized Output
    float scalingFactor = (cappedMagnitude - deadzoneThreshold) / (1.0f - deadzoneThreshold);
    
    return {
        (rawX / magnitude) * scalingFactor,
        (rawY / magnitude) * scalingFactor
    };
}

int main() {
    std::cout << "--- Initializing Deadzone-Patch Firmware ---" << std::endl;
    float deadzone = 0.12f; // 12% Hardware tolerance threshold
    
    // Simulating a stream of hardware inputs (e.g., polling a sensor)
    StickInput simulatedHardwareBuffer[] = {
        {0.08f, 0.05f},   // Drift (Should be neutralized)
        {0.11f, -0.02f},  // Drift (Should be neutralized)
        {0.45f, 0.60f},   // Actual Intentional Movement
        {-0.90f, 0.10f},  // Actual Intentional Movement
        {1.00f, 1.00f}    // Corner test (Magnitude > 1.0)
    };

    int bufferSize = sizeof(simulatedHardwareBuffer) / sizeof(simulatedHardwareBuffer[0]);

    std::cout << "[SYSTEM] Threshold set to: " << (deadzone * 100) << "%" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    for (int i = 0; i < bufferSize; i++) {
        float rx = simulatedHardwareBuffer[i].x;
        float ry = simulatedHardwareBuffer[i].y;
        
        StickInput filtered = applyDeadzone(rx, ry, deadzone);

        std::cout << "Raw Sensor [X: " << rx << ", Y: " << ry << "] ";
        
        if (filtered.x == 0.0f && filtered.y == 0.0f) {
             std::cout << "-> NOISE FILTERED (Output: 0, 0)\n";
        } else {
             std::cout << "-> SIGNAL PASSED  (Output: X:" << filtered.x << " Y:" << filtered.y << ")\n";
        }

        // Simulating the clock cycle delay of an embedded system
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "[SYSTEM] Buffer reading complete." << std::endl;

    return 0;
}
