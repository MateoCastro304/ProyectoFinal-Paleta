#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define lcdAdd 0x27
const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
LiquidCrystal_I2C lcd(lcdAdd,16,2);

void setup() {
  pinMode(A0,INPUT);
  pinMode(D5,OUTPUT);

  digitalWrite(D5,HIGH);
  Wire.begin(D1,D2);
  lcd.init();
  delay(10);
  lcd.backlight();
  lcd.clear();

  // initialize serial communication at 115200
  Serial.begin(9600);
}

void loop() {
  // read the analog in value
  
  
  static const int interval=5000;
  static int previousMillis=0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Guardar el tiempo actual
    lcd.clear();
    
    int analogValue = analogRead(analogInPin);
  
    float BatRead = ( (float)analogValue * 4.84)/1023.0;
    // print the readings in the Serial Monitor
    lcd.setCursor(0,0);
    lcd.print("Analog= ");
    lcd.print(analogValue);
    lcd.setCursor(0,1);
    lcd.print("Bat= ");
    lcd.print(BatRead);

    previousMillis = currentMillis;
  }
}