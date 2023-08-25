#ifndef HEADER_H  
#define HEADER_H

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "rotation.h"

#define ledGolpe 14

#define mpuAddress 0x69
MPU6050 mpu(mpuAddress);


#endif