#define LED_PIN 2  // GPIO2 (D4 on NodeMCU)

// Morse Code Dictionary
struct MorseCode {
    char character;
    const char* code;
};

// Morse dictionary for A-Z & 0-9
MorseCode morseTable[] = {
    {'A', ".-"},   {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},  {'E', "."}, 
    {'F', "..-."}, {'G', "--."},  {'H', "...."}, {'I', ".."},   {'J', ".---"}, 
    {'K', "-.-"},  {'L', ".-.."}, {'M', "--"},   {'N', "-."},   {'O', "---"}, 
    {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},  {'S', "..."},  {'T', "-"}, 
    {'U', "..-"},  {'V', "...-"}, {'W', ".--"},  {'X', "-..-"}, {'Y', "-.--"}, 
    {'Z', "--.."}, 

    {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
    {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."}
};

// Timing in milliseconds
const int dotDuration = 200;     // Short blink for dot
const int dashDuration = 600;    // Long blink for dash
const int symbolGap = 400;       // Time between dots/dashes
const int letterGap = 800;       // Time between letters

// Function to find Morse code for a given character
const char* getMorseCode(char inputChar) {
    inputChar = toupper(inputChar);  // Convert lowercase to uppercase
    for (int i = 0; i < sizeof(morseTable) / sizeof(morseTable[0]); i++) {
        if (morseTable[i].character == inputChar) {
            return morseTable[i].code;
        }
    }
    return "";  // Return empty string if character is not found
}

// Function to blink Morse code properly
void blinkMorse(const char* morseCode) {
    for (int i = 0; morseCode[i] != '\0'; i++) {
        digitalWrite(LED_PIN, LOW);  // **Turn LED ON for dot or dash (ACTIVE LOW)**
        
        if (morseCode[i] == '.') {
            delay(dotDuration);  // **Stay ON for dot duration**
        } else if (morseCode[i] == '-') {
            delay(dashDuration);  // **Stay ON for dash duration**
        }
        
        digitalWrite(LED_PIN, HIGH);  // **Turn LED OFF after dot/dash**
        delay(symbolGap);  // **Short pause between Morse elements**
    }
}

void setup() {
    pinMode(LED_PIN, OUTPUT);  // Set LED as output
    digitalWrite(LED_PIN, HIGH);  // **Ensure LED is OFF when the ESP starts**
    Serial.begin(115200);  // Start Serial Monitor
    Serial.println("Enter text to convert to Morse code:");
}

void loop() {
    // Only process if there is new input
    if (Serial.available() > 0) {
        String inputText = Serial.readString();  // Read user input

        Serial.print("Morse Code for: ");
        Serial.println(inputText);

        for (int i = 0; i < inputText.length(); i++) {
            char letter = inputText[i];

            if (letter == ' ') {
                delay(letterGap);  // Pause for spaces
                continue;
            }

            const char* morseCode = getMorseCode(letter);
            Serial.print(letter);
            Serial.print(" -> ");
            Serial.println(morseCode);
            
            blinkMorse(morseCode);  // Blink Morse code
            delay(letterGap);
        }

        // **Ensure LED is OFF after blinking**
        digitalWrite(LED_PIN, HIGH);

        Serial.println("Enter new text to convert:");
    }
}
