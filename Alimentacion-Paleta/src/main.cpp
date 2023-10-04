#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#define lcdAdd 0x27

const uint8_t batValuePin = A0, mosfetSupplyPin = D7;  // ESP8266 Analog Pin ADC0 = A0
LiquidCrystal_I2C lcd(lcdAdd,16,2);

void lcdValueBattery(const uint8_t analogPinBat, float batVolt){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("[ADC] = ");
  lcd.print(analogRead(analogPinBat));
  lcd.setCursor(0,1);
  lcd.print("[V] = ");
  lcd.print(batVolt);
}

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(batValuePin,INPUT);     // Configura el pin del LED como salida
  pinMode(mosfetSupplyPin, OUTPUT);

  digitalWrite(mosfetSupplyPin,HIGH);

  Wire.begin(D1,D2);
  lcd.init();

  delay(10);
  lcd.backlight();
  lcd.clear();
}

void loop() {
  // read the analog in value
    
  static const int interval=5000;
  static int previousMillis=0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    
    float batCharge = ((float) analogRead(batValuePin) * 4.84)/1023.0;
    lcdValueBattery(batValuePin, batCharge);

    previousMillis = currentMillis;
  }
}
