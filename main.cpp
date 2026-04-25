#include <iostream>
#include <cmath>

/**
 * THE DEADZONE PATCH (Cyber-Physical Calibration Layer)
 * Logic: We ignore all input within a small "radius" around the center.
 * This prevents "mechanical noise" (stick drift) from being read as intent.
 */

struct StickInput {
    float x; // Horizontal Axis (-1.0 to 1.0)
    float y; // Vertical Axis   (-1.0 to 1.0)
};

StickInput applyDeadzone(float rawX, float rawY, float deadzoneThreshold) {
    // 1. Calculate the Magnitude (Distance from center using Pythagorean theorem)
    float magnitude = std::sqrt(rawX * rawX + rawY * rawY);

    // 2. Safety Lock & Logic Gate
    // If magnitude is 0, or falls within the deadzone threshold, force zero state.
    if (magnitude <= deadzoneThreshold || magnitude == 0.0f) {
        return {0.0f, 0.0f};
    }

    // 3. Normalized Output
    // Scales the remaining input so it starts at 0.0 right after the deadzone.
    float scalingFactor = (magnitude - deadzoneThreshold) / (1.0f - deadzoneThreshold);
    
    return {
        (rawX / magnitude) * scalingFactor,
        (rawY / magnitude) * scalingFactor
    };
}

int main() {
    // Example: A robotics sensor or thumbstick sending ghost signals
    float driftX = 0.08f; 
    float driftY = 0.05f;
    float deadzone = 0.15f; // We ignore anything under 15% movement

    StickInput result = applyDeadzone(driftX, driftY, deadzone);

    std::cout << "--- Cyber-Physical Sensor Calibration ---" << std::endl;
    std::cout << "Raw Input (Drift): X=" << driftX << ", Y=" << driftY << std::endl;
    std::cout << "Filtered Output:   X=" << result.x << ", Y=" << result.y << std::endl;
    
    if (result.x == 0.0f && result.y == 0.0f) {
        std::cout << "STATUS: Mechanical hysteresis neutralized successfully." << std::endl;
    }

    return 0;
}
