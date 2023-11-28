#include "IMUSensors.h"
//MPU6050 MPU(0x68);
MPU6050 MPU(0x68);
bool mpu_set_config(){
    MPU.initialize();
    // Configurar sensibilidad del acelerómetro (0 = +/- 2g, 1 = +/- 4g, 2 = +/- 8g, 3 = +/- 16g)
    if (!MPU.testConnection()){
        Serial.println("Error al iniciar");
        return false;
    }else
    {
        MPU.setFullScaleAccelRange(0);
        MPU.setFullScaleGyroRange(0);
        Serial.println("MPU Seteado");
        mpu_set_interrupt();
        Serial.println("Interrupciones Seteadas");
        set_offsets();
        Serial.println("OffSets Configurados");
        return true;
    }
   
    
}
bool mpu_set_interrupt(){
    // Configurar interrupción para detección de golpes (opcional)
    bool test = false;
    MPU.setIntDataReadyEnabled(false);  // Deshabilitar interrupción de datos listos
    MPU.setInterruptMode(1);            // Interrupción cuando se detecta un golpe
    MPU.setInterruptLatch(0);           // Latch hasta que se lea el registro INT_STATUS
    MPU.setMotionDetectionThreshold(100); // Establecer umbral de detección de movimiento (ajustar según sea necesario)
    MPU.setMotionDetectionDuration(2);  // Establecer duración mínima para que se considere un golpe
    test = true;
    return test;
}
ang update_rotation()
{
    static int16_t ax, ay, az;
    static int16_t gx, gy, gz;

    static long tiempo_prev=0;
    static float ang_x_prev=0,ang_y_prev=0;

    ang inclinacion;
    // Leer las aceleraciones y velocidades angulares
    MPU.getAcceleration(&ax, &ay, &az);
    MPU.getRotation(&gx, &gy, &gz);

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
bool golpe_detectado(){
    if (MPU.getIntMotionStatus()) {
        MPU.getIntStatus();
        return true;
    }
    else return false;
}
bool get_estado_mpu(){
    return MPU.testConnection();
}
void set_offsets(){
    /*
Sensor readings with offsets:   -1      1       16380   -1      0       -1
                Your offsets:   -1250   -1713   1028    43      7       -19
Data is printed as:             acelX   acelY   acelZ   giroX   giroY   giroZ
Check that your sensor readings are close to 0 0 16384 0 0 0
If calibration was succesful write down your offsets so you can set
them in your projects using something similar to mpu.setXAccelOffset(youroffset)
*/
    MPU.setXAccelOffset(-1250);
    MPU.setYAccelOffset(1713);
    MPU.setZAccelOffset(1028);

    MPU.setXGyroOffset(43);
    MPU.setYGyroOffset(7);
    MPU.setZGyroOffset(19);
}