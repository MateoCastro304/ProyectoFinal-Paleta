#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Informacion sobre puertos GPIO ESP8266
/* https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/ */

const byte mosfetSupplyPin = 13;
const byte ledTest = 14;
const byte analogInPin = 17;  // ESP8266 Analog Pin ADC0 = 17

#define lcdAdd 0x27
//LiquidCrystal_I2C lcd(lcdAdd,16,2);

void lcdShowValueBattery(const uint8_t analogPinBat, float batVolt){
  //Serial.clear();
  //Serial.setCursor(0,0);
  Serial.print("[ADC] = ");
  Serial.println(analogRead(analogPinBat));
  //Serial.setCursor(0,1);
  Serial.print("[V] = ");
  Serial.println(batVolt);
  Serial.println();
}

void setup() {
  pinMode(analogInPin,INPUT);
  pinMode(ledTest, OUTPUT);        // Configura el pin del LED como salida
  pinMode(mosfetSupplyPin, OUTPUT);

  digitalWrite(mosfetSupplyPin,HIGH);
  
  Serial.begin(9600);

  delay(10);

  //Wire.begin(SDA,SCL); //D1 = SCL, D2 = SDA
  //lcd.init();
  delay(10);
  //lcd.backlight();
  //lcd.clear();
}

void loop() {
  // read the analog in value
  static const int interval[2]={200,8000};
  static int previousMillis[2] = {0,0};
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis[0] >= interval[0]) {

    float batCharge = ((float) analogRead(analogInPin) * 5.1)/1023.0;
    lcdShowValueBattery(analogInPin, batCharge);
    digitalWrite(ledTest,!digitalRead(ledTest));

    previousMillis[0] = currentMillis;
  }
  if (currentMillis - previousMillis[1] >= interval[1])
  {
    previousMillis[1] = currentMillis;
    Serial.println("Sistema apagado");
    digitalWrite(mosfetSupplyPin, LOW);
  }
}
