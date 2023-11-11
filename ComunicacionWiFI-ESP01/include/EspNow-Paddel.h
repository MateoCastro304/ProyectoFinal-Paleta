#ifndef ESPNOW_PADDEL
#define ESPNOW_PADDEL

#include <Arduino.h>
#include <espnow.h>
#include <ESP8266WiFi.h>

typedef struct data_paddel {
    char a[32];
    int b;
    float c;
    String d;
    bool e;
} data_paddel;
// typedef struct ang{
//   float x;
//   float y;
// }ang;

// typedef struct MPUData{
//     float angx;
//     float angy;
// };

// typedef struct BMData{
//     float h;
//     float temp;
// };

// typedef struct data_paddel {
//     ang anggolpe;
//     MPUData MPU_data;
//     BMData BM_data;
//     int golpes;
// } data_paddel;

// data_paddel myData;

bool set_espnow(uint8_t rol);
void set_peer(uint8_t rol);

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus); ///Datos Envío
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len); ///Desempaquetar datos recibidos

void send_to_peer(uint8_t *structurePointer, int structureLength);
data_paddel get_data_recv();

#endif