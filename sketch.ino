#include <DHT.h>  // Ukljucivanje DHT biblioteke

#define DHTPIN 3        // Pin na kojem je SDA pin DHT22 senzora (Pin 3)
#define DHTTYPE DHT22   // Tip senzora
#define BUTTON_PIN 2    // Pin za tipkalo (prekid)
#define LED_PIN 13      // Pin za LED diodu

DHT dht(DHTPIN, DHTTYPE);  

volatile bool buttonPritisnut = false;  


void buttonprekid() {
  buttonPritisnut = true;  
}

void setup() {
  Serial.begin(9600);   
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  pinMode(LED_PIN, OUTPUT);  

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonprekid, FALLING);
}

void loop() {
  if (buttonPritisnut) {
    buttonPritisnut = false;  

    float h = random(30, 80); 
    float t = random(15, 35);  

    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.print(" °C, Vlaznost: ");
    Serial.print(h);
    Serial.println(" %");

    digitalWrite(LED_PIN, HIGH);   
    delay(1000);                    
    digitalWrite(LED_PIN, LOW);    
  }

  delay(2000); 
}
