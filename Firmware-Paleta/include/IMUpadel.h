#ifndef ROTATION_H  
#define ROTATION_H

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
//#define _mpuAddress 0x69

//#define mpuAddress 0x69

extern MPU6050 MPU;

typedef struct ang{
  float x;
  float y;
}ang;

bool mpuSetConfig();
ang updateRotation();

#endif  