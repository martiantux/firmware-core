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

#include <Arduino.h>
#include "util/LEDStatusManager/LEDStatusManager.h"
#include "util/WiFiManager/WiFiManager.h"
#include <WebServer.h>

WiFiManager wifiManager;
WebServer server(80);

void handleRoot() {
    server.send(200, "text/plain", "Hello, world!");
}

void setup() {
    Serial.begin(115200);
    LEDStatusManager::getInstance().setStatus(0);
    wifiManager.setup();

    // Set up and start the web server
    server.on("/", handleRoot);

    // Default route handler
    server.onNotFound([]() {
        server.send(404, "text/plain", "Not found. Please check the URL.");
    });

    server.begin();
}

void loop() {
    LEDStatusManager::getInstance().update();
    wifiManager.update();
    server.handleClient();
}
