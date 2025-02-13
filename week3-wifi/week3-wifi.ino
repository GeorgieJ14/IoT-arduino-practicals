//COMP6031 Expt 4
#include "WiFi.h"

const char* ssid = "Brookes WiFi";
const char* password = "HelloBrookes";

void setup() {

    Serial.begin(115200);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(5000);
        Serial.println("Connecting to WiFi..");
    }
    delay(5000);
    Serial.println("Connected to the WiFi network");
}

void loop() {

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC address: ");
    Serial.println(WiFi.macAddress());
    delay(5000);
} 
