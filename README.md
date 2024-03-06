# Unified Firmware Core for IoT Projects

## Overview
The Firmware-Core is a foundational software framework designed for Distracted Labs IoT projects, offering essential functionalities and connectivity options to facilitate development, ensure consistency, and enhance reliability across various IoT applications.

## Modules

### LEDStatusManager
LEDStatusManager provides an interface for controlling an LED indicator, making it easy to signal the device's status and any operational alerts. It's particularly useful for debugging and providing visual feedback on the device's state before logging etc may be available.

**Features**:
- **Multiple Status Indications**: Support for various LED blinking patterns to represent different statuses, such as connectivity status, error codes, or operational states.
- **Non-blocking Operation**: Implements a non-blocking approach to ensure LED status updates do not interfere with the core functionalities of the device.
- **Easy Integration**: Designed for straightforward integration with other modules to visually indicate their status or errors.

**Usage**:
```
LEDStatusManager ledManager;                    // Create an instance
LEDStatusManager::getInstance().update();       // Call update in your main loop to handle LED changes

LEDStatusManager::getInstance().setStatus(0);   // Set OK status / no indicator flashing
LEDStatusManager::getInstance().setStatus(1);   // Flash once before pausing
LEDStatusManager::getInstance().setStatus(5);   // Flash 5 times before pausing
```

### WiFiManager
WiFiManager handles all aspects of WiFi connectivity, from network scanning and connection to managing reconnection strategies. It ensures that the device maintains a stable and reliable WiFi connection, crucial for IoT applications reliant on real-time network communication.

**Features**:
- **Auto-Reconnect**: Implements an exponential backoff strategy for reconnections, minimizing network strain while ensuring the device reconnects as soon as possible.
- **Connection Status Monitoring**: Provides real-time feedback on the WiFi connection status, which can be used by other modules or indicated through LEDs.
- **Configurable Network Credentials**: Integrates with the configuration system to allow dynamic setting of WiFi SSIDs and passwords.
- **DNS Reliability**: Utilizes both Cloudflare (1.1.1.1) and Google (8.8.8.8) DNS servers to enhance connectivity reliability and bypass potential local network DNS issues, ensuring higher uptime and stability.

**Usage**:
```
WiFiManager wifiManager;    // Create an instance
wifiManager.setup();        // Call in your setup() to init and connect to wifi
wifiManager.update();       // Call update in your main loop to manage WiFi connectivity
```
## License and Credits

This project, developed by Bradley James Hammond (Martian Tux) and Distracted Labs, is licensed under the GNU General Public License v3.0. Full license text is available in the [LICENSE](LICENSE) file.

Contributions, feedback, and adaptations are welcome in accordance with the terms of this license. Please credit and provide a link back to the original source when using this project or its components.

For inquiries or further information, contact martiantux@proton.me or hello@distractedlabs.cc.

Stay connected and support my projects:
- [Follow on Instagram](https://instagram.com/martiantux)
- [Chat on Telegram](https://t.me/martiantux)
- [Support on Patreon](https://patreon.com/martiantux)
