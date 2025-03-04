#include <ESP8266WiFi.h>

bool sniffingActive = false;  // Start with sniffing OFF

void wifiSniffer(uint8_t *buf, uint16_t len) {
    if (!sniffingActive) return;  // Ignore packets if sniffing is disabled
    if (len < 36) return;  // Ignore small packets

    int ssid_length = buf[25];  // Extract SSID length from packet

    // Validate SSID length (must be between 1 and 32 characters)
    if (ssid_length > 0 && ssid_length < 32 && len >= (26 + ssid_length)) {
        String ssid = "";
        for (int i = 26; i < (26 + ssid_length); i++) {
            if (isprint(buf[i])) {  // Only allow readable characters
                ssid += (char)buf[i];
            }
        }

        // Only print SSID if it's valid (not empty)
        if (ssid.length() > 0 && ssid != "[HIDDEN]") {
            Serial.print("📡 Hidden SSID Revealed: ");
            Serial.println(ssid);
        }
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    wifi_set_opmode(STATION_MODE);
    wifi_promiscuous_enable(0);  // Start with sniffing disabled
    wifi_set_promiscuous_rx_cb(NULL);  // Unregister callback initially

    // **Proper startup message**
    Serial.println("==========================================");
    Serial.println("Type 'START' to begin sniffing hidden SSIDs.");
    Serial.println("Type 'STOP' to stop sniffing.");
    Serial.println("==========================================");
}

void loop() {
    // Check for user input to START or STOP sniffing
    if (Serial.available() > 0) {
        String input = Serial.readString();
        input.trim();

        if (input.equalsIgnoreCase("STOP") && sniffingActive) {
            Serial.println("Sniffing stopped. Type 'START' to resume.");
            wifi_promiscuous_enable(0);  // Disable sniffing
            wifi_set_promiscuous_rx_cb(NULL);  // Unregister callback
            sniffingActive = false;
        } 
        else if (input.equalsIgnoreCase("START") && !sniffingActive) {
            Serial.println("Sniffing started... Looking for hidden SSIDs.");
            wifi_promiscuous_enable(1);  // Enable sniffing
            wifi_set_promiscuous_rx_cb(wifiSniffer);  // Register callback again
            sniffingActive = true;
        }
    }

    delay(500);  // Avoid excessive CPU usage
}
