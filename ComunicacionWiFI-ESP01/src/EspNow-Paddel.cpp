#include "EspNow-Paddel.h"

uint8_t macESP01[] = {0x84, 0xF3, 0xEB, 0x4C, 0xA0, 0xDF};
uint8_t macWemos[] = {0x3C, 0x61, 0x05, 0xCF, 0xB3, 0x9C};

uint8_t* dev_to_send = macWemos;    //Definir El dispositivo peer


data_paddel _data_recv;

data_paddel get_data_recv(){
    return _data_recv;
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
    Serial.print("Sending... Delivery: ");
    Serial.println(!sendStatus ? "Success":"Fail");
}
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
}

void send_to_peer(uint8_t *structurePointer, int structureLength){
    esp_now_send(dev_to_send, structurePointer, structureLength);
}