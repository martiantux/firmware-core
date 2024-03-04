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

#include "util/LogManager/LogManager.h"

LogManager::LogManager() : currentLogLevel(INFO) {}

void LogManager::setup() {
    // setup stuffs
}

const char* logLevelToString(LogLevel level) {
    switch (level) {
        case DEBUG: return "DEBUG";
        case INFO: return "INFO";
        case WARN: return "WARN";
        case ERROR: return "ERROR";
        case FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

void LogManager::log(LogLevel level, const String& message) {
    // Get current log time from TimeManager
    String logTime = TimeManager::getInstance().getLogTime();

    // Format the log message for serial/Discord output
    String formattedMessage = String(logTime + " [" + logLevelToString(level) + "] " + message);

    // Log formatted message to serial
    Serial.println(formattedMessage);

    // Create a JSON object for the log entry
    StaticJsonDocument<256> logEntry;
    logEntry["time"] = logTime;
    logEntry["level"] = logLevelToString(level);
    logEntry["message"] = message;

    // Add the log entry to the log buffer array
    logBuffer.add(logEntry);

    // Limit the number of log entries to MAX_LOG_ENTRIES
    if (logBuffer.size() > MAX_BUFFER_SIZE) {
        logBuffer.remove(0); // Remove the oldest entry
    }
}

void LogManager::update() {
    // Placeholder for future needs
}

String LogManager::getBuffer() {
    String output;
    serializeJson(logBuffer, output);
    return output;
}

String LogManager::getLastLogs(size_t lastCount) {
    String output;
    size_t startIndex = logBuffer.size() > lastCount ? logBuffer.size() - lastCount : 0;
    JsonDocument lastLogs;

    for (size_t i = startIndex; i < logBuffer.size(); ++i) {
        lastLogs.add(logBuffer[i]);
    }

    serializeJson(lastLogs, output);
    return output;
}

void LogManager::clearBuffer() {
    logBuffer.clear();
}

void LogManager::sendToDiscord(const String& message) {
    // Implement later, must be non-blocking
}
