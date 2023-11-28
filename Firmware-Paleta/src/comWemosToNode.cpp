#include "comWemosToNode.h"

//ESP01 MAC: 84:F3:EB:4C:A0:DF
//WEMOS MAC: 3C:61:05:D1:C2:49
//NODEMCU MAC: A4:CF:12:C9:91:48
uint8_t macESP01[] = {0x84, 0xF3, 0xEB, 0x4C, 0xA0, 0xDF};
uint8_t macWemos[] = {0x3C, 0x61, 0x05, 0xD1, 0xC2, 0x49};
uint8_t macNodeMCU[] = {0xA4, 0xCF, 0x12, 0xC9, 0x91, 0x48};

dataWemos dataRecv;
char comandos_node;

char get_comando_node(){
    char _comandos_node = comandos_node;
    comandos_node = 0;
    return _comandos_node;
}
bool _datosActualizados = false;
dataWemos getDatosRecibidos(){
    _datosActualizados = false;
    return dataRecv;
}
bool datosNuevos(){
    return _datosActualizados;
}
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    Serial.print("Sending... Delivery: ");
    Serial.println(!sendStatus ? "Success":"Fail");
}
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    comandos_node = *incomingData;
    char test_recibido = 'L';
    if (comandos_node == 'l')
    {
        send_mac_node((uint8_t*)&test_recibido,sizeof(test_recibido));
    }
    
    Serial.println(comandos_node);
}
bool set_espnow(){
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    Serial.println(!esp_now_init() ? "ESPNOW Iniciado correctamente":"Error al iniciar ESPNOW");
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(OnDataRecv);

    //ESPNOW PEER CONFIG
    Serial.println((!esp_now_add_peer(macNodeMCU, ESP_NOW_ROLE_COMBO, 1, NULL, 0)) ? "Peer añadido":"Peer no añadido");
    Serial.println((esp_now_is_peer_exist(macNodeMCU) > 0) ? "Node Encontrada":"No se encontró Wemos");
    return true;
}
int send_mac_node(uint8_t* structurePointer, int len){
    if (handShaking())
    {
        Serial.println("Ta Todo Bien");
        esp_now_send(macNodeMCU,structurePointer, len);
        return 0;
    }
    else
    {
        Serial.println("Ta Todo Mal");
        return 1;
    }
}
bool handShaking(){
    char test = 'l';

    send_mac_node((uint8_t*)&test,sizeof(test));

    int time = 0;
    unsigned long currentMillis = millis();

    while (get_comando_node() != 'L'){
        if (currentMillis < millis()){
            time ++;
            currentMillis = millis();
        }
        if (time > 1000)
            return false;
    }
    return true;
}