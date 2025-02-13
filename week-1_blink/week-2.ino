PWM_Frequency
PWM_Channel
PWM_Resolution

Input PIN
Output pin
Variable for storing light level value

void setup() {
    Serial.begin(115200);
    ledcSetup(PWM_Channel, PWM_Frequency, PWM_Resolution);
    ledcAttachPin(GPIOPIN, PWM_Channel);
}

void loop() {
    Read in value of light level from LDR
    Serial.print("Raw value =");
    Serial.println(light levl value);
    ledcWrite(PWM_Channel, val);
    delay(1000);
}
