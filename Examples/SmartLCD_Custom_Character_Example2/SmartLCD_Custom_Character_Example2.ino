/*
   FILE:    SmartLCD_Custom_Character_Example2
   DATE:    2018-11-29
   VERSION: 0.1
   AUTHOR:  Håkon Løvdal

2018-11-29 version 0.1: Original version based on copy of SmartLCD_Custom_Character_Example

This file is basically the same as SmartLCD_Custom_Character_Example.ino,
only that this shows how to easily reuse existing public domain 5x8 character
font definitions so you do not have to design your own.


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



// Bitmaps copied from
// https://github.com/olikraus/u8g2/blob/master/tools/font/bdf/5x8.bdf
// COPYRIGHT "Public domain font.  Share and enjoy."

// To make cut and paste from BDF as simple as possible this macro allows
// the "raw", unprefixed hex values from BDF to be entered directly and
// just adds the "0x" prefix internally.
// Difference in bit ordering: BDF uses the 5 highest bits, SmartLCD uses
// the lowest 5 bits. Hence the 3 bit shift.
#define BDF_VALUES(v1, v2, v3, v4, v5, v6, v7, v8) \
	(0x##v1)>>3, \
	(0x##v2)>>3, \
	(0x##v3)>>3, \
	(0x##v4)>>3, \
	(0x##v5)>>3, \
	(0x##v6)>>3, \
	(0x##v7)>>3, \
	(0x##v8)>>3

static const byte Bitmap_Omega[]     = { BDF_VALUES( 00, 70, 88, 88, 88, 50, D8, 00 ) };
static const byte Bitmap_degree[]    = { BDF_VALUES( 00, 20, 50, 20, 00, 00, 00, 00 ) };
static const byte Bitmap_plusminus[] = { BDF_VALUES( 00, 00, 20, 70, 20, 00, 70, 00 ) };
static const byte Bitmap_mu[]        = { BDF_VALUES( 00, 00, 00, 90, 90, 90, E0, 80 ) };
static const byte Bitmap_Oslash[]    = { BDF_VALUES( 00, 70, B0, B0, D0, D0, E0, 00 ) };

enum CustChar {
	CUST_CHAR_Omega,
	CUST_CHAR_degree,
	CUST_CHAR_plusminus,
	CUST_CHAR_mu,
	CUST_CHAR_Oslash,
	////////////////////////////////
	CUST_CHAR_LAST_DUMMY_ENTRY
};
static_assert(CUST_CHAR_LAST_DUMMY_ENTRY < 8, "SmartLCD supports a maximum of 8 custom characters");

void setup()
{
  SmartLCD.init();                    //Initiliases the library

  SmartLCD.Clear();                   //Clear the screen

  //Write the bitmap data to the custom characters

  SmartLCD.DefCustChar(CUST_CHAR_Omega, Bitmap_Omega);
  SmartLCD.DefCustChar(CUST_CHAR_degree, Bitmap_degree);
  SmartLCD.DefCustChar(CUST_CHAR_plusminus, Bitmap_plusminus);
  SmartLCD.DefCustChar(CUST_CHAR_mu, Bitmap_mu);
  SmartLCD.DefCustChar(CUST_CHAR_Oslash, Bitmap_Oslash);
}


void loop()
{
  SmartLCD.CurPos(0, 0);            //Set the cursor to row 0 column 0

  // "Øresund bridge"
  SmartLCD.PrintCustChar(CUST_CHAR_Oslash);
  SmartLCD.Print("resund bridge");

  SmartLCD.CurPos(1, 0);            //Set the cursor to row 1 column 0


  // "T=23°C±2% R1=1kΩ"
  SmartLCD.Print("T=23");
  SmartLCD.PrintCustChar(CUST_CHAR_degree);
  SmartLCD.Print("C");
  SmartLCD.PrintCustChar(CUST_CHAR_plusminus);
  SmartLCD.Print("2% R1=1k");
  SmartLCD.PrintCustChar(CUST_CHAR_Omega);

  while(1);                         //Do nothing
}
