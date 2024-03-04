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

#ifndef TimeManager_h
#define TimeManager_h

#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "util/LogManager/LogManager.h"

class TimeManager {
public:
    static TimeManager& getInstance() {
        static TimeManager instance;
        return instance;
    }

    void setup(const char* ntpServer = "pool.ntp.org", long timezoneOffset = 0);
    void update();
    unsigned long getCurrentTimestamp();
    String getLogTime();
    String getLongDate();
    String getShortDate();
    String getTimeString();
    void setNTPServer(const char* ntpServer);
    void setTimezoneOffset(long timezoneOffset);

private:
    TimeManager();
    ~TimeManager();
    TimeManager(const TimeManager&) = delete;
    TimeManager& operator=(const TimeManager&) = delete;

    WiFiUDP ntpUDP;
    NTPClient timeClient;
    const long updateInterval = 60000; // Sync interval in milliseconds
    unsigned long lastSyncTime = 0;
    const char* ntpServer;
    long timezoneOffset;

    void syncTime();
};

#endif // TimeManager_h
