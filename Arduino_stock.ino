#include <SoftPWM.h>
#include <SoftPWM_timer.h>
#include <LiquidCrystal.h>

String GPUfan;  //Fan speed
String GPUtemp;  //GPU temp
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);		//Check your lcd to see what pins it uses, my OSEPP one uses these pins

int sensorPin = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  SoftPWMBegin(SOFTPWM_NORMAL); 
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    GPUtemp = Serial.readStringUntil('*');    
    GPUfan = Serial.parseFloat();
  }
  lcd.print("GPUTemp:" + GPUtemp);
  lcd.setCursor(0, 1);        //Move onto the second line
  lcd.print("GPUFanspeed:");
  lcd.print(GPUfan);             
  delay(2500);
  lcd.clear();                //Clear the lcd    

  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 100;
  int MappedTemperatureC = map(temperatureC, 0, 30, 0, 255);
  Serial.println(MappedTemperatureC);
  SoftPWMSet(52, MappedTemperatureC);
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.print(temperatureC);
  delay(5000);
  lcd.clear();
}
