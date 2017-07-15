/* FILE:    SmartLCD_Keypad_Example
   DATE:    12/07/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies
   
24/05/17 version 0.1: Original version

This sketch requires the optional SmartLCD keypad accessory to be connected to the 
SmartLCD
 

More information about the library can be found in the software section of our support 
forum here:

http://forum.hobbycomponents.com/software


How to connect the Smart LCD to an Arduino Uno/Nano:

Uno/Nano.......SmartLCD I2C Header
GND............G (GND)
5V.............5 (5V)
A4.............D (SDA)
A5.............C (SCL)


You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used directly for the purpose of selling products that
directly compete with Hobby Components Ltd's own range of products.
THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/


#include "SmartLCDI2C.h"                  //Include the SmartLCD I2C Library

#define I2C_ADD 0x27                      //I2C address of the Smart LCD

SmartLCD SmartLCD(I2C_ADD);               //Create an instance of the library



void setup() 
{
  SmartLCD.init();                        //Initiliases the library

  SmartLCD.Clear();                       //Clear the screen

  SmartLCD.Print("Press a button..");     //Print some text

  //Play some notes through the Keypad speaker
  for(int Note = 0; Note < 12; Note++)
  {
    SmartLCD.PlayNote(Note, 50);
    delay(50);
  }
}


void loop() 
{
  //Check if a button is currently pressed
  if(SmartLCD.ButtonState() == true && SmartLCD.Button() != KEYPAD_NONE)
  {
    SmartLCD.PlayNote(NOTE_B, 10);        //If so then play a note
    SmartLCD.CurPos(1, 5);

    while(SmartLCD.ButtonState());        //Wait until button is no longer pressed
    
    switch(SmartLCD.Button())             //Print some text to show which button was pressed
    {
      case(KEYPAD_LEFT):
        SmartLCD.Print(" LEFT "); 
        break;

      case(KEYPAD_UP):
        SmartLCD.Print("  UP  "); 
        break;

      case(KEYPAD_RIGHT): 
        SmartLCD.Print("RIGHT "); 
        break;
        
      case(KEYPAD_BACK):
        SmartLCD.Print(" BACK ");
        break;

       case(KEYPAD_DOWN):
        SmartLCD.Print(" DOWN "); 
        break;
        
      case(KEYPAD_SELECT):
        SmartLCD.Print("SELECT"); 
        break;
    }

    SmartLCD.ClearButton();             //Clear the button state
  }
}
