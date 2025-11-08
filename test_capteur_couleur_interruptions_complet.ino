// --- Mesure de fréquence avec interruptions ---

volatile unsigned long compteur = 0; // Compteur d'impulsions (volatile car modifié par ISR)
unsigned long startTime = 0;      // Pour le chronométrage
unsigned long endTime = 0;      // Pour le chronométrage
unsigned long lastDisplay = 0;      // Pour le chronométrage
const unsigned long window = 200;  // Durée de mesure (ms)

// Déclaration pour le capteur de couleur TCS3200
float RGB_frequency_array[4];     // Stockage des valeurs RGB + clarté
int colors_selection = 0;     // Pour le filtrage des couleurs (RGB et clarté)
int colors_scale = 2;   // Choix de l'échelle de fréquence (de 0 (désactivé) à 3 le plus sensible)
char colors[] = {'R', 'G', 'B', 'C'}; // liste des couleurs

// Broches du TCS3200
#define S0     3   
#define S1     4
#define S2     5 
#define S3     6  
#define OUT    2  
#define LED    7  


void setup() {
  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  pinMode(LED, OUTPUT);

  // Choisir l'échelle de 0 à 3 (Off, 2%, 20%, 100%)
  switch(colors_scale) {
    case 0: digitalWrite(S0, LOW); digitalWrite(S1, LOW); break;   // Off
    case 1: digitalWrite(S0, LOW); digitalWrite(S1, HIGH); break;   // 2%
    case 2: digitalWrite(S0, HIGH); digitalWrite(S1, LOW); break;   // 20%
    case 3: digitalWrite(S0, HIGH); digitalWrite(S1, HIGH); break;   // 100%
  }
  
  // Allumer la LED
  digitalWrite(LED, LOW);


  Serial.println("Mesure de fréquence démarrée...");

  // Attacher l’interruption sur front montant
  attachInterrupt(digitalPinToInterrupt(OUT), compteurPlus, RISING);


}


void loop() {
  switch(colors_selection) {
    case 0: digitalWrite(S2, LOW); digitalWrite(S3, LOW); break;   // Rouge
    case 1: digitalWrite(S2, HIGH); digitalWrite(S3, HIGH); break; // Vert
    case 2: digitalWrite(S2, LOW); digitalWrite(S3, HIGH); break;  // Bleu
    case 3: digitalWrite(S2, HIGH); digitalWrite(S3, LOW); break;  // Clair
  }

  delay(100);  // Stabilisation du capteur

  compteur = 0;
  startTime = millis();

  while (millis() - startTime < window) {
    // on attend pendant la fenêtre de mesure
  }

  noInterrupts();
  unsigned long compte = compteur;
  interrupts();

  float frequence = (float)compte * (1000.0 / window);
  RGB_frequency_array[colors_selection] = frequence;

  colors_selection = (colors_selection + 1) % 4;

  if (millis() - lastDisplay >= 1000) {
    float R = RGB_frequency_array[0];
    float G = RGB_frequency_array[1];
    float B = RGB_frequency_array[2];
    float total = R + G + B;
    R = R / total * 100.0;
    G = G / total * 100.0;
    B = B / total * 100.0;

    for (int i = 0; i < 4; i++) {
      Serial.print(colors[i]);
      Serial.print(" = ");
      Serial.print(RGB_frequency_array[i]);
      Serial.println(" Hz");
    }

    Serial.print("R:");
    Serial.print(R);
    Serial.print(" - ");
    Serial.print("G:");
    Serial.print(G);
    Serial.print(" - ");
    Serial.print("B:");
    Serial.print(B);
    Serial.println(" - ");

    lastDisplay = millis();
  }
}

// Fonction d'interruption : incrémente le compteur à chaque front montant
void compteurPlus() {
  compteur++;
}
