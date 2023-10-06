#include <Arduino.h>
#include "HeaderPaleta.h"

void setup()
{
  Serial.begin(9600);
  Wire.begin(D1,D2);
  delay(10);


  mpu.initialize();
  pinMode(ledGolpe,OUTPUT);

  mpuSetConfig();
  Serial.println(mpu.testConnection() ? "IMU iniciado correctamente" : "Error al iniciar IMU");

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
  ang incDisp = updateRotation();
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
}


