#include <Arduino.h>
//#define lcdAdd 0x27
//const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
//LiquidCrystal_I2C lcd(lcdAdd,16,2);

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(A0,INPUT);
  pinMode(D6, OUTPUT);          // Configura el pin del LED como salida
  pinMode(D7, OUTPUT);

  digitalWrite(D6,HIGH);

  //Wire.begin(D1,D2);
  //lcd.init();
  // delay(10);
  // lcd.backlight();
  // lcd.clear();

  // initialize serial communication at 115200
  
}

void loop() {
  // read the analog in value
  /*static const int interval=5000;
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
  }*/
  digitalWrite(D7,!digitalRead(D7));
  delay(200);
}
