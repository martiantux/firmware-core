/**
 * @author Bradley Hammond
 * @date 2024-02-19
 * @contact hello@bradleyjh.com, brad@distractedlabs.cc
 * 
 * Developed for Distracted Labs. All rights reserved.
 * Unauthorized copying of this file, via any medium, is strictly prohibited.
 */

#include "util/LEDStatusManager/LEDStatusManager.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 2 // Default LED pin for ESP32 if not defined
#endif

LEDStatusManager::LEDStatusManager() : _status(0), _lastBlinkTime(0), _blinkCount(0), _maxBlinks(0), _ledState(false) {
    pinMode(LED_BUILTIN, OUTPUT);
}

void LEDStatusManager::update() {
    unsigned long currentMillis = millis();

    // Check for pause between sets of blinks
    if (_status != 0 && _blinkCount >= _maxBlinks * 2 && currentMillis - _lastBlinkTime < _pauseInterval) {
        // In pause, do nothing until pause is over
        return;
    }

    // Reset pattern after pause or initially
    if (_status != 0 && _blinkCount >= _maxBlinks * 2 && currentMillis - _lastBlinkTime >= _pauseInterval) {
        resetBlinkPattern();
        return; // Start new set of blinks after pause
    }

    // Continue with blink logic if not pausing and not resetting
    if (_status != 0 && (currentMillis - _lastBlinkTime >= _blinkInterval) && _blinkCount < _maxBlinks * 2) {
        toggleLED();
        _lastBlinkTime = currentMillis;
    }
}

void LEDStatusManager::setStatus(int status) {
    _status = status;
    resetBlinkPattern();

    switch (_status) {
        case 1: _maxBlinks = 1; break; // SD
        case 2: _maxBlinks = 2; break; // WiFi
        case 3: _maxBlinks = 3; break; // WAN
        case 4: _maxBlinks = 4; break; // Config Error
        default: _maxBlinks = 0; break; // LED off for OK status
    }
}

void LEDStatusManager::toggleLED() {
    _ledState = !_ledState;
    digitalWrite(LED_BUILTIN, _ledState ? HIGH : LOW);
    _blinkCount++;
}

void LEDStatusManager::resetBlinkPattern() {
    _blinkCount = 0;
    _lastBlinkTime = millis();
    digitalWrite(LED_BUILTIN, LOW); // Ensure LED is off during pause
    _ledState = false;
}
