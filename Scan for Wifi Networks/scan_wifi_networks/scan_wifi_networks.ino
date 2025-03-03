#include <ESP8266WiFi.h>

bool stopScan = false;  // Flag to stop scanning

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void loop() {
    if (stopScan) {
        Serial.println("Scanning stopped by user.");
        while (true) yield();  // Prevents watchdog reset
    }

    Serial.println("Scanning for Wi-Fi networks...");
    int numNetworks = WiFi.scanNetworks();

    if (numNetworks == 0) {
        Serial.println("No Wi-Fi networks found.");
    } else {
        Serial.println("Networks found:");
        Serial.println("-----------------------------");

        for (int i = 0; i < numNetworks; i++) {
            Serial.print("SSID: ");
            Serial.print(WiFi.SSID(i));

            Serial.print(" | BSSID: ");
            Serial.print(WiFi.BSSIDstr(i));

            Serial.print(" | Signal Strength: ");
            Serial.print(WiFi.RSSI(i));
            Serial.print(" dBm");

            Serial.print(" | Encryption: ");
            switch (WiFi.encryptionType(i)) {
                case ENC_TYPE_WEP: Serial.println(" WEP"); break;
                case ENC_TYPE_TKIP: Serial.println(" WPA/WPA2 (TKIP)"); break;
                case ENC_TYPE_CCMP: Serial.println(" WPA2 (AES)"); break;
                case ENC_TYPE_AUTO: Serial.println(" WPA/WPA2 (Auto)"); break;
                case ENC_TYPE_NONE: Serial.println(" Open (No Password)"); break;
                default: Serial.println(" Unknown");
            }
        }
    }

    Serial.println("-----------------------------");
    Serial.println("Scan complete. Waiting 5 seconds before next scan... Type 'STOP' to end scanning.");

    delay(5000);

    // Check for user input to stop scanning
    if (Serial.available() > 0) {
        String input = Serial.readString();
        input.trim();
        if (input.equalsIgnoreCase("STOP")) {
            stopScan = true;
        }
    }
}
