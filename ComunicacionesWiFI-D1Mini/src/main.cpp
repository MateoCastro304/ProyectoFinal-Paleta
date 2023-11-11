#include "EspNow-Paddel.h"

#ifndef STASSID
    #define STASSID "Electronica_ALUMNOS"
    #define STAPSK  "alumnosElec2022"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;



data_paddel myData;
//ESP01 MAC: 84:F3:EB:4C:A0:DF
//WEMOS MAC: 3C:61:05:D1:C2:49
//NUEVO WEMOS3C:61:05:CF:B3:9C
//NODEMCU MAC: A4:CF:12:C9:91:48

void setup() {
    Serial.begin(9600);
    delay(1);
    Serial.println();
    Serial.println("ESPNOW two-way initializing: ");

    WiFi.mode(WIFI_STA);

    Serial.println();
    Serial.print("connected, address=");
    Serial.println(WiFi.macAddress());
    
    if (!set_espnow(ESP_NOW_ROLE_COMBO)) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    set_peer(ESP_NOW_ROLE_COMBO);
}

void loop() {
   if(flag_is_recv()){
    myData = get_data_recv();
    String _buff = "Char: "+ String(myData.a);
    Serial.println(_buff);
    delay(5);
    _buff = "Int: "+ String(myData.b) + "\nFloat: "+ String(myData.c);
    Serial.println(_buff);
    delay(5);
    _buff = "String "+ String(myData.d) + "\nbool: "+ String(myData.e);
    Serial.println(_buff);
    delay(5);

    clear_flag();
   }
}