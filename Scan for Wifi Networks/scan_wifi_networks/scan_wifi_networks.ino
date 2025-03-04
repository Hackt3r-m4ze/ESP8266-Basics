#include <ESP8266WiFi.h>

bool scanActive = true;  // Flag to control scanning

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void loop() {
    // Check for user input to START or STOP scanning
    if (Serial.available() > 0) {
        String input = Serial.readString();
        input.trim();

        if (input.equalsIgnoreCase("STOP")) {
            Serial.println("Scanning stopped. Type 'START' to resume.");
            scanActive = false;  // Disable scanning
        } else if (input.equalsIgnoreCase("START")) {
            Serial.println("Resuming scan...");
            scanActive = true;  // Enable scanning
        }
    }

    // Perform Wi-Fi scanning only if scanning is active
    if (scanActive) {
        Serial.println("Scanning for Wi-Fi networks...");
        int numNetworks = WiFi.scanNetworks();

        if (numNetworks == 0) {
            Serial.println("No Wi-Fi networks found.");
        } else {
            Serial.println("Networks found:");
            Serial.println("-----------------------------");

            for (int i = 0; i < numNetworks; i++) {
                Serial.print("SSID: ");

                // If SSID is empty, it's a hidden network
                if (WiFi.SSID(i).length() == 0) {
                    Serial.print("[HIDDEN]");
                } else {
                    Serial.print(WiFi.SSID(i));
                }

                Serial.print(" | BSSID: ");
                Serial.print(WiFi.BSSIDstr(i));  // Always available

                Serial.print(" | Signal Strength: ");
                Serial.print(WiFi.RSSI(i));  // Always available
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
        Serial.println("Scan complete. Waiting 5 seconds before next scan... Type 'STOP' to pause.");

        delay(5000);
    } else {
        delay(500);  // Short delay to avoid CPU overload when scanning is off
    }
}
