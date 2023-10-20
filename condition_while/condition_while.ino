#define led_connection 5
#define led_run 6

int counter = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(led_connection, OUTPUT);
  pinMode(led_run, OUTPUT);
}

void loop() 
{
  counter++;
  Serial.print("Counter : ");Serial.println(counter);
  for (int i = 0 ; i<=10;i++)
    {
      digitalWrite(led_run, HIGH);
      Serial.println("led_run");
      delay(1000);
    }
      digitalWrite(led_run,LOW);
      delay(1000);
}
