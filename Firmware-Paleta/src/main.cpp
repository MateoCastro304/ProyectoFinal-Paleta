/*#include <Arduino.h>


#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#define ledGolpe 14
const int mpuAddress = 0x68;  // Puede ser 0x68 o 0x69
MPU6050 mpu(mpuAddress);

int16_t ax, ay, az;
int16_t gx, gy, gz;

typedef struct ang{
  float x;
  float y;
}ang;

ang updateRotation()
{
  static long tiempo_prev=0;
  static float ang_x_prev,ang_y_prev;
  ang inclinacion;

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
void ISR_tiltSwitch();
void setup()
{
  Serial.begin(9600);
  Wire.begin(D1,D2);
  delay(10);


  mpu.initialize();
  pinMode(ledGolpe,OUTPUT);
  //attachInterrupt(D5,ISR_tiltSwitch,FALLING);

  Serial.println(mpu.testConnection() ? F("IMU iniciado correctamente") : F("Error al iniciar IMU"));

  // Configurar sensibilidad del acelerómetro (0 = +/- 2g, 1 = +/- 4g, 2 = +/- 8g, 3 = +/- 16g)
  mpu.setFullScaleAccelRange(0);

  // Configurar interrupción para detección de golpes (opcional)
  //mpu.setIntDataReadyEnabled(false);  // Deshabilitar interrupción de datos listos
  mpu.setInterruptMode(1);            // Interrupción cuando se detecta un golpe
  mpu.setInterruptLatch(0);           // Latch hasta que se lea el registro INT_STATUS
  mpu.setMotionDetectionThreshold(100); // Establecer umbral de detección de movimiento (ajustar según sea necesario)
  mpu.setMotionDetectionDuration(2);  // Establecer duración mínima para que se considere un golpe
}

void loop()
{
  
  // Leer las aceleraciones y velocidades angulares
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);
  ang incDisp = updateRotation();
  
  //uint8_t intStatus = mpu.getIntStatus();
  if (mpu.getIntMotionStatus()) {
    Serial.print(F("Rotacion en X:  "));
    Serial.print(incDisp.x);
    Serial.print(F("\t Rotacion en Y: "));
    Serial.println(incDisp.y);
    digitalWrite(ledGolpe, HIGH); // Encender LED
    delay(1000);             // Mantener encendido por 100 ms
    digitalWrite(ledGolpe, LOW);  // Apagar LED

    mpu.getIntStatus();
  }


  static const int interval=10;
  static int previousMillis=0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Guardar el tiempo actual
    previousMillis = currentMillis;
    // Serial.print(F("Rotacion en X:  "));
    // Serial.print(incDisp.x);
    // Serial.print(F("\t Rotacion en Y: "));
    // Serial.println(incDisp.y);
  }
  //delay(10);
}
void ISR_tiltSwitch(){

}*/

