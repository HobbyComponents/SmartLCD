/* FILE:    SmartLCD_System_Up_Time_Example
   DATE:    12/07/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies
   
24/05/17 version 0.1: Original version

Uses the SmartLCD library to display the current system up time in seconds
 

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


#include "SmartLCDI2C.h"          //Include the SmartLCD I2C Library

#define I2C_ADD 0x27              //I2C address of the Smart LCD

SmartLCD SmartLCD(I2C_ADD);       //Create an instance of the library



void setup() 
{
  SmartLCD.init();                //Initiliases the library
}



void loop()                 
{
  unsigned long time;
  
  SmartLCD.Clear();               //Clear the screen
  
  SmartLCD.CurPos(0, 2);          //Set the cursor to row 0 column 2
  SmartLCD.Print("System Time:"); //Print some text


  while(1)
  {
    Time = millis();              //Get the current system time in milliseconds
    SmartLCD.CurPos(1, 4);        //Set the cursor to row 1 column 4
    SmartLCD.Print(Time / 1000);  //Print the time in seconds
    SmartLCD.Print(".");          //Print a DP then print the fractional part in milliseconds

    if(Time % 1000 < 100)         //If is less than 100 milliseconds first pad with a 0   
      SmartLCD.Print("0");
    if(Time % 1000 < 10)          //If is less than 10 milliseconds then pad with another 0 
      SmartLCD.Print("0");
    
    SmartLCD.Print(time % 1000);  //Then print the fractional part

    delay(1);                     //Don't do anything for another millisecond
  }

}
