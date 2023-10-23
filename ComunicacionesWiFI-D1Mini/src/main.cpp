#include "EspNow-Paddel.h"

#ifndef STASSID
    #define STASSID "Electronica_ALUMNOS"
    #define STAPSK  "alumnosElec2022"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

typedef struct data_paddel {
    char a[32];
    int b;
    float c;
    String d;
    bool e;
} data_paddel;

data_paddel myData;
//ESP01 MAC: 84:F3:EB:4C:A0:DF
//WEMOS MAC: 3C:61:05:D1:C2:49
//NODEMCU MAC: A4:CF:12:C9:91:48
// uint8_t macESP01[] = {0x84, 0xF3, 0xEB, 0x4C, 0xA0, 0xDF};
// uint8_t macWemos[] = {0x3C, 0x61, 0x05, 0xD1, 0xC2, 0x49};
// uint8_t macNodeMCU[] = {0xA4, 0xCF, 0x12, 0xC9, 0x91, 0x48};
// void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
//     Serial.print("Last Packet Send Status: ");
//     if (sendStatus == 0){
//         Serial.println("Delivery success");
//     }
//     else{
//         Serial.println("Delivery fail");
//     }
// }
//char recvAsk[50];
// void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
//     memcpy(&recvAsk,incomingData,sizeof(recvAsk));
//     String impresion(recvAsk);
//     Serial.println(impresion);
// }

void setup() {
    Serial.begin(9600);
    delay(1);
    Serial.println();
    Serial.println("ESPNOW two-way initializing: ");

    WiFi.mode(WIFI_STA);
    // WiFi.begin(STASSID, STAPSK);
    // Serial.print("\nConnecting to ");
    // Serial.println(STASSID);

    // while (WiFi.status() != WL_CONNECTED) {
    //   Serial.print('.');
    //   delay(500);
    // }
    WiFi.disconnect();
    Serial.println();
    Serial.print("connected, address=");
    Serial.println(WiFi.localIP());
    //WiFi.disconnect();
    // Init ESP-NOW
    if (!set_espnow(ESP_NOW_ROLE_COMBO)) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    set_peer(macNodeMCU, ESP_NOW_ROLE_COMBO);
    
    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    //esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    //esp_now_register_send_cb(OnDataSent);
    //esp_now_register_recv_cb(OnDataRecv);

    // Register peer
    //esp_now_add_peer(macNodeMCU, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    // esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    // esp_now_register_send_cb(OnDataSent);
  
    // // Register peer
    // esp_now_add_peer(macNodeMCU, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
    static unsigned long lastTime = 0;  
    const int timerDelay = 5000;
    if ((millis() - lastTime) > timerDelay) {
        // Set values to send
        static float i=0;
   
        strcpy(myData.a, "THIS IS A CHAR");
        myData.b = random(1,20);
        myData.c = i;
        myData.d = "Hello";
        myData.e = !myData.e;

        // Send message via ESP-NOW
        //esp_now_send(macNodeMCU, (uint8_t *) &myData, sizeof(myData));
        send_to_peer((uint8_t *) &myData,sizeof(myData));

        i += 0.5;
        lastTime = millis();
    }
}