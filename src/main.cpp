/**
 * @author Bradley Hammond
 * @date 2024-02-19
 * @contact hello@bradleyjh.com, brad@distractedlabs.cc
 * 
 * Developed for Distracted Labs. All rights reserved.
 * Unauthorized copying of this file, via any medium, is strictly prohibited.
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
