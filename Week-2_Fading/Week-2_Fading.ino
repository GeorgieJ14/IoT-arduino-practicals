int ledPin = 9; // LED connected to digital pin 9
int brightness = 0; // how bright the LED is
int fadeAmount = 5; // how many points to fade the LED by

void setup() {
    pinMode(ledPin, OUTPUT);
}

void loop() {
    // set the brightness of pin 9:
    analogWrite(ledPin, brightness);

    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    if (brightness == 0 || brightness == 255) {
        fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
}
