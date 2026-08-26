#include <Arduino.h>

const int LED_G = 2;
const int LED_R = 4;
const int BUZZER = 5;

void setup() {
  Serial.begin(9600);

  pinMode(LED_G, OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, LOW);
  digitalWrite(BUZZER, LOW);  


}

void loop() {
  if(Serial.available()>0){
    char comando = Serial.read();
    if(comando == 'G'){
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_R, LOW);
      digitalWrite(BUZZER, LOW);  

    }
    else if(comando == 'R'){
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_R, HIGH);
      Serial.write("apito");
      digitalWrite(BUZZER, HIGH);  
    }
  }
}