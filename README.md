Sustav za prekide radi tako da pritiskom na tipkalo 1 pokreće LED diodu koja se uključi na 5 sekundi. Prilikom tih 5 sekundi potrebno je pritisnuti tipkalo 2 koje aktivira senzor temperature i vlažnosti zraka. Ako se ne klikne prvo na tipkalo 1 koje uključuje diodu, nego direktno na tipkalo 2 tada će biti poruka na serijskom monitoru da nije moguće očitovanje te da pritisnemo tipkalo 1. Na senzoru se očitavaju nasumične vrijednosti temperature i vlažnosti zraka unutar unaprijed definiranog raspona (primjerice: temperatura od 15°C do 35°C, vlažnost od 30% do 80%). Svakim novim pritiskom na tipkalo sustav generira nove podatke unutar tog raspona. Predstavlja neku bazu sustava koja služi za praćenje temperature i vlažnosti prostora. Upotreba sustava može biti prilagođena za uvjete u prostorima poput staklenika, laboratorija, pametnih kuća, sistem sale (server soba) i slično. Sustav je jednostavan i očitava podatke, a može se proširiti da se navedeni podaci pohranjuju ili prenose na aplikaciju koju bi osoba mogla koristiti na mobilnom uređaju. Nadogradnja ovog sustava mogla bi uključiti LCD zaslon koji bi služio za trenutni prikaz izmjerenih vrijednosti, budući da u Wokwi simulatoru koristim serijski monitor. Tako bi i za nadogradnju moglo biti da koristimo neku automatsku reakciju poput ventilatora koji bi se uključio u određenim uvjetima, odnosno visokoj temperaturi ili ovlaživača zraka kada bi bila niska vlažnost. U tome može se podesiti da sustav radi na baterije ili solarne panele radi korištenja negdje gdje je potrebna prenosivost samog sustava, a i zbog same uštede energije.


## Grafikon strukture - "Prikaz strukture sustava s komponentama i njihovim međusobnim vezama"
![slika1](https://github.com/user-attachments/assets/af6122d3-f819-4385-8937-ad65935a83c0)

## Komponente

| Komponenta              | Količina | Pin na Arduino Mega             | 
|-------------------------|----------|---------------------------------|
| Arduino Uno             | 1        | -                               |
| Tipkalo 1               | 1        | GIO2                            |
| Tipkalo 2               | 1        | GIO3                            | 
| Crvena LED              | 1        | 13                              | 
| DHT22 sensor | 1 | SDA: GIO4, VCC: 5V, GND: GND|
|Otpornik 200Ω | 1 | između GIO13 i LED |

## Funkcionalni zahtjevi

| ID    | Opis                                                                                          |
|-------|-----------------------------------------------------------------------------------------------|
| FR-1  | Sustav mora detektirati pritiske tipkala (BUTTON1, BUTTON2) i aktivirati LED diodu |
| FR-2  | Prekid tipkala mora imati definirane prioritete |
| FR-3  | Sustav mora ignorirati višestruke signale uzrokovane mehaničkim odbijanjem tipkala |
| FR-4  | Sustav mora omogućiti korisniku pritisak na **tipkalo 1** za uključivanje LED diode na 5 sekundi |
| FR-5  | Nakon uključivanja LED diode pomoću **tipkala 1**, korisnik mora pritisnuti **tipkalo 2** kako bi aktivirao senzor temperature i vlažnosti (unutar tih 5 sekundi) |
| FR-6  | Ako ne pritisnemo unutar 5 sekundi isključi se funkcionalnost i sustav se mora ponovo pokrenuti na **Tipkalo 1**|
| FR-7  | Ako korisnik pritisne tipkalo 2 prije tipkala 1, sustav mora prikazati poruku na serijskom monitoru koja obavještava korisnika da pritisne prvo tipkalo 1. |
| FR-8  | Senzor temperature i vlažnosti (DHT22) mora očitavati nasumične vrijednosti unutar definiranog raspona (npr. temperatura od 15°C do 35°C, vlažnost od 30% do 80%). |
| FR-9  | Svakim novim pritiskom na **tipkalo 2**, sustav mora generirati nove nasumične podatke za temperaturu i vlažnost. |
| FR-10   | Na serijskom monitoru mora biti ispisana poruka s očitanim vrijednostima temperature i vlažnosti kad se senzor aktivira. |
| FR-11   | Sustav na kraju može koristiti mali delay kako bi spriječio previše procesiranja (u mojem slučaju delay(200)) |
| FR-12   | Prekidi moraju biti brzi i precizni bez grešaka

## Plan ispitivanja, rezultati ispitivanja

Test 1: Funkcionalnost prekida tipkala 1  
Proces: Nakon svakog pritiska tipkala, LED dioda se uspješno pali  
Status: Prošlo, uspješno radi

Test 2: Funkcionalnost prekida tipkala 2  
Proces: Unutar 5 sekundi pritiskom na tipkalo 2 pojavljuju se rezultati temperature i vlažnosti  
Status: Prošlo, uspješno radi

Test 3: Funkcionalnost prekida tipkala  
Proces: Prilikom pritiska odmah na tipkalo 2 izbacuje poruku da nema očitovanje te da pritisnemo tipkalo 1  
Status: Prošlo, uspješno radi

Test 4: Validacija očitanja senzora  
Proces: Senzor je generirao temperaturu od 15°C do 35°C i vlažnost od 30% do 80%   
Status: Prošlo, uspješno radi  

Test 5: Testiranje više ciklusa  
Proces: Nakon 10 uzastopnih pritisaka, sustav je svaki put ispravno generirao nove vrijednosti   
Status: Prošlo, uspješno radi  

## Link za projekt na Wokwi stranici je: https://wokwi.com/projects/426611158698088449


