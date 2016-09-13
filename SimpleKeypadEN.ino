/*  CREDITS
 *  SimpleKeypad : Example for the MyKeypad 
 *  Created by : Jacques Bellavance, june 25, 2016
 *  This code is public domain
 */ 

/*  CONNEXIONS
 *  MyKeypad allows us to use up to 16 switches 
 *  connected to an analog pin on the Arduino.
 *  +5V-----Rpullup-----+--------+-------+--- ... ---+-----A10
 *                     1nF      SW0     SW1   ...   SWn
 *                     CAP      R0      R1    ...   Rn
 *  GND-----------------+--------+-------+--- ... ---+
 *
 * Pullup actual value 10000 Ohms : 
 * R0 = 1.2 KOhms
 * R1 = 3.9 KOhms
 * R2 = 10.0 KOhms
 * R3 = 22.0 KOhms
 * R4 = 82.0 KOhms
 */

/* METHODS
 * boolean keyPressed()          retrns true if any switch is cloded
 * int getKey()                  Return the id af the closed switch, debounce of 50ms.
 * int getKey(debounceLimit)     Allows to specify the debounce duration (in milliseconds). 
 * int getKeyAndWaitForRelease() Same a getKey(), but waits until the switch is depressed before sending the switch's id
 */

#include <MyKeypad.h>;

//CONSTRUCTOR===========================
int inputPin = A12;
int buttonCount = 5;
MyKeypad keypad(inputPin,buttonCount);
//---------------------------------------

void setup() {
Serial.begin(9600);
}

void loop() {
  if (keypad.keyPressed()) {
    int key = keypad.getKeyAndWaitForRelease(); // or : int key = keypad.getKey();
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
