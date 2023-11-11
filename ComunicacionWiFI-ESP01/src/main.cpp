#include <Arduino.h>

/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>
#include "EspNow-Paddel.h"
//My MAC: 84:F3:EB:4C:A0:DF
//Oth MAC: 3C:61:05:D1:C2:49
//NUEVO WEMOS3C:61:05:CF:B3:9C

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



void setup() {
    Serial.begin(9600);

    Serial.println();
    Serial.println();
  
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    //WiFi.disconnect();
    // Init ESP-NOW
    if (!set_espnow(ESP_NOW_ROLE_COMBO)) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    set_peer(ESP_NOW_ROLE_COMBO);
    
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
