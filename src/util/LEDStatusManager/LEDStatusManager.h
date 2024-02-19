/**
 * @author Bradley Hammond
 * @date 2024-02-19
 * @contact hello@bradleyjh.com, brad@distractedlabs.cc
 * 
 * Developed for Distracted Labs. All rights reserved.
 * Unauthorized copying of this file, via any medium, is strictly prohibited.
 */

#ifndef LEDStatusManager_h
#define LEDStatusManager_h

#include <Arduino.h>

class LEDStatusManager {
public:
    static LEDStatusManager& getInstance() {
        static LEDStatusManager instance;       // Singleton instance
        return instance;
    }

    void update();                              // Periodically called to manage WiFi connection
    void setStatus(int status);                 // Sets the LED status, controlling its blinking pattern

private:
    LEDStatusManager();                         // Private constructor for singleton
    int _status;                                // Current LED status
    unsigned long _lastBlinkTime;               // Timestamp of the last LED blink
    const unsigned long _blinkInterval = 200;   // Duration of each blink in milliseconds
    const unsigned long _pauseInterval = 2000;  // Pause duration between sets of blinks in milliseconds
    int _blinkCount;                            // Current count of blinks in the ongoing sequence
    int _maxBlinks;                             // Maximum number of blinks in the current pattern
    bool _ledState;                             // Current state of the LED (ON/OFF)

    void toggleLED();                           // Toggles the current state of the LED
    void resetBlinkPattern();                   // Resets the blinking pattern based on the current status
};

#endif // LEDStatusManager_h
