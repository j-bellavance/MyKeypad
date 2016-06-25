# MyKeypad
A small library to use voltage divider setup switches and methods to calculate resistors values.

MyKeypad allows us to use up to 16 switches connected to an analog pin on the Arduino.

if (keypad.keyPressed()) theKey = keypad.getKey();

will return the id (0..n-1) of the switch that was pressed.
