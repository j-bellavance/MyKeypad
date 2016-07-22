/*  CREDITS
 *  ResistorValues : Example for the library MyKeypad
 *  Créé par Jacques Bellavance, june 25, 2016
 *  This code is public domain
 */ 

/*  CONNEXIONS
 *  MyKeypad allows us to use up to 16 switches 
 *  connected to an analog pin on the Arduino.
 *  +5V-----Rpullup-----+--------+-------+--- ... ---+-----A10
 *                     1nF      SW0     SW1   ...   SWn
 *                     CAP      R0      R1    ...   Rn
 *  GND-----------------+--------+-------+--- ... ---+
 */

/* INTRODUCTION
 * This sketch will display on the serial monitor
 * the values of optimal resistors for R0..Rn-1
 * analogRead() can return values from 0 to 1023.
 * For a setup of n switches, the 0..1024 range is divided in n segments.
 * The center of each segment is the target for Rn's value
 * The selected resistors are taken in the E12 series with a tolerance of +- 5%
 * (see :http://www.positron-libre.com/cours/electronique/resistances/serie-resistance.php)
 * 
 * NOTE :
 * The library is capable of dealing with a maximum of 16 switches.
 */
  
/* METHODS
 * The contructor's arguments are :
 * - Argument1 : inputPin (The analog pin on the Arduino
 * - Argument2 : buttonCount (The number of switches of the setup
 * 
 * The 'calculateResistorValues()' method can be called with or without the pullup resistor value
 * If the pullup value is ommited, 10 KOhms is used
 * 
 * The 'getResistorValue(i)' method will return the resistor value for switch i (Ri)
 * 
 * The 'getRealPullup()' method will return the real pullup resistor value used for calculations
 */

/* UTE
 * In GLOBAL VARIABLES :
 * - change « switchCount » for the number of switches in the setup
 * - change « pullup » for the value that you intend to use
 * Upload the sketch to Arduino
 * Open the Serial Monitor to obtain the values
 */

#include <MyKeypad.h>

//GLOBAL VARIABLES=======================================================
int readPin = A10;        //Broche sur laquelle est branchée le montage
int switchCount = 10;     //Nombre d'interrupteurs du montage
double pullup = 10000.0;  //Valeur de la résistance de rappel (Pullup)
//-----------------------------------------------------------------------

MyKeypad test(readPin,switchCount); //L'objet du montage est nommé « test »

//Setup()=================================================================================
void setup() {
  Serial.begin(9600);                         //Initialise the Serial Monitor
  Serial.println("Start...");                 //Start
  test.calculateResistorsValues(pullup);      //Compute the resistor values
//test.calculateResistorsValues();            //pullup = 10 KOhms
  Serial.print("Pullup actual value ");       //The real value of the pullup resistor
  Serial.print(long(test.getRealPullup()));
  Serial.println(" Ohms : ");
  for (int i=0 ; i<switchCount ; i++) {       //For each resistor
    char prefix = 'K';                          //Show the value
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
