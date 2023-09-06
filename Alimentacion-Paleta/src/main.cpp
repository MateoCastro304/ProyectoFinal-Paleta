#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Informacion sobre puertos GPIO ESP8266
/* https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/ */

const byte STAT = 13;
const byte ledTest = 14;
const int analogInPin = 17;  // ESP8266 Analog Pin ADC0 = 17

#define lcdAdd 0x27
LiquidCrystal_I2C lcd(lcdAdd,16,2);

void setup() {
  pinMode(analogInPin,INPUT);
  pinMode(ledTest, OUTPUT);        // Configura el pin del LED como salida
  pinMode(STAT, OUTPUT);

  digitalWrite(STAT,HIGH);
  
  Serial.begin(9600);
  delay(10);

  Wire.begin(SDA,SCL);

  lcd.init();
  delay(10);
  lcd.backlight();
  lcd.clear();
}

void loop() {
  // read the analog in value
  static const int interval[2]={500,8000};
  static int previousMillis[2] = {0,0};
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis[0] >= interval[0]) {
    // Guardar el tiempo actual
    // lcd.clear();
    // int analogValue = analogRead(analogInPin);
    // float BatRead = ( (float)analogValue * 4.84)/1023.0;
    // // print the readings in the Serial Monitor
    // lcd.setCursor(0,0);
    // lcd.print("Analog= ");
    // lcd.print(analogValue);
    // lcd.setCursor(0,1);
    // lcd.print("Bat= ");
    // lcd.print(BatRead);
    digitalWrite(ledTest,!digitalRead(ledTest));

    previousMillis[0] = currentMillis;
  }
  if (currentMillis - previousMillis[1] >= interval[1])
  {
    previousMillis[1] = currentMillis;
    Serial.println("Sistema apagado");
    digitalWrite(STAT, LOW);
  }
}
