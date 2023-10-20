#include <esp_task_wdt.h>
#define WDT_TIMEOUT 20
void setup() {
  Serial.begin(115200);
  esp_task_wdt_init(WDT_TIMEOUT, true);
  esp_task_wdt_add(NULL);
  esp_task_wdt_reset();
  delay(1000);
  Serial.println("ESP_RESET");
  delay(1000);
}

void loop() {
  Serial.println("ESP_RUN");
  for(int i=0;i<=25;i++)
  {
    Serial.print("i :");Serial.println(i);
    delay(1000);
  }
  esp_task_wdt_reset();
  delay(1000);
}
