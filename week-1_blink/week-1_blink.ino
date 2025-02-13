int pinNumber = 13;


void setup() {
    pinMode(pinNumber, OUTPUT);
}

void loop() {
    digitalWrite(pinNumber, HIGH);
    delay(1000);
    digitalWrite(pinNumber, LOW);
    delay(1000);
}
