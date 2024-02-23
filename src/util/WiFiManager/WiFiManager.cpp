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

#include "util/WiFiManager/WiFiManager.h"
#include "util/config.h"

WiFiManager::WiFiManager() : _lastCheckTime(0), _attemptingConnection(false), _reconnectionAttempts(0) {
    logDebug("WiFiManager initialized");
}

void WiFiManager::setup() {
    WiFi.mode(WIFI_STA);

    if (!MDNS.begin(HOSTNAME)) {
        logDebug("Failed to start mDNS responder");
        return;
    }
    logDebug("mDNS responder started");

    // Register mDNS services
    for (const auto& service : mdnsServices) {
        MDNS.addService(service.service, service.protocol, service.port);
        logDebug((String("Registered mDNS service: ") + service.service).c_str());
    }
    logDebug("WiFiManager setup complete");
}

void WiFiManager::update() {
    if (WiFi.status() == WL_CONNECTED && !_attemptingConnection) { return; }  // If connected, no further action needed

    if (_reconnectionAttempts > 5) {  // After 5 failed attempts, reset the WiFi module
        logDebug("Maximum reconnection attempts reached. Resetting WiFi module.");
        rebootDevice();
        _reconnectionAttempts = 0;
    }

    if (millis() - _lastCheckTime > calculateBackoffDuration()) {
        attemptConnection();
    }
}

void WiFiManager::attemptConnection() {
    if (WiFi.status() != WL_CONNECTED && !_attemptingConnection) {
        logDebug("Attempting WiFi connection...");
        WiFi.config(WIFI_IP, WIFI_GATEWAY, WIFI_SUBNET, WIFI_PRIMARY_DNS, WIFI_SECONDARY_DNS);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        _attemptingConnection = true;
        _lastCheckTime = millis();
        _reconnectionAttempts++;
        LEDStatusManager::getInstance().setStatus(2); // Indicate WiFi connection attempt
    } else if (_attemptingConnection && millis() - _lastCheckTime > 20000) {
        logDebug("Connection attempt timed out.");
        _attemptingConnection = false;
        logConnectionStatus();
    } else if (WiFi.status() == WL_CONNECTED) {
        _attemptingConnection = false;
        _reconnectionAttempts = 0;
        logConnectionStatus();
        LEDStatusManager::getInstance().setStatus(0); // WiFi connected, turn off LED
    }
}

void WiFiManager::rebootDevice() {
    WiFi.disconnect(true);
    delay(1000);    // Allow some time for the disconnect to complete
    ESP.restart();  // Restart the ESP32
    logDebug("ESP32 restarting.");
}

unsigned long WiFiManager::calculateBackoffDuration() {
    unsigned long backoffDuration = 3 * pow(2, _reconnectionAttempts - 1) * 1000;  // Start with 3 seconds
    return backoffDuration;
}

void WiFiManager::logConnectionStatus() {
    if (WiFi.status() == WL_CONNECTED) {
        logDebug("WiFi connected successfully.");
    } else {
        logDebug("Failed to connect to WiFi.");
    }
}

void WiFiManager::logDebug(const char* message) {
    // Implement logging later, for now print to serial.
    Serial.println(message);
}
