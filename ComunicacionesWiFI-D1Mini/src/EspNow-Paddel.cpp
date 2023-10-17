#include "EspNow-Paddel.h"

uint8_t macESP01[] = {0x84, 0xF3, 0xEB, 0x4C, 0xA0, 0xDF};
uint8_t macWemos[] = {0x3C, 0x61, 0x05, 0xD1, 0xC2, 0x49};
uint8_t macNodeMCU[] = {0xA4, 0xCF, 0x12, 0xC9, 0x91, 0x48};
uint8_t* dev_to_send;

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

