#include <Arduino.h>
#include "I2CScanner.h"
#include <Wire.h>
#include <Adafruit_BMP280.h>
#define SDA_PIN D2
#define SCL_PIN D1
#define PIN_MOSFET 13  //D7

I2CScanner scanner;
Adafruit_BMP280 BMP; // I2C
//if you use ESP8266-01 with not default SDA and SCL pins, define these 2 lines, else delete them	

void setup() 
{	
	//uncomment the next line if you use custom sda and scl pins for example with ESP8266-01 (sda = 4, scl = 5)
	pinMode(PIN_MOSFET,OUTPUT);
	pinMode(D5,OUTPUT);
	delay(10);
	digitalWrite(PIN_MOSFET,HIGH);
	Wire.begin(SDA_PIN, SCL_PIN);
	
	Serial.begin(9600);
	while (!Serial) {};
	if (!BMP.begin(BMP280_ADDRESS_ALT))
  	{
    Serial.println("No se pudo iniciar BMP");
	digitalWrite(D5,HIGH);
  	}else{
    Serial.println("BMP Iniciado correctamente");
	digitalWrite(D5,LOW);
  	}

  	BMP.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
	//scanner.Init();
}

void loop() 
{
	//scanner.Scan();
	delay(5000);
}
/*#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define SDA_PIN D1
#define SCL_PIN D2

#define PIN_MOSFET 13  //D7

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	// initialize the LCD
	

	Wire.begin(SDA_PIN, SCL_PIN);
	lcd.begin(16,2);  // sda=0, scl=2
  	delay(10);
	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("Hello, world!");
}

void loop()
{
/*lcd.setCursor(0,0);
  lcd.print(1);
  lcd.setCursor(1,0);
  lcd.print(1);
  delay(500);
  lcd.clear();
  delay(500);
}*/