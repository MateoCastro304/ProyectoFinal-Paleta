#include "rotation.h"

ang updateRotation()
{
    MPU6050 _mpu(_mpuAddress);
    
    static int16_t ax, ay, az;
    static int16_t gx, gy, gz;

    static long tiempo_prev=0;
    static float ang_x_prev=0,ang_y_prev=0;

    ang inclinacion;
    // Leer las aceleraciones y velocidades angulares
    _mpu.getAcceleration(&ax, &ay, &az);
    _mpu.getRotation(&gx, &gy, &gz);

    float dt = (millis() - tiempo_prev) / 1000.0;
    tiempo_prev = millis();

    //Calcular los ángulos con acelerometro
    float accel_ang_x = atan(ay / sqrt(pow(ax, 2) + pow(az, 2)))*(180.0 / 3.14);
    float accel_ang_y = atan(-ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);

    //Calcular angulo de rotación con giroscopio y filtro complementario
    inclinacion.x = 0.98*(ang_x_prev + (gx / 131)*dt) + 0.02*accel_ang_x;
    inclinacion.y = 0.98*(ang_y_prev + (gy / 131)*dt) + 0.02*accel_ang_y;

    ang_x_prev = inclinacion.x;
    ang_y_prev = inclinacion.y;

    return inclinacion;
}