#include <Arduino.h>

/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>

//My MAC: 84:F3:EB:4C:A0:DF
//Oth MAC: 3C:61:05:D1:C2:49
uint8_t macESP01[] = {0x84, 0xF3, 0xEB, 0x4C, 0xA0, 0xDF};
uint8_t macWemos[] = {0x3C, 0x61, 0x05, 0xD1, 0xC2, 0x49};
//const char* host = "djxmmx.net";
//const uint16_t port = 17;
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    String d;
    bool e;
} struct_message;

struct_message myData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    Serial.print("Sending... Delivery: ");
    Serial.println(!sendStatus ? "Success":"Fail");
    /*if (sendStatus == 0){
    Serial.println("Success");
    }
    else{
        Serial.println("Fail");
    }*/
}
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    memcpy(&myData, incomingData, sizeof(myData));

    String _buff = "Bytes received: "+ String(len) + "\nChar: "+ String(myData.a);
    Serial.println(_buff);
    delay(5);
    _buff = "Int: "+ String(myData.b) + "\nFloat: "+ String(myData.c);
    Serial.println(_buff);
    delay(5);
    _buff = "String "+ String(myData.d) + "\nbool: "+ String(myData.e);
    Serial.println(_buff);
    delay(5);
    char ask[] = "ESP01: Estructura Recibida";
    esp_now_send(macWemos, (uint8_t *) &ask, sizeof(ask));
    /*Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("Char: ");
    Serial.println(myData.a);
    Serial.print("Int: ");
    Serial.println(myData.b);
    Serial.print("Float: ");
    Serial.println(myData.c);
    Serial.print("String: ");
    Serial.println(myData.d);
    Serial.print("Bool: ");
    Serial.println(myData.e);
    Serial.println();*/
}

void setup() {
    Serial.begin(9600);

    Serial.println();
    Serial.println();
  
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    // Init ESP-NOW
    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
  
    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_register_recv_cb(OnDataRecv);

    //Add peer
    esp_now_add_peer(macWemos, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    esp_now_register_send_cb(OnDataSent);
    
}

void loop() {
    
    
}
