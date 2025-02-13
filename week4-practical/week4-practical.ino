/***************************************************
    Adafruit MQTT Library ESP8266 Example

    Must use ESP8266 Arduino from:
        https://github.com/esp8266/Arduino
    Works great with Adafruit's Huzzah ESP board:
    ----> https://www.adafruit.com/product/2471
    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    Written by Tony DiCola for Adafruit Industries.
    MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

// WiFi parameters
#define WLAN_SSID       "yourSSID"
#define WLAN_PASS       "yourPASSWORD"

// MQTT broker
#define MQTT_SERVER     "io.adafruit.com"
#define MQTT_SERVERPORT 1883                   // use 8883 for SSL
#define MQTT_USERNAME   "yourMQTTusername"
#define MQTT_KEY        "yourMQTTpassword"

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiClientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY);

// Setup a feed called 'test' for publishing.
Adafruit_MQTT_Publish test = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/feeds/test");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USERNAME "/feeds/onoff");

void MQTT_connect();

void setup() {
    Serial.begin(115200);
    delay(10);

    // Connect to WiFi access point.
    Serial.println(); Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);

    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.println("WiFi connected");
    Serial.println("IP address: "); Serial.println(WiFi.localIP());

    // Setup MQTT subscription for onoff feed.
    mqtt.subscribe(&onoff);
}

void loop() {
    // Ensure the connection to the MQTT server is alive (this will make the first
    // connection and automatically reconnect when disconnected).  See the MQTT_connect
    // function definition further below.
    MQTT_connect();

    // this is our 'wait for incoming subscription packets' busy subloop
    // try to spend your time here

    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(5000))) {
        if (subscription == &onoff) {
            Serial.print(F("Got: "));
            Serial.println((char *)onoff.lastread);
        }
    }

    // Now we can publish stuff!
    Serial.print(F("\nSending test value "));
    Serial.print(millis());
    Serial.print("...");
    if (! test.publish(millis())) {
        Serial.println(F("Failed"));
    } else {
        Serial.println(F("OK!"));
    }

    // ping the server to keep the mqtt connection alive
    // NOT required if you are publishing once every KEEPALIVE seconds
    if(! mqtt.ping()) {
        mqtt.disconnect();
    }

    delay(10000);  // wait 10 seconds
}

void MQTT_connect() {
    int8_t ret;

    // Stop if already connected.
    if (mqtt.connected()) {
        return;
    }

    Serial.print("Connecting to MQTT... ");

    uint8_t retries = 3;
    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
             Serial.println(mqtt.connectErrorString(ret));
             Serial.println("Retrying MQTT connection in 5 seconds...");
             mqtt.disconnect();
             delay(5000);  // wait 5 seconds
             retries--;
             if (retries == 0) {
                 // basically die and wait for WDT to reset me
                 while (1);
             }
    }
    Serial.println("MQTT Connected!");
}
