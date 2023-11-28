#ifndef ROTATION_H  
#define ROTATION_H

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
//#define _mpuAddress 0x69

//#define mpuAddress 0x69
#define PIN_SCL 5           //D1
#define PIN_SDA 4           //D2

typedef struct ang{
  float x;
  float y;
}ang;

bool mpu_set_config();
ang update_rotation();
void set_offsets();
bool get_estado_mpu();
bool golpe_detectado();
bool mpu_set_interrupt();
#endif  