/* FILE:    SmartLCD_Hello_World_Example
   DATE:    12/07/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies
   
24/05/17 version 0.1: Original version

Uses the SmartLCD library print and cursor functions to print 'Hello World !' to the 
screen.
 

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


#include "SmartLCDI2C.h"      //Include the SmartLCD I2C Library

#define I2C_ADD 0x27          //I2C address of the Smart LCD

SmartLCD SmartLCD(I2C_ADD);   //Create an instance of the library



void setup() 
{
  SmartLCD.init();            //Initiliases the library
}



void loop()                 
{
  SmartLCD.Clear();           //Clear the screen
  
  SmartLCD.CurPos(0, 5);      //Set the cursor to row 0 column 5
  SmartLCD.Print("Hello");    //Print some text
  
  SmartLCD.CurPos(1, 4);      //Set the cursor to row 1 column 4
  SmartLCD.Print("World !");  //Print some text

  while(1);                   //Do nothing
}
