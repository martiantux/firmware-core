/*
 * Copyright (C) [2024] Bradley James Hammond / Distracted Labs
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 * For inquiries, please contact hello@distractedlabs.cc.
 */

#ifndef WiFiManager_h
#define WiFiManager_h

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include "util/LEDStatusManager/LEDStatusManager.h"
#include "util/LogManager/LogManager.h"

class WiFiManager {
public:
    WiFiManager();
    void setup();                               // Takes care of anything that needs to be initialized in setup()
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
