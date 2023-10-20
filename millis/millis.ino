
unsigned long previousMillis = 0;
const long interval = 1000;

#define led_run 6
int ledState = LOW;   

void setup() {
  Serial.begin(115200);
  pinMode(led_run, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    Serial.print("perviousMillis :");
    Serial.println(previousMillis);
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
   digitalWrite(led_run, ledState);
  }  
}
