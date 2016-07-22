/*  CRÉDITS
 *  SimpleKeypad : Exemple pour la librairie MyKeypad
 *  Créé par Jacques Bellavance, le 25 juin 2016
 *  Ce code est du domaine public
 */ 

/*  MONTAGE
 *  MyKeypad permet d'utiliser jusqu'à 16 interrupteurs 
 *  qui peuvent être lus sur une broche d'entrée analogue d'un Arduino.
 *  +5V-----Rpullup-----+--------+-------+--- ... ---+-----A12
 *                     1nF      SW0     SW1   ...   SWn
 *                     CAP      R0      R1    ...   Rn
 *  GND-----------------+--------+-------+--- ... ---+
 * Pour un Pullup de 10 KOhms : 
 * R0 = 1.2 KOhms
 * R1 = 3.9 KOhms
 * R2 = 10.0 KOhms
 * R3 = 22.0 KOhms
 * R4 = 82.0 KOhms
 */

/* MÉTHODES
 * boolean keyPressed()          Retourne vrai si un des interrupteurs est fermé.
 * int getKey()                  Retourne le numéro (0..n-1) de l'interrupteur fermé. Debounce à 50ms.
 * int getKey(debounceLimit)     Permet de spécifier la durée du debounce (en millisecondes). 
 * int getKeyAndWaitForRelease() Comme getKey(), mais attend que l'interrupteur soit ouvert avant de retourner son numéro.
 */

#include <MyKeypad.h>;

//CONSTRUCTEUR===========================
int inputPin = A12;
int buttonCount = 5;
MyKeypad keypad(inputPin,buttonCount);
//---------------------------------------

void setup() {
Serial.begin(9600);
}

void loop() {
  if (keypad.keyPressed()) {
    int key = keypad.getKeyAndWaitForRelease(); // ou : int key = keypad.getKey();
    switch (key) {
      case 0: {
        Serial.println("Left");
        break;
      }
      case 1: {
        Serial.println("Right");
        break;
      }
      case 2: {
        Serial.println("Up");
        break;
      }
      case 3: {
        Serial.println("Down");
        break;
      }
      case 4: {
        Serial.println("Enter");
        break;
      }
    }
  }
}
