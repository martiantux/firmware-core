
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

#define INDICATOR_LED_PIN 2             // Pin to use for indicator LED
#define MAX_BUFFER_SIZE 100             // Max log lines to keep in the buffer
#define NTP_SERVER "pool.ntp.org"       // NTP time sync server
#define TIMEZONE_OFFSET 0               // Timezone offset in seconds

struct MDNSService {
    const char* service;
    const char* protocol;
    uint16_t port;
};

const MDNSService mdnsServices[] = {
    {"http", "tcp", 80},        // HTTP service
    {"mqtt", "tcp", 1883},      // MQTT service
    {"ftp", "tcp", 21},         // FTP service
    {"custom", "tcp", 5000}     // A custom service on port 5000
};

#endif // config_h
