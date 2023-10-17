#include "EspNow-Paddel.h"

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    Serial.print("Last Packet Send Status: ");
    if (sendStatus == 0){
        Serial.println("Delivery success");
    }
    else{
        Serial.println("Delivery fail");
    }
}
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    
}

void send_to_peer(uint8_t *structurePointer, int structureLength){
    esp_now_send(dev_to_send, structurePointer, structureLength);
}