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

#ifndef CONFIG_H
#define CONFIG_H

#include <IPAddress.h>

#define HOSTNAME "awesome-esp32"
#define WIFI_SSID "yourSSID"
#define WIFI_PASSWORD "yourPassword"
#define WIFI_IP IPAddress(192, 168, 1, 100)
#define WIFI_GATEWAY IPAddress(192, 168, 1, 1)
#define WIFI_SUBNET IPAddress(255, 255, 255, 0)
#define WIFI_PRIMARY_DNS IPAddress(1, 1, 1, 1)      // Cloudflare DNS
#define WIFI_SECONDARY_DNS IPAddress(8, 8, 8, 8)    // Google DNS

// mDNS services to register
struct MDNSService {
    const char* service;
    const char* protocol;
    uint16_t port;
};

// Define your mDNS services here
const MDNSService mdnsServices[] = {
    {"http", "tcp", 80},  // HTTP service
    {"mqtt", "tcp", 1883},  // MQTT service
    {"ftp", "tcp", 21},  // FTP service
    {"custom", "tcp", 5000}  // A custom service on port 5000
};

// Log buffer line size
#define MAX_BUFFER_SIZE 100

#endif // config_h
