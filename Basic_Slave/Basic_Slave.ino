#include "ModbusRtu.h"


Modbus slave(1, Serial1, 0);

unsigned long timeread = 0;
unsigned int interval = 1000;

uint8_t state=0 ;
const int num = 6;
uint16_t Data[num];


void setup()
{

  Serial.begin(115200);
  Serial1.begin(115200);
  slave.start();
}


void loop()
{
  state = slave.poll(Data,num);
  unsigned long currentMillis = millis();
  if (currentMillis - timeread >= interval && state >= 7 )
  {
    timeread = currentMillis;
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
