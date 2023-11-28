#include <Arduino.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

#include "comWemosToNode.h"

#define PIN_MOSFET 13   //D7
#define PIN_BAT 17      // ESP8266 Analog Pin ADC0 = 17
#define PIN_LED0 16         //D0
#define PIN_LED1 14         //D5

#ifndef STASSID
    #define STASSID "MateoA52"
    #define STAPSK  "mateo033121"
#endif

Adafruit_BMP280 BMP; // I2C
dataWemos daToSend;
void SerialValueBattery(){
  //Serial.clear();
  //Serial.setCursor(0,0);
  int adcValue = analogRead(PIN_BAT);
  float batCharge = ((float) adcValue * 5.1)/1023.0;
  Serial.println();
  Serial.print("[ADC] = ");
  Serial.println(adcValue);
  //Serial.setCursor(0,1);
  Serial.print("[V] = ");
  daToSend.bat_ok = (adcValue>600)? true:false;
  Serial.println(batCharge);
  Serial.println();
}

void setup()
{
  pinMode(PIN_BAT, INPUT);
  pinMode(PIN_MOSFET, OUTPUT);

  pinMode(PIN_LED0, OUTPUT);
  pinMode(PIN_LED1,OUTPUT);
  
  digitalWrite(PIN_MOSFET, HIGH);
  digitalWrite(PIN_LED1, HIGH);

  Serial.begin(9600);
  Serial.println();
  // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    Serial.println(WiFi.macAddress());
    
    /*WiFi.mode(WIFI_STA);
    WiFi.begin(STASSID, STAPSK);
    Serial.print("\nConnecting to ");
    Serial.println(STASSID);

    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(500);
    }
    Serial.println();
    Serial.print("connected, address=");
    Serial.println(WiFi.localIP());*/
  delay(500);
  if (!set_espnow()){
    digitalWrite(PIN_LED0,HIGH);
    delay(500);
    digitalWrite(PIN_LED0,LOW);
  }
  else{
    digitalWrite(PIN_LED0,HIGH);
  }

  Wire.begin(PIN_SDA, PIN_SCL);
  Wire.setClock(400000);

  delay(1000);
  
  if (mpu_set_config())
  {
    Serial.println("MPU Iniciado correctamente");
  }else{
    Serial.println("Error al iniciar MPU");
  }

  // if (!BMP.begin(BMP280_ADDRESS_ALT))
  // {
  //   Serial.println("No se pudo iniciar BMP");
  // }else{
  //   Serial.println("BMP Iniciado correctamente");
  //   BMP.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
  //                   Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
  //                   Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
  //                   Adafruit_BMP280::FILTER_X16,      /* Filtering. */
  //                   Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  // }

}

void loop()
{
  ang incDisp = update_rotation();
  if (golpe_detectado()) {
    
    Serial.print(F("Rotacion en X:  "));
    Serial.print(incDisp.x);
    Serial.print(F("\t Rotacion en Y: "));
    Serial.println(incDisp.y);

    daToSend.posicion_golpe_x = incDisp.x;
    daToSend.posicion_golpe_y = incDisp.y;
    //daToSend.altitud = BMP.readAltitude(1013.25);

    //Serial.print(F("Approx altitude = "));
    //Serial.print(daToSend.altitud); /* Adjusted to local forecast! */
    //Serial.println(" m");
    
    daToSend.cant_golpes++;
    send_mac_node((uint8_t *) &daToSend, sizeof(daToSend));
    digitalWrite(PIN_LED0, HIGH); // Encender LED
    delay(1000);             // Mantener encendido por 100 ms
    digitalWrite(PIN_LED0, LOW);  // Apagar LED

  
  }
  static const int interval=4000;
  static int previousMillis=0;
  unsigned long currentMillis = millis();
  /*if (currentMillis - previousMillis >= interval) {
    // Guardar el tiempo actual
    previousMillis = currentMillis;
    if (get_estado_mpu())
    {
      daToSend.error = 0;
      Serial.println("IMU funcionando");
    }
    else
    {
      daToSend.error = 1;
      Serial.println("Error IMU");
    }

    Serial.print(F("Pressure = "));
    Serial.println(" Pa");
    //SerialValueBattery();
    // Serial.print(incDisp.x);
    // Serial.print(F("\t Rotacion en Y: "));
    // Serial.println(incDisp.y);
  }*/
}


