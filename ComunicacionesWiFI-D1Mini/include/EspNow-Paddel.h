#ifndef ESPNOW_PADDEL
#define ESPNOW_PADDEL

#include <Arduino.h>
#include <espnow.h>
#include <ESP8266WiFi.h>

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

extern uint8_t macESP01[];
extern uint8_t macWemos[];
extern uint8_t macNodeMCU[];
extern uint8_t* dev_to_send;

bool set_espnow(uint8_t rol);
void set_peer(uint8_t *mac_dev, uint8_t rol);

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus); ///Datos Envío
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len); ///Desempaquetar datos recibidos

void send_to_peer(uint8_t *structurePointer, int structureLength);


#endif