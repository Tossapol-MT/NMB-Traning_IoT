#include <ModbusMaster.h>


ModbusMaster node;

unsigned long timeread = 0;
unsigned int interval = 1000;


void setup()
{

  Serial.begin(115200);
  Serial1.begin(115200);
  node.begin(1, Serial1);
}


void loop()
{
  uint8_t j, result;
  int num = 6;
  uint16_t Data[num];
  
  result = node.readHoldingRegisters(0, num);
  unsigned long currentMillis = millis();
  if (currentMillis - timeread >= interval && result == node.ku8MBSuccess)
  {
    timeread = currentMillis;
    for (j = 0; j < num; j++)
    {
      Data[j] = node.getResponseBuffer(j);
    }
    Serial.println("-----------------------------");
    Serial.print("D200 : "); Serial.println(Data[0]);
    Serial.print("D201 : "); Serial.println(Data[1]);
    Serial.print("D202 : "); Serial.println(Data[2]);
    Serial.print("D203 : "); Serial.println(Data[3]);
    Serial.print("D204 : "); Serial.println(Data[4]);
    Serial.print("D205 : "); Serial.println(Data[5]);
    Serial.println("-----------------------------");
  }
}
