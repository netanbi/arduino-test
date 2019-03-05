
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(7, 8, 9, 10, 11, 13);
float sensorValue = 0; // The sensor value
int tempValue;
float sensorMin = 80;  // Minimum sensor value
float sensorMax = 716;// Maximum sensor value
float outMin = 7;
float outMax = 150;

int x;


void setup()
{
  Serial.begin(115200);
  lcd.begin(20, 4);
}
float fmap (float sensorValue, float sensorMin, float sensorMax, float outMin, float outMax)
    {
  return (sensorValue - sensorMin) * (outMax - outMin) / (sensorMax - sensorMin) + outMin;
     }
void loop() {

  sensorValue = analogRead(A7); 
 
  sensorValue = fmap (sensorValue, sensorMin, sensorMax, 0, 150); 
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Flow: ");
  if (sensorValue >= 0)
  {
    lcd.print(sensorValue);
  }
  else
  { 
    lcd.print("0");  
  }
  lcd.print("L/min");
  x = analogRead(A7);
  Serial.println(x);
  tempValue = analogRead(A4);
  lcd.setCursor(0, 2);  
  lcd.print("Temp: ");
  lcd.print(tempValue);
  lcd.print(" ");
  lcd.print(char(223));
  lcd.print("C");
  delay(2000);

}

