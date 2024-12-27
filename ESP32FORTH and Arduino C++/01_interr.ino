// program for simple interrupt possibility test
// case sensitive code
#define buttonPin 33
#define LEDPin 32

void IRAM_ATTR menLED(){
    digitalWrite(LEDPin, !digitalRead(LEDPin));
    Serial.println("Here one interrupt!");
}

void setup(){
    pinMode(LEDPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    attachInterrupt(buttonPin, menLED, FALLING);
    Serial.begin(115200);
    digitalWrite(LEDPin, HIGH);
}

void loop(){
  Serial.println("ESP32 goes");
  Serial.print("Input 32: ");
  Serial.println(digitalRead(LEDPin));
  delay(1000);

}
