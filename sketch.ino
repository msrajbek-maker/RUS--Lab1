#include <DHT.h>  // Uključivanje DHT biblioteke

#define DHTPIN 4        // Pin na kojem je SDA pin DHT22 senzora (Pin 4)
#define DHTTYPE DHT22   // Tip senzora
#define BUTTON_PIN1 2   // Pin za tipkalo 1 (prekid za LED)
#define BUTTON_PIN2 3   // Pin za tipkalo 2 (prekid za DHT22) - izmijenjeno na pin 3
#define LED_PIN 13      // Pin za LED diodu

DHT dht(DHTPIN, DHTTYPE);  

volatile bool buttonPritisnut1 = false;  // Prekid za LED
volatile bool buttonPritisnut2 = false;  // Prekid za DHT22
volatile bool ledUpaljena = false;  // Provjera da li je LED upaljena
bool porukaIspisana = false;  // Varijabla za kontrolu ispisivanja poruke

void buttonprekid1() {  // ISR za prvo tipkalo (LED)
  buttonPritisnut1 = true;
}

void buttonprekid2() {  // ISR za drugo tipkalo (DHT22)
  if (ledUpaljena) {  // Samo dozvoli očitavanje ako je LED dioda upaljena
    buttonPritisnut2 = true;
    porukaIspisana = false;  // Resetiraj varijablu kad je očitavanje dozvoljeno
  } else {
    // Ispisuje poruku samo ako nije ispisana ranije
    if (!porukaIspisana) {
      Serial.println("Nije moguće očitovanje. Pritisnite button 1.");
      porukaIspisana = true;  // Označi da je poruka ispisana
    }
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(BUTTON_PIN1, INPUT_PULLUP);  // Tipkalo za LED
  pinMode(BUTTON_PIN2, INPUT_PULLUP);  // Tipkalo za DHT22
  pinMode(LED_PIN, OUTPUT);            // LED dioda

  // Prekidi za oba tipkala
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN1), buttonprekid1, FALLING);  // Prekid za LED
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN2), buttonprekid2, FALLING);  // Prekid za DHT22
}

void loop() {
  // Ako je pritisnuto prvo tipkalo, pali LED
  if (buttonPritisnut1) {
    buttonPritisnut1 = false;  // Resetiraj flag

    digitalWrite(LED_PIN, HIGH);   // Upali LED diodu
    ledUpaljena = true;            // Označi da je LED dioda upaljena
    delay(5000);                   // LED dioda ostaje upaljena 5 sekundi
    digitalWrite(LED_PIN, LOW);    // Isključi LED diodu
    ledUpaljena = false;           // Resetiraj status LED diode
  }

  // Ako je pritisnuto drugo tipkalo, očitaj temperaturu i vlažnost
  if (buttonPritisnut2) {
    buttonPritisnut2 = false;  // Resetiraj flag
    
    // Simulacija očitavanja temperature i vlažnosti
    float h = random(30, 80); 
    float t = random(15, 35); 

    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.print(" °C, Vlažnost: ");
    Serial.print(h);
    Serial.println(" %");
  }

  delay(200);  // Mali delay kako bi spriječio previše procesiranja
}
