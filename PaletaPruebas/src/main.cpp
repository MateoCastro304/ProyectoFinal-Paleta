/*
API ESPNOW DOC: https://www.espressif.com/sites/default/files/documentation/2c-esp8266_non_os_sdk_api_reference_en.pdf



*/


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <I2Cdev.h>

#include <espnow.h>
#include <MPU6050.h>
#include <Adafruit_BMP280.h>

#define PIN_MOSFET 13  //D7
#define PIN_BAT 17      // ESP8266 Analog Pin ADC0 = 17
#define PIN_LED0 16         //D0
#define PIN_LED1 14         //D5
#define PIN_SCL 5           //D1
#define PIN_SDA 4           //D2

MPU6050 MPU(0x68);

typedef struct ang{
    float x;
    float y;
}ang;

ang updateRotation();

uint8_t macESP01[] = {0x84, 0xF3, 0xEB, 0x4C, 0xA0, 0xDF};
uint8_t macWemos[] = {0x3C, 0x61, 0x05, 0xD1, 0xC2, 0x49};
uint8_t macNodeMCU[] = {0xA4, 0xCF, 0x12, 0xC9, 0x91, 0x48};

typedef struct dataWemos{
    bool bat_ok;
    bool hay_golpe;
    int cant_golpes;
    ang posicion_golpe;
}dataWemos;
dataWemos daToSend;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    Serial.print("Last Packet Send Status: ");
    Serial.println((sendStatus == 0) ? "success":"fail");
}

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    //memcpy(&dataReceive, incomingData, sizeof(dataReceive));

    Serial.println("Messagge Received: ");
    //Serial.println(dataReceive);
}


void setup() {
    pinMode(PIN_BAT, INPUT);
    pinMode(PIN_MOSFET, OUTPUT);

    pinMode(PIN_LED0, OUTPUT);
    pinMode(PIN_LED1,OUTPUT);
  
    digitalWrite(PIN_MOSFET, HIGH);
    digitalWrite(PIN_LED1, HIGH);

    Serial.begin(9600);
    Serial.println();

    WiFi.mode(WIFI_STA);
    //ESPNOW CONFIG
    Serial.println(!esp_now_init() ? "ESPNOW Iniciado correctamente":"Error al iniciar ESPNOW");

    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(OnDataRecv);

    //ESPNOW PEER CONFIG
    Serial.println((!esp_now_add_peer(macNodeMCU, ESP_NOW_ROLE_COMBO, 1, NULL, 0)) ? "Peer añadido":"Peer no añadido");
    Serial.println((esp_now_is_peer_exist(macNodeMCU) > 0) ? "NodeMCU Encontrada":"No se encontró NodeMCU");

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

  ang incDisp = updateRotation();
  if (MPU.getIntMotionStatus()) {
    
    Serial.print("Ang X: ");
    Serial.print(incDisp.x);
    Serial.print("  Ang y: ");
    Serial.println(incDisp.y);
    daToSend.bat_ok = true;
    daToSend.cant_golpes++;
    daToSend.hay_golpe = true;

    daToSend.posicion_golpe = incDisp;
    //Serial.println(++golpes);
    esp_now_send(macNodeMCU, (uint8_t *) &daToSend, sizeof(daToSend));
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