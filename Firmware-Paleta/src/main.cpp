#include <Arduino.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "HeaderPaleta.h"
#include "IMUpadel.h"

MPU6050 MPU(0x68);
Adafruit_BMP280 BMP; // I2C
void setup()
{
  
  pinMode(analogInPin, INPUT);
  pinMode(mosfetSupplyPin, OUTPUT);
  pinMode(ledGolpe, OUTPUT);
  
  digitalWrite(mosfetSupplyPin, HIGH);
  
  Serial.begin(9600);
  Serial.println();
  
  delay(500);

  Wire.begin(PIN_SDA, PIN_SCL);
  Wire.setClock(400000);

  delay(1000);
  
  // MPU.initialize();
  // while (!MPU.testConnection())
  // {
  //   Wire.begin(PIN_SDA, PIN_SCL);
  //   Serial.println("Error al iniciar IMU");
  //   Serial.println("intentando inicializar nuevamente...");
  //   MPU.initialize();
  //   delay(2000);
  // }
  
  if (mpuSetConfig())
  {
    Serial.println("MPU Iniciado correctamente");
  }else{
    while (!mpuSetConfig())
    {
      Serial.println("Error al iniciar MPU");
      Serial.println("intentando inicializar nuevamente...");

      Wire.begin(PIN_SDA, PIN_SCL);
      Wire.setClock(400000);
      MPU.initialize();
      delay(2000);
    }
    Serial.println("MPU Iniciado");
  }

  if (!BMP.begin(BMP280_ADDRESS_ALT))
  {
    Serial.println("No se pudo iniciar BMP");
  }else{
    Serial.println("BMP Iniciado correctamente");
  }

  BMP.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop()
{
  ang incDisp = updateRotation();
  if (MPU.getIntMotionStatus()) {
    
    Serial.print(F("Rotacion en X:  "));
    Serial.print(incDisp.x);
    Serial.print(F("\t Rotacion en Y: "));
    Serial.println(incDisp.y);

    Serial.print(F("Approx altitude = "));
    Serial.print(BMP.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    digitalWrite(ledGolpe, HIGH); // Encender LED
    delay(1000);             // Mantener encendido por 100 ms
    digitalWrite(ledGolpe, LOW);  // Apagar LED

    MPU.getIntStatus();
  }
  static const int interval=10000;
  static int previousMillis=0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Guardar el tiempo actual
    previousMillis = currentMillis;
    Serial.println(MPU.testConnection() ? "IMU funcionando" : "Error IMU");
    Serial.print(F("Pressure = "));
    Serial.print(BMP.readPressure());
    Serial.println(" Pa");
    // Serial.print(incDisp.x);
    // Serial.print(F("\t Rotacion en Y: "));
    // Serial.println(incDisp.y);
  }
}


