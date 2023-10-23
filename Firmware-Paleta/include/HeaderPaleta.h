#ifndef HEADER_H  
#define HEADER_H

#include <Arduino.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "IMUPadel.h"
#include "EspNow-Paddel.h"

#define mosfetSupplyPin 13  //D7
#define analogInPin 17      // ESP8266 Analog Pin ADC0 = 17
#define ledGolpe 16         //D0
#define ledState 14         //D5
#define PIN_SCL 5           //D1
#define PIN_SDA 4           //D2
#endif