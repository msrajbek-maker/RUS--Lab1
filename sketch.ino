#include <DHT.h>  // Ukljucivanje DHT biblioteke za senzor

#define DHTPIN 4        // Pin na kojem je SDA pin DHT22 senzora (Pin 4)
#define DHTTYPE DHT22   // Tip senzora
#define BUTTON_PIN1 2   // Pin za tipkalo 1 (prekid za LED)
#define BUTTON_PIN2 3   // Pin za tipkalo 2 (prekid za DHT22) - izmijenjeno na pin 3
#define LED_PIN 13      // Pin za LED diodu

DHT dht(DHTPIN, DHTTYPE);  

volatile bool buttonPritisnut1 = false;  // Prekid za LED
volatile bool buttonPritisnut2 = false;  // Prekid za DHT22
volatile bool ledUpaljena = false;  // Provjerava da li je LED upaljena
bool porukaIspisana = false;  // Varijabla za kontrolu ispisivanja poruke

void buttonprekid1() {  // ISR za prvo tipkalo (LED)
  buttonPritisnut1 = true;
}

void buttonprekid2() {  // ISR za drugo tipkalo (DHT22)
  if (ledUpaljena) {  // Samo dozvoljava ocitavanje ako je LED dioda upaljena
    buttonPritisnut2 = true;
    porukaIspisana = false;  // Resetira varijablu prilikom dozvoljenog ocitavanja
  } else {
    // Ispisuje poruku samo ako nije ispisana ranije
    if (!porukaIspisana) {
      Serial.println("Nije moguce ocitovanje. Pritisnite button 1.");
      porukaIspisana = true;  // Oznacuje da je poruka ispisana
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
    buttonPritisnut1 = false;  // Resetira vrijednost

    digitalWrite(LED_PIN, HIGH);   // Pali LED diodu
    ledUpaljena = true;            // Oznacuje da je LED dioda upaljena
    delay(5000);                   // LED dioda ostaje upaljena 5 sekundi
    digitalWrite(LED_PIN, LOW);    // Iskljucuje LED diodu
    ledUpaljena = false;           // Resetira status LED diode
  }

  // Ako je pritisnuto drugo tipkalo, ocitava temperaturu i vlaznost
  if (buttonPritisnut2) {
    buttonPritisnut2 = false;  // Resetira vrijednost
    
    // Ocitavanje temperature i vlaznosti
    float h = random(30, 80); 
    float t = random(15, 35); 

    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.print(" °C, Vlaznost: ");
    Serial.print(h);
    Serial.println(" %");
  }

  delay(200);  // Da nema previse izvrsavanja 
}
