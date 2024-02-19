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

WiFiManager wifiManager;

void setup() {
  Serial.begin(115200);
  LEDStatusManager::getInstance().setStatus(0);
}

void loop() {
    LEDStatusManager::getInstance().update();
    wifiManager.update();
}
