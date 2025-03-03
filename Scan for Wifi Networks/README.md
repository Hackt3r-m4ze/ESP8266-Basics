## How the program works

| Step | What It Does |
| ---- | -------------|
| Setup | Starts Serial Monitor, sets ESP8266 to Station Mode |
| Loop Starts | Runs continuously unless user stops it |
| Wi-Fi Scan | Scans nearby Wi-Fi networks using WiFi.scanNetworks() |
| Display Results | Prints SSID, BSSID, Signal Strength, Encryption Type |
| Wait 5 Seconds | Pauses before scanning again |
| Check for STOP Command | If the user types "STOP", scanning stops |
| Check for START Command | If the user types "STARt", scanning starts |

## What the Output Means

- SSID: Wi-Fi network name.
- BSSID: MAC address of the router.
- Signal Strength (RSSI in dBm):
    -30 dBm = Excellent (very close).
    -50 dBm = Good.
    -70 dBm = Weak.
    -90 dBm = Very bad (almost out of range).
- Encryption Type:
    - Open = No password (Vulnerable).
    - WPA/WPA2 = Secure networks.
    - WEP = Very weak encryption (can be cracked easily).

## Limitations of scanning with EPS8622

- It cannot detect WPA3 encryption devices
- It cannot detect 5GHz frequency devices
- To do this we would need an wifi adapter

## Hidden network (SSID) detection Limitations

- Sometimes when trying to detect hidden networks or networks without SSID this code might not work as some routers will not send the beacon frame when SSID is not being sent. 
- To detect this we would need to use another program that will capture the probe request and reveal the hidden identity.
- Use the scan_probes2detect_hidden_nw code for this exercise.
