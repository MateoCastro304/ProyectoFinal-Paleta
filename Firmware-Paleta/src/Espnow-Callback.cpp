#include "EspNow-Paddel.h"

char dataReceive[60];
data_paddel daToSend = {
    .anggolpe={0,0},
    .golpes = 0,
    .altitude = 0,
    .valueBattery = 0,
    .error = 0,
};
/*
typedef struct data_paddel {
    ang anggolpe;
    float pressure;
    int golpes;
    float altitude;
    int valueBattery;
    uint8_t error;
} data_paddel;
*/
//Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    Serial.print("Last Packet Send Status: ");
    if (sendStatus == 0){
        Serial.println("Delivery success");
    }
    else{
        Serial.println("Delivery fail");
    }
}

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    memcpy(&dataReceive, incomingData, sizeof(dataReceive));

    Serial.println("Messagge Received: ");
    Serial.println(dataReceive);
}

void send_to_peer(uint8_t *structurePointer, int structureLength){
    esp_now_send(dev_to_send, structurePointer, structureLength);
}