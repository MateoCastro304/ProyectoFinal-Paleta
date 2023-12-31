#include "EspNow-Paddel.h"

uint8_t macESP01[] = {0x84, 0xF3, 0xEB, 0x4C, 0xA0, 0xDF};
uint8_t macWemos[] = {0x3C, 0x61, 0x05, 0xD1, 0xC2, 0x49};
uint8_t macNodeMCU[] = {0xA4, 0xCF, 0x12, 0xC9, 0x91, 0x48};

uint8_t* dev_to_send = macESP01;    //Definir El dispositivo peer


char dataReceive[60];
data_paddel _data_recv;
bool _is_recv = false;
data_paddel get_data_recv(){
    return _data_recv;
}
bool flag_is_recv(){
    return _is_recv;
}
void clear_flag(){
    _is_recv = false;
}
bool set_espnow(uint8_t rol){
    if (esp_now_init() != 0) {
        return 0;
    }

    esp_now_set_self_role(rol);
    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(OnDataRecv);

    return 1;
}

void set_peer(uint8_t rol){
    esp_now_add_peer(dev_to_send, rol, 1, NULL, 0);
}

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
    memcpy(&_data_recv, incomingData, sizeof(_data_recv));
    
    _is_recv = true;
}

void send_to_peer(uint8_t *structurePointer, int structureLength){
    esp_now_send(dev_to_send, structurePointer, structureLength);
}