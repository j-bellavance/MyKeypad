/* CRÉDITS
 * MyKeypad
 * Créé par Jacques Bellavance, le 25 juin 2016
 * Ce code est du domaine public
*/
#include "Arduino.h"
#include "MyKeypad.h"

//CONSTRUCTEUR=============================================
//inputPin : broche analogue de l'Arduino
//buttonCount : nombre de d'interrupteurs du montage
//---------------------------------------------------------
MyKeypad::MyKeypad(int inputPin, int buttonCount) {
  pinMode(inputPin, INPUT);
  MYinputPin = inputPin;
  MYbuttonCount = buttonCount;
  MYbinSize = 1024 / buttonCount;
}//--------------------------------------------------------

//keyPressed()==========================================================
//La valeur 1010 a été choisie arbitrairement pour permetre une
//variation dans des environnements bruyants (électriquement parlant).
//----------------------------------------------------------------------
bool MyKeypad::keyPressed() {
  if (analogRead(MYinputPin) < 1000) return analogRead(MYinputPin);
  else                           	 return 0;
}//---------------------------------------------------------------------

//getKey()=========================================================================
//Retourne le numéro de l'interrupteur qui est ouvert (0..n-1)
//Un délai pour détecter un rebond de l'interrupteur a été défini dans MyKeypad.h
//En cas d'erreur, la valeur 99 est retournée.
//---------------------------------------------------------------------------------
int MyKeypad::getKey() {
	unsigned long topchrono = millis();
	MYanswer = int(analogRead(MYinputPin)/MYbinSize);
	while (millis() - topchrono < MYdebounceLimit) {}
	if (int(analogRead(MYinputPin) / MYbinSize) == MYanswer) return MYanswer;
	else                                                     return 99;
}//--------------------------------------------------------------------------------

//getKey(int)======================================================================
//Retourne le numéro de l'interrupteur qui est ouvert (0..n-1)
//Le délai pour détecter un rebond de l'interrupteur est fourni en argument
//Utiliser cette syntaxe si la valeur par défaut (50ms) est trop courte
//En cas d'erreur, la valeur 99 est retournée.
//---------------------------------------------------------------------------------
int MyKeypad::getKey(int debounceLimit) {
	unsigned long topchrono = millis();
	MYanswer = int(analogRead(MYinputPin) / MYbinSize);
	while (millis() - topchrono < debounceLimit) {}
	if (int(analogRead(MYinputPin) / MYbinSize) == MYanswer) return MYanswer;
	else                                                     return 99;
}//--------------------------------------------------------------------------------

//getKeyAndWaitForRelease()========================================================
//Comme « getKey() », mais attend que l'interrupteur soit fermé avant de retourner
//---------------------------------------------------------------------------------
int MyKeypad::getKeyAndWaitForRelease() {
	  unsigned long topchrono = millis();
	  MYanswer = int(analogRead(MYinputPin) / MYbinSize);
	  while (millis() - topchrono < MYdebounceLimit) {}
	  if (int(analogRead(MYinputPin) / MYbinSize) != MYanswer) MYanswer = 99;
	  while (analogRead(MYinputPin) < 1000) {}
	  return int(MYanswer);
}//---------------------------------------------------------------------------------

//nearestResistor(double)=====================================================================
//Retourne la valeur de la résistance de la série E12 la plus proche de la cible
//--------------------------------------------------------------------------------------------
double MyKeypad::nearestResistor(double target) {
	double realValues[12] = { 1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2 };
	double lowestDifference = 9999999999.0;
	double chosenValue;
	for (double powerOfTen = 1; powerOfTen < 1000000000.0; powerOfTen *= 10.0) {
		for (int j = 0; j < 12; j++) {
			double thisResistor = realValues[j] * powerOfTen;
			if (abs(thisResistor - target) < lowestDifference) {
				lowestDifference = abs(thisResistor - target);
				chosenValue = thisResistor;
			}
		}
	}
	return chosenValue;
}//-------------------------------------------------------------------------------------------

//calculateResistorValues()===================================================================
//Place dans MYresistors[16] la valeur des résistances du montage
//Cette version fait les calculs avec une résistance de rappel de 10 KOhms
//(voir : http://electronicdesign.com/components/one-pin-keypad-features-low-component-count)
//--------------------------------------------------------------------------------------------
void MyKeypad::calculateResistorsValues() {
	double resolution = 1024.0;
	double pullup = 10000.0;
	double binSize = resolution / MYbuttonCount;
	double targetCenter = binSize / 2;
	double targetResistor = (targetCenter * pullup) / (resolution - targetCenter);
	for (int i = 0; i < MYbuttonCount; i++) {
		MYresistors[i] = nearestResistor(targetResistor);
		targetCenter += binSize;
		targetResistor = (targetCenter * pullup) / (resolution - targetCenter);
	}
}//-----------------------------------------------------------------------------------

//calculateResistorValues(double)=============================================================
//Place dans MYresistors[16] la valeur des résistances du montage
//Cette version fait les calculs avec une résistance de rappel fournie en argument
//--------------------------------------------------------------------------------------------
void MyKeypad::calculateResistorsValues(double pullup) {
	MYpullup = nearestResistor(pullup);
	double resolution = 1024.0;
	double binSize = resolution / MYbuttonCount;
	double targetCenter = binSize / 2;
	double targetResistor = (targetCenter * MYpullup) / (resolution - targetCenter);
	for (int i = 0; i < MYbuttonCount; i++) {
		MYresistors[i] = nearestResistor(targetResistor);
		targetCenter += binSize;
		targetResistor = (targetCenter * MYpullup) / (resolution - targetCenter);
	}
}//----------------------------------------------------------------------------------------------

//getResistorValue(int)============================
//Retourne la ième valeur de résitance du montage
//-------------------------------------------------
double MyKeypad::getResistorValue(int i) {
	return MYresistors[i];
}//------------------------------------------------

//getReealPullup()===============================
//Retourne la valeur de résitance de rappel
//réelle utilisée pour les calculs
//------------------------------------------------
double MyKeypad::getRealPullup() {
	return MYpullup;
}//-----------------------------------------------