#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
<<<<<<< HEAD
#define lcdAdd 0x27

const uint8_t batValuePin = A0, mosfetSupplyPin = D7;  // ESP8266 Analog Pin ADC0 = A0
LiquidCrystal_I2C lcd(lcdAdd,16,2);

void lcdValueBattery(const uint8_t analogPinBat, float batVolt){
=======

// Informacion sobre puertos GPIO ESP8266
/* https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/ */

const byte mosfetSupplyPin = 13;
const byte ledTest = 14;
const byte analogInPin = 17;  // ESP8266 Analog Pin ADC0 = 17

#define lcdAdd 0x27
LiquidCrystal_I2C lcd(lcdAdd,16,2);

void lcdShowValueBattery(const uint8_t analogPinBat, float batVolt){
>>>>>>> c78785d48cff0674adc30242695901b2c92d3614
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("[ADC] = ");
  lcd.print(analogRead(analogPinBat));
  lcd.setCursor(0,1);
  lcd.print("[V] = ");
  lcd.print(batVolt);
}

void setup() {
  pinMode(analogInPin,INPUT);
  pinMode(ledTest, OUTPUT);        // Configura el pin del LED como salida
  pinMode(mosfetSupplyPin, OUTPUT);

  digitalWrite(mosfetSupplyPin,HIGH);
  
  Serial.begin(9600);

  delay(10);

<<<<<<< HEAD
  pinMode(batValuePin,INPUT);     // Configura el pin del LED como salida
  pinMode(mosfetSupplyPin, OUTPUT);

  digitalWrite(mosfetSupplyPin,HIGH);

  Wire.begin(D1,D2);
  lcd.init();

=======
  Wire.begin(SDA,SCL); //D1 = SCL, D2 = SDA

  lcd.init();
>>>>>>> c78785d48cff0674adc30242695901b2c92d3614
  delay(10);
  lcd.backlight();
  lcd.clear();
}

void loop() {
  // read the analog in value
<<<<<<< HEAD
    
  static const int interval=5000;
  static int previousMillis=0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    
    float batCharge = ((float) analogRead(batValuePin) * 4.84)/1023.0;
    lcdValueBattery(batValuePin, batCharge);

    previousMillis = currentMillis;
=======
  static const int interval[2]={500,8000};
  static int previousMillis[2] = {0,0};
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis[0] >= interval[0]) {

    float batCharge = ((float) analogRead(analogInPin) * 4.84)/1023.0;
    lcdShowValueBattery(analogInPin, batCharge);
    digitalWrite(ledTest,!digitalRead(ledTest));

    previousMillis[0] = currentMillis;
  }
  if (currentMillis - previousMillis[1] >= interval[1])
  {
    previousMillis[1] = currentMillis;
    Serial.println("Sistema apagado");
    digitalWrite(mosfetSupplyPin, LOW);
>>>>>>> c78785d48cff0674adc30242695901b2c92d3614
  }
}
