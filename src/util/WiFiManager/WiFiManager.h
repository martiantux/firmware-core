/**
 * @author Bradley Hammond
 * @date 2024-02-19
 * @contact hello@bradleyjh.com, brad@distractedlabs.cc
 * 
 * Developed for Distracted Labs. All rights reserved.
 * Unauthorized copying of this file, via any medium, is strictly prohibited.
 */

#ifndef WiFiManager_h
#define WiFiManager_h

#include <Arduino.h>
#include <WiFi.h>
#include "util/LEDStatusManager/LEDStatusManager.h"

class WiFiManager {
public:
    WiFiManager();
    void update();                              // Periodically called to manage WiFi connection

private:
    unsigned long _lastCheckTime;               // Tracks time for managing connection attempts
    bool _attemptingConnection;                 // Indicates if a connection attempt is underway
    int _reconnectionAttempts;                  // Counts the number of reconnection attempts

    void attemptConnection();                   // Initiates a WiFi connection attempt
    void rebootDevice();                        // Reboots the device in an attempt to correct WiFi module issues
    unsigned long calculateBackoffDuration();   // Calculates the backoff duration for reconnection attempts
    void logConnectionStatus();                 // Logs the current WiFi connection status
    void logDebug(const char* message);         // Utility function for logging debug messages
};

#endif // WiFiManager_h
