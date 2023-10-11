#ifndef ROTATION_H  
#define ROTATION_H

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
//#define _mpuAddress 0x69
#define ledGolpe 14
#define mpuAddress 0x69

MPU6050 mpu(mpuAddress);

typedef struct ang{
  float x;
  float y;
}ang;

bool mpuSetConfig();
ang updateRotation();

#endif  