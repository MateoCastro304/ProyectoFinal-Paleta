#include <Arduino.h>




void setup() {
  // put your setup code here, to run once:
  digitalWrite(6,0);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(8,OUTPUT);
  delay(100);
  digitalWrite(6,1);
}

void loop() {
  digitalWrite(5,1);
  delay(20);
  digitalWrite(5,0);
  delay(20);
  
  // put your main code here, to run repeatedly:
}

