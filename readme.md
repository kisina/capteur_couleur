# Capteur de couleur (TCS3200) — Mesure par interruptions

Projet Arduino pour mesurer la fréquence de sortie du capteur de couleur TCS3200 en utilisant des interruptions. Le sketch principal est [test_capteur_couleur_interruptions_complet.ino](test_capteur_couleur_interruptions_complet.ino).

## Fichiers du workspace
- [test_capteur_couleur_interruptions_complet.ino](test_capteur_couleur_interruptions_complet.ino) — code principal (mesure et affichage).
- [.vscode/arduino.json](.vscode/arduino.json) — configuration de la carte/port pour l'extension Arduino.
- [.vscode/c_cpp_properties.json](.vscode/c_cpp_properties.json) — configuration IntelliSense.

## Principe
Le sketch compte les fronts montants sur la sortie du capteur (broche définie par [`OUT`](test_capteur_couleur_interruptions_complet.ino)) via une routine d'interruption (`[`compteurPlus`](test_capteur_couleur_interruptions_complet.ino)`). Pendant une fenêtre temporelle définie par [`window`](test_capteur_couleur_interruptions_complet.ino) (200 ms), le compteur (`[`compteur`](test_capteur_couleur_interruptions_complet.ino)`) est remis à zéro, puis la fréquence est calculée avec la formule :
$ f = \text{count} \times \dfrac{1000}{\text{window}} $
(le code implémente ceci et stocke la valeur dans [`RGB_frequency_array`](test_capteur_couleur_interruptions_complet.ino)).

## Connexions (Arduino UNO)
Les constantes de broche sont définies dans le sketch :
- [`S0`](test_capteur_couleur_interruptions_complet.ino), [`S1`](test_capteur_couleur_interruptions_complet.ino), [`S2`](test_capteur_couleur_interruptions_complet.ino), [`S3`](test_capteur_couleur_interruptions_complet.ino) — entrées de configuration du TCS3200.
- [`OUT`](test_capteur_couleur_interruptions_complet.ino) — sortie du capteur reliée à une entrée d'interruption (pin 2).
- [`LED`](test_capteur_couleur_interruptions_complet.ino) — LED d'éclairage (optionnelle).

Branchez le TCS3200 selon sa documentation : S0..S3 aux broches indiquées, la sortie OUT sur la broche d'interruption (pin 2 sur UNO), alimentation GND/VCC selon le capteur, et LED si utilisée.

## Réglages importants dans le code
- Échelle de mesure : variable [`colors_scale`](test_capteur_couleur_interruptions_complet.ino) (0..3) contrôle la sensibilité via S0/S1.
- Sélection des filtres couleur : [`colors_selection`](test_capteur_couleur_interruptions_complet.ino) parcourt R/G/B/Clair et écrit les broches S2/S3 en conséquence.
- Fenêtre de mesure : [`window`](test_capteur_couleur_interruptions_complet.ino) en ms (par défaut 200).

## Utilisation
1. Ouvrir le projet dans VS Code.
2. Vérifier [`.vscode/arduino.json`](.vscode/arduino.json) pour la carte et le port configurés.
3. Téléverser le sketch [test_capteur_couleur_interruptions_complet.ino](test_capteur_couleur_interruptions_complet.ino) avec l'extension Arduino.
4. Ouvrir le moniteur série à 9600 bauds (Serial.begin(9600) dans le sketch).
5. Lire les fréquences R/G/B/Clair et les pourcentages relatifs affichés.

## Sortie série
Le sketch imprime périodiquement :
- Les fréquences mesurées (Hz) pour `R`, `G`, `B`, `C`.
- Les pourcentages normalisés R/G/B (sur la somme des 3 canaux).

## Dépannage
- Si aucune interruption n'est comptée, vérifier le câblage de [`OUT`](test_capteur_couleur_interruptions_complet.ino) et la compatibilité du numéro de pin d'interruption.
- Ajuster [`colors_scale`](test_capteur_couleur_interruptions_complet.ino) si le signal est trop faible/fort.
- Vérifier la stabilisation (delay(100)) et augmenter si nécessaire.

## Références rapides (symboles clés)
- [`compteur`](test_capteur_couleur_interruptions_complet.ino)
- [`compteurPlus`](test_capteur_couleur_interruptions_complet.ino)
- [`RGB_frequency_array`](test_capteur_couleur_interruptions_complet.ino)
- [`colors_scale`](test_capteur_couleur_interruptions_complet.ino)
- [`window`](test_capteur_couleur_interruptions_complet.ino)
- [`S0`, `S1`, `S2`, `S3`, `OUT`, `LED`](test_capteur_couleur_interruptions_complet.ino)

---
Pour modifier la configuration de build/port, consultez [.vscode/arduino.json](.vscode/arduino.json) et pour l'édition IntelliSense [.vscode/c_cpp_properties.json](.vscode/c_cpp_properties.json).
