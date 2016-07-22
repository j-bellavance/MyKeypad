/*  CRÉDITS
 *  ResistorValues : Exemple pour la librairie MyKeypad
 *  Créé par Jacques Bellavance, le 25 juin 2016
 *  Ce code est du domaine public
 */ 

/*  CONNEXIONS
 *  MyKeypad permet d'utiliser jusqu'à 16 interrupteurs 
 *  qui peuvent être lus sur une broche d'entrée analogue d'un Arduino.
 *  +5V-----Rpullup-----+--------+-------+--- ... ---+-----A10
 *                     1nF      SW0     SW1   ...   SWn
 *                     CAP      R0      R1    ...   Rn
 *  GND-----------------+--------+-------+--- ... ---+
 */

/* INTRODUCTION
 * Ce sketch permet d'afficher sur le moniteur série de l'arduino
 * les valeurs des résistances R1..Rn qui seront optimales.
 * La plage des valeurs possibles pour une broche analogue de l'Arduino est de 0 à 1023.
 * Pour un montage avec n interrupteurs, la plage 0..1024 est divisée en n segments.
 * Le centre de chaque segment est la cible vers laquelle la résistance choisie doit tendre.
 * Les résistances choisies font partie de la série E12 et sont supposées à +- 5%
 * (voir :http://www.positron-libre.com/cours/electronique/resistances/serie-resistance.php)
 * 
 * NOTE :
 * La librairie accepte des montages avec jusqu'à 16 interrupteurs.
 */
  
/* MÉTHODES
 * Le constructeur doit avoir comme arguments :
 * - La broche analogue sur laquelle la montage est connecté
 * - Le nombre d'interrupteurs du montage
 * 
 * La méthode calculateResistorValues() peut être appelée avec ou sans la valeur de laq résistance de rappel.
 * Si elle est appelée sans la résistance de rappel la valeur utilisée est de 10 KOhms
 * 
 * La méthode getResistorValue(i) permet de lire la valeur de la ième résistance
 * 
 * La méthode getRealPullup() permet de récupérer la vraie valeur utilisée pour les calculs.
 */

/* UTILISATION
 * Dans les VARIABLES GLOBALES, 
 * - changer « switchCount » pour le nombre d'interrupteurs du montage
 * - changer « pullup » pour la valeur que vous désirez utiliser
 * Téléverser le sketch vers l'Arduino
 * Ouvrir le moniteur série et lire les valeurs de R0..Rn
 */

#include <MyKeypad.h>

//VARIABLES GLOBALES=====================================================
int readPin = A10;        //Broche sur laquelle est branchée le montage
int switchCount = 10;     //Nombre d'interrupteurs du montage
double pullup = 10000.0;  //Valeur de la résistance de rappel (Pullup)
//-----------------------------------------------------------------------

MyKeypad test(readPin,switchCount); //L'objet du montage est nommé « test »

//Setup()=================================================================================
void setup() {
  Serial.begin(9600);                         //Initialisation du moniteur série
  Serial.println("Demarrage...");             //Indication du début
  test.calculateResistorsValues(pullup);      //Calcul des résistances
//test.calculateResistorsValues();            //pullup = 10 KOhms
  Serial.print("Pour un Pullup de ");         //Valeur réelle de la résistance de rappel
  Serial.print(long(test.getRealPullup()));
  Serial.println(" Ohms : ");
  for (int i=0 ; i<switchCount ; i++) {       //Pour chaque résistance
    char prefix = 'K';                          //Afficher sa valeur
    Serial.print('R');
    Serial.print(i);
    Serial.print(" = ");
    double rval = (test.getResistorValue(i));
    if (rval > 999 ) {
       prefix = 'K';
       rval /= 1000;
    }
    else prefix = ' ';
    Serial.print(rval,1);
    Serial.print(' ');
    Serial.print(prefix);
    Serial.println(" Ohms");
  }
}//Setup()-----------------------------------------------------------------------------------

void loop() {}
