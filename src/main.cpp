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
#include "util/LogManager/LogManager.h"
#include "util/LEDStatusManager/LEDStatusManager.h"
#include "util/WiFiManager/WiFiManager.h"
#include "util/TimeManager/TimeManager.h"
#include <WebServer.h>

WiFiManager wifiManager;
WebServer server(80);

void handleRoot() {
    server.send(200, "text/plain", "Hello, world!");
}

void handleLogs() {
    String htmlContent = "<!DOCTYPE html>\n<html>\n<head>\n<title>Log Viewer</title>\n<style>\n";
    htmlContent += "body { font-family: 'Arial', sans-serif; background-color: #f0f0f0; color: #333; }\n";
    htmlContent += "#logContainer { margin: auto; width: 80%; background-color: #fff; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }\n";
    htmlContent += "ul { list-style-type: none; padding: 0; }\n";
    htmlContent += "li { margin: 10px 0; }\n";
    htmlContent += "</style>\n</head>\n<body>\n<div id='logContainer'>\n<h2>System Logs</h2>\n<ul>\n";

    String logs = LogManager::getInstance().getLastLogs(20);
    DynamicJsonDocument doc(4096); // Adjust the size according to your log buffer size
    DeserializationError error = deserializeJson(doc, logs);

    if (!error) {
        JsonArray array = doc.as<JsonArray>();
        for (JsonObject logEntry : array) {
            String time = logEntry["time"];
            String level = logEntry["level"];
            String message = logEntry["message"];
            htmlContent += "<li>[" + time + "] <b>" + level + "</b>: " + message + "</li>\n";
        }
    } else {
        htmlContent += "<li>Error parsing logs</li>\n";
    }

    htmlContent += "</ul>\n</div>\n</body>\n</html>";

    server.send(200, "text/html", htmlContent);
}

void setup() {
    LogManager::getInstance().log(INFO, "Devicing starting up");
    Serial.begin(115200);
    LEDStatusManager::getInstance().setStatus(0);
    wifiManager.setup();

    LogManager::getInstance().setup();
    TimeManager::getInstance().setup("pool.ntp.org", 0);

    server.on("/", handleRoot);
    server.on("/logs", handleLogs);

    server.onNotFound([]() {
        server.send(404, "text/plain", "Not found. Please check the URL.");
    });

    LogManager::getInstance().log(INFO, "Startup finished");
    server.begin();
}

void loop() {
    LEDStatusManager::getInstance().update();
    wifiManager.update();
    LogManager::getInstance().update();
    TimeManager::getInstance().update();
    server.handleClient();
}
