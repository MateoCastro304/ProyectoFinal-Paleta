#include "IMUPadel.h"

bool mpuSetConfig(){
    mpu.initialize();
    //Serial.println(mpu.testConnection() ? "IMU iniciado correctamente" : "Error al iniciar IMU");
    if (!mpu.testConnection()){
        return false;
    }
    
    // Configurar sensibilidad del acelerómetro (0 = +/- 2g, 1 = +/- 4g, 2 = +/- 8g, 3 = +/- 16g)
    mpu.setFullScaleAccelRange(0);

    // Configurar interrupción para detección de golpes (opcional)
    //mpu.setIntDataReadyEnabled(false);  // Deshabilitar interrupción de datos listos
    mpu.setInterruptMode(1);            // Interrupción cuando se detecta un golpe
    mpu.setInterruptLatch(0);           // Latch hasta que se lea el registro INT_STATUS
    mpu.setMotionDetectionThreshold(100); // Establecer umbral de detección de movimiento (ajustar según sea necesario)
    mpu.setMotionDetectionDuration(2);  // Establecer duración mínima para que se considere un golpe

    return mpu.testConnection();
}
ang updateRotation()
{
    static int16_t ax, ay, az;
    static int16_t gx, gy, gz;

    static long tiempo_prev=0;
    static float ang_x_prev=0,ang_y_prev=0;

    ang inclinacion;
    // Leer las aceleraciones y velocidades angulares
    mpu.getAcceleration(&ax, &ay, &az);
    mpu.getRotation(&gx, &gy, &gz);

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