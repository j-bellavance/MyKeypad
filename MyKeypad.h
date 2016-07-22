/* CRÉDITS
 * MyKeypad
 * Créé par Jacques Bellavance, le 25 juin 2016
 * Ce code est du domaine public
 */

/* MONTAGE
 * MyKeypad permet d'utiliser jusqu'à 16 interrupteurs
 * qui peuvent être lus sur une broche d'entrée analogue d'un Arduino.
 * +5V-----Rpullup-----+------+-------+--- ... ---+-----A10
 *                    1nF    SW0     SW1   ...   SWn
 *                     |     R0      R1    ...   Rn
 * GND-----------------+------+-------+--- ... ---+
 */

/* INTRODUCTION
 * La plage des valeurs possibles pour une broche analogue de l'Arduino est de 0 à 1023.
 * Pour un montage avec n interrupteurs, la plage 0..1024 est divisée en n segments.
 * Le centre de chaque segment est la cible vers laquelle la résistance choisie doit tendre.
 * Les résistances choisies font partie de la série E12 et sont supposées à +- 5%
 * (voir :http://www.positron-libre.com/cours/electronique/resistances/serie-resistance.php)
 *
 * NOTE :
 * La librairie accepte des montages avec jusqu'à 16 interrupteurs.
 * Au-delà, il faut utiliser des résistances de la série E48 avec des précisions de +- 2%
 * ou de la série E96 avec des précisions de +- 1%
 * Pour les personnes intéressées à changer le code pour ces montages :
 * - modifier « nearestResistor() » dans MyKeypad.cpp.
 * - modifier « MYresistors[XX] » ici.
 */

#ifndef MyKeypad_h
#define MyKeypad_h

#include "Arduino.h"

class MyKeypad {
  public:
    MyKeypad(int inputPin, int butonCount);         //CONSTRUCTEUR
	bool keyPressed();                              //Indique si un interrupteur est présentement fermé
	int getKey();                                   //Retourne le numéro (0..n) de l'interrupteur
	int getKey(int debounceLimit);                  //Retourne le numéro (0..n) de l'interrupteur avec valeur de délai de rebond
	int getKeyAndWaitForRelease();                  //Retourne le numéro (0..n) de l'interrupteur et attend qu'il soit relâché
	void calculateResistorsValues();                //Calcule les résistances optimales pour le montage avec une résistance de rappel de 10 KOhms
	void calculateResistorsValues(double pullup);   //Calcule les résistances optimales pour le montage avec une résistance de rappel spécifique
	double getResistorValue(int i);                 //Retourne la valeur de la résistance Ri
	double getRealPullup();                         //Retourne la vraie valeur de la résistance de rappel utilisée pour les calculs
  private:
	double nearestResistor(double target);          //Retourne la valeur de la résistance de la série E12 la plus rapprochée de la valeur cible
    int MYinputPin;                                 //
	int MYbuttonCount;
    float MYbinSize;
	int MYanswer;
	int MYdebounceLimit = 50;
	double MYresistors[16];
	double MYpullup = 10000.0;
};

#endif
