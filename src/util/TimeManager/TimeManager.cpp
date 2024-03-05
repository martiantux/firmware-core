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

#include "util/TimeManager/TimeManager.h"

TimeManager::TimeManager() : timeClient(ntpUDP) {}

TimeManager::~TimeManager() {}

void TimeManager::setup(const char* ntpServer, long timezoneOffset) {
    this->ntpServer = ntpServer;
    this->timezoneOffset = timezoneOffset;
    timeClient.setPoolServerName(ntpServer);
    timeClient.setTimeOffset(timezoneOffset);
    timeClient.begin();
}

void TimeManager::update() {
    unsigned long currentMillis = millis();
    if (lastSyncTime || currentMillis - lastSyncTime >= updateInterval) {
        if (WiFi.status() == WL_CONNECTED) {
            syncTime();
            lastSyncTime = currentMillis;
        }
    }

    // Any other time keeping update code
}

void TimeManager::syncTime() {
    LogManager::getInstance().log(INFO, "Attempting time synchronization...");
    if (!timeClient.forceUpdate()) {
        LogManager::getInstance().log(WARN, "Failed to sync time with NTP server.");
    }
    else {
        LogManager::getInstance().log(INFO, "Time synchronization sucessful.");
    }
}

unsigned long TimeManager::getCurrentTimestamp() {
    return timeClient.getEpochTime();
}

String TimeManager::getLogTime() {
    // TODO: This should provide millis until we have time sync, then correct unix timestamps.
    // TODO: Might be good to log both millis() AND unix stamp.

    return String(millis());
}

String TimeManager::getLongDate() {
    return timeClient.getFormattedTime() + " - " + timeClient.getDay() + ", " + timeClient.getFormattedTime();
}

String TimeManager::getShortDate() {
    return timeClient.getFormattedTime() + " - " + timeClient.getDay();
}

String TimeManager::getTimeString() {
    return timeClient.getFormattedTime();
}

void TimeManager::setNTPServer(const char* ntpServer) {
    this->ntpServer = ntpServer;
    timeClient.setPoolServerName(ntpServer);
}

void TimeManager::setTimezoneOffset(long timezoneOffset) {
    this->timezoneOffset = timezoneOffset;
    timeClient.setTimeOffset(timezoneOffset);
}
