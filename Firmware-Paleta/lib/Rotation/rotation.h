#ifndef ROTATION_H  
#define ROTATION_H

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#define _mpuAddress 0x69

typedef struct ang{
  float x;
  float y;
}ang;

ang updateRotation();

#endif  