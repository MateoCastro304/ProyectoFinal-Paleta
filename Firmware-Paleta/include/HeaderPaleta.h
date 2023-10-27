#ifndef HEADER_H  
#define HEADER_H

#include <Arduino.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "IMUPadel.h"
#include "EspNow-Paddel.h"

#define PIN_MOSFET 13  //D7
#define PIN_BAT 17      // ESP8266 Analog Pin ADC0 = 17
#define PIN_LED0 16         //D0
#define PIN_LED1 14         //D5
#define PIN_SCL 5           //D1
#define PIN_SDA 4           //D2
#endif