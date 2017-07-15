/* FILE:    SmartLCD_Custom_Character_Example
   DATE:    12/07/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies
   
24/05/17 version 0.1: Original version

Uses the SmartLCD library to write bitmap icons to the 8 custom characters and then
prints them to the screen.
 

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


//Bitmaps for each custom character
byte Battery[] =        {0x0E,0x1F,0x11,0x11,0x11,0x11,0x11,0x1F};
byte LeftArrow[] =      {0x00,0x04,0x0C,0x1F,0x0C,0x04,0x00,0x00};
byte UpArrow[] =        {0x04,0x0E,0x1F,0x04,0x04,0x04,0x04,0x04};
byte DownArrow[] =      {0x04,0x04,0x04,0x04,0x04,0x1F,0x0E,0x04};
byte RightArrow[] =     {0x00,0x04,0x06,0x1F,0x06,0x04,0x00,0x00};
byte PadLockLocked[] =  {0x0E,0x11,0x11,0x1F,0x1B,0x1B,0x1F, 0x00};
byte PadLockOpen[] =    {0x0E,0x10,0x10,0x1F,0x1B,0x1B,0x1F, 0x00};
byte Ohmega[] =         {0x0,0x0E,0x11,0x11,0x11,0x0A,0x1B, 0x00};



void setup() 
{
  SmartLCD.init();                    //Initiliases the library

  SmartLCD.Clear();                   //Clear the screen
  
  SmartLCD.Print("Custom graphics:"); //Print something
  
  //Write the bitmap data to the 8 custom characters
  SmartLCD.DefCustChar(0, Battery);
  SmartLCD.DefCustChar(1, LeftArrow);
  SmartLCD.DefCustChar(2, UpArrow);
  SmartLCD.DefCustChar(3, DownArrow);
  SmartLCD.DefCustChar(4, RightArrow);
  SmartLCD.DefCustChar(5, PadLockLocked);
  SmartLCD.DefCustChar(6, PadLockOpen);
  SmartLCD.DefCustChar(7, Ohmega);
}


void loop()                 
{
  SmartLCD.CurPos(1, 4);            //Set the cursor to row 1 column 4

  //Print the 8 custom characters to the screen
  SmartLCD.PrintCustChar(0);        
  SmartLCD.PrintCustChar(1);        
  SmartLCD.PrintCustChar(2);
  SmartLCD.PrintCustChar(3);
  SmartLCD.PrintCustChar(4);
  SmartLCD.PrintCustChar(5);
  SmartLCD.PrintCustChar(6);
  SmartLCD.PrintCustChar(7);
  
  while(1);                         //Do nothing
}

