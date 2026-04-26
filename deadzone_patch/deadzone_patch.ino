/**
 * BARE METAL FIRMWARE: Deadzone-Patch
  * This C++ code is compiled directly into a .bin "Firmware Image," 
 * bypassing the PC's UI and OS to execute directly on the hardware.
 * Target: Arduino Pro Micro / Teensy (USB HID Controller)
 * Thank you to all those that pursue science and contribute to the field. 
 */

#include <Joystick.h>
#include <math.h>

// Initialize the USB Gamepad profile
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Buttons, Hat Switches (Set to 0 for this test)
  true, true, false,     // X, Y, but no Z Axis
  false, false, false,   // No Rx, Ry, Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

// Physical analog pins on the circuit board
const int PIN_X = A0;
const int PIN_Y = A1;

// The Architect's Calibration Threshold
const float DEADZONE_THRESHOLD = 0.15f; 

struct StickInput {
    float x;
    float y;
};

// The core logic (Identical to our previous architecture)
StickInput applyDeadzone(float rawX, float rawY, float threshold) {
    float magnitude = sqrt(rawX * rawX + rawY * rawY);

    if (magnitude <= threshold || magnitude == 0.0f) {
        return {0.0f, 0.0f};
    }

    // Cap magnitude to 1.0 (circular bounds)
    float cappedMagnitude = magnitude;
    if (cappedMagnitude > 1.0f) {
        cappedMagnitude = 1.0f;
    }

    float scalingFactor = (cappedMagnitude - threshold) / (1.0f - threshold);
    
    return {
        (rawX / magnitude) * scalingFactor,
        (rawY / magnitude) * scalingFactor
    };
}

void setup() {
    // Start the USB connection to the PC/Console
    Joystick.begin();
    
    // Standard gamepads use an 8-bit range (-127 to 127)
    Joystick.setXAxisRange(-127, 127);
    Joystick.setYAxisRange(-127, 127);
}

void loop() {
    // 1. Read Raw Voltage from the Potentiometer (0 to 1023)
    int rawADC_X = analogRead(PIN_X);
    int rawADC_Y = analogRead(PIN_Y);

    // 2. Normalize the hardware data to our math range (-1.0 to 1.0)
    float normX = ((rawADC_X / 1023.0f) * 2.0f) - 1.0f;
    float normY = ((rawADC_Y / 1023.0f) * 2.0f) - 1.0f;

    // 3. Apply the Deadzone Filter
    StickInput cleanInput = applyDeadzone(normX, normY, DEADZONE_THRESHOLD);

    // 4. Denormalize back to 8-bit and send the clean signal over USB
    Joystick.setXAxis((int)(cleanInput.x * 127));
    Joystick.setYAxis((int)(cleanInput.y * 127));

    // Polling rate delay (10 milliseconds = 100Hz refresh rate)
    delay(10); 
}
