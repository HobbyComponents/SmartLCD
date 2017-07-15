/* FILE:    SmartLCD_Wait_Bar_Example
   DATE:    12/07/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies
   
24/05/17 version 0.1: Original version

Uses the SmartLCD library to draw a wait bar on the screen
 

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


#include "SmartLCDI2C.h"                //Include the SmartLCD I2C Library

#define I2C_ADD 0x27                    //I2C address of the Smart LCD

SmartLCD SmartLCD(I2C_ADD);             //Create an instance of the library



void setup() 
{
  SmartLCD.init();                      //Initiliases the library
}

void loop() 
{
  SmartLCD.Clear();                     //Clear the screen

  SmartLCD.Print("Please wait:");       //Print some text

  /* Step from 0 to 100% and draw the wait bar for each step */
  for(byte Percent = 0; Percent <= 100; Percent++)
  {
    SmartLCD.CurPos(0, 12);             //Set the cursor to row 0 column 12
    SmartLCD.Print(Percent);            //Display the current percentage
    SmartLCD.Print("%");

    // Draw the wait bar at row 1, column 0, and make it 16 characters long
    SmartLCD.WaitBar(1, 0, 16, Percent);

    delay(10);
  }

  delay(2000);
}
