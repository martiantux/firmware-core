/**
 * @author Bradley Hammond
 * @date 2024-02-19
 * @contact hello@bradleyjh.com, brad@distractedlabs.cc
 * 
 * Developed for Distracted Labs. All rights reserved.
 * Unauthorized copying of this file, via any medium, is strictly prohibited.
 */
 
#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID "yourSSID"
#define WIFI_PASSWORD "yourPassword"
#define WIFI_IP IPAddress(192, 168, 1, 100)
#define WIFI_GATEWAY IPAddress(192, 168, 1, 1)
#define WIFI_SUBNET IPAddress(255, 255, 255, 0)
#define WIFI_PRIMARY_DNS IPAddress(1, 1, 1, 1)      // Cloudflare DNS
#define WIFI_SECONDARY_DNS IPAddress(8, 8, 8, 8)    // Google DNS

#endif // config_h
