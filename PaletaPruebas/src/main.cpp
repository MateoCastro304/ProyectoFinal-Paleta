#include <Arduino.h>

#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

#define PIN_MOSFET 13  //D7
#define PIN_BAT 17      // ESP8266 Analog Pin ADC0 = 17
#define PIN_LED0 16         //D0
#define PIN_LED1 14         //D5
#define PIN_SCL 5           //D1
#define PIN_SDA 4           //D2

MPU6050 MPU(0x68);
//Adafruit_BMP280 BMP;

typedef struct ang{
    float x;
    float y;
}ang;

ang updateRotation();

void setup() {
    pinMode(PIN_BAT, INPUT);
    pinMode(PIN_MOSFET, OUTPUT);

    pinMode(PIN_LED0, OUTPUT);
    pinMode(PIN_LED1,OUTPUT);
  
    digitalWrite(PIN_MOSFET, HIGH);
    digitalWrite(PIN_LED1, HIGH);

    Serial.begin(9600);
    Serial.println();

    Wire.begin(PIN_SDA, PIN_SCL);
    Wire.setClock(400000);

    MPU.initialize();
    delay(2000);
    Serial.println(MPU.testConnection() ? "MPU6050 iniciado correctamente" : "Error al iniciar MPU6050");
    
    // Configurar sensibilidad del acelerómetro (0 = +/- 2g, 1 = +/- 4g, 2 = +/- 8g, 3 = +/- 16g)
    MPU.setFullScaleAccelRange(0);

    // Configurar interrupción para detección de golpes (opcional)
    MPU.setIntDataReadyEnabled(false);  // Deshabilitar interrupción de datos listos
    MPU.setInterruptMode(1);            // Interrupción cuando se detecta un golpe
    MPU.setInterruptLatch(0);           // Latch hasta que se lea el registro INT_STATUS
    MPU.setMotionDetectionThreshold(100); // Establecer umbral de detección de movimiento (ajustar según sea necesario)
    MPU.setMotionDetectionDuration(2);  // Establecer duración mínima para que se considere un golpe
}

void loop() {
    static int golpes = 0;

  ang incDisp = updateRotation();
  if (MPU.getIntMotionStatus()) {
    
    Serial.print("Ang X: ");
    Serial.print(incDisp.x);
    Serial.print("  Ang y: ");
    Serial.println(incDisp.y);
    Serial.println(++golpes);

    digitalWrite(PIN_LED0, HIGH); // Encender LED
    delay(1000);             // Mantener encendido por 100 ms
    digitalWrite(PIN_LED0, LOW);  // Apagar LED

    MPU.getIntStatus();
  }
}

ang updateRotation()
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