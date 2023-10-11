#include <ESPNOWPaddel.h>

void send_to_peer(uint8_t *structurePointer, int structureLength){
    esp_now_send(dev_to_send, structurePointer, structureLength);
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

/*void set_peer(uint8_t *mac_dev, uint8_t rol){
    esp_now_add_peer(mac_dev, rol, 1, NULL, 0);
    dev_to_send = mac_dev;
}*/

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