/* FILE:    SmartLCD_Custom_Character_Animation_Example
   DATE:    12/07/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies
   
24/05/17 version 0.1: Original version

Uses the SmartLCD library animate one of the custom characters.

 
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


// Battery icon bitmaps for each charge state
byte Battery[6][8] = {{0x0E,0x1F,0x11,0x11,0x11,0x11,0x11,0x1F},  // 0%
                      {0x0E,0x1F,0x11,0x11,0x11,0x11,0x1F,0x1F},  // 20%
                      {0x0E,0x1F,0x11,0x11,0x11,0x1F,0x1F,0x1F},  // 40%
                      {0x0E,0x1F,0x11,0x11,0x1F,0x1F,0x1F,0x1F},  // 60%
                      {0x0E,0x1F,0x11,0x1F,0x1F,0x1F,0x1F,0x1F},  // 80%
                      {0x0E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}}; // 100%


void setup() 
{
  SmartLCD.init();                    //Initiliases the library

  SmartLCD.Clear();                   //Clear the screen
  SmartLCD.Print("Charging: ");       //Print something
  
  // Write the 0% charge icon to custom character 0 and print it to the screen
  SmartLCD.DefCustChar(0, Battery[0]);
  SmartLCD.CurPos(0, 10);
  SmartLCD.PrintCustChar(0);
  
}


void loop()                 
{
  // Loop through each icon bitmap and write it to custom character 0.
  // Custom character 0 is already printed to the screen will automatically 
  // update so no need to reprint it.
  for(byte i = 0; i <= 5; i++)
  {
    SmartLCD.DefCustChar(0, Battery[i]);
  
    delay(500);
  }
}
