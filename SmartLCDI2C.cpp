/* FILE:    SMARTLCDI2C.cpp
   DATE:    26/04/22
   VERSION: 0.3
   AUTHOR:  Andrew Davies
   WEBSITE: HobbyComponents.com

12/07/17 version 0.1: 	Original version
04/02/22 version 0.2: 	Added new example (SmartLCD_Custom_Character_Example2) to show how to use existing public domain characters. Thanks to Håkon Løvdal.
			Fixed issue that cause compiler error when passing a char array to some functions.  Thanks to Håkon Løvdal.
			Fixed an invalid token name for note NOTE_AS.  Thanks to Håkon Løvdal.
			Added type case to requestFrom to fix compiler error. Thanks to Håkon Løvdal.
26/04/22 version 0.3:	Added option to print floating point numbers via the Print() function.

Arduino I2C library for the Hobby Components Smart LCD.
Products currently supported by this library:

Hobby Components 1602 Smart LCD (HCMODU0122) available from hobbycomponents.com

Optional:

Hobby Components SmartLCD Keypad kit (HCKITS0058)

More information about this library can be found in the software section of our support
forum here:

http://forum.hobbycomponents.com/software

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


#include "SmartLCDI2C.h"

/* Smart LCD I2C commands */
#define	I2CPRINTCHAR 	0
#define	I2CCLEAR 		1
#define I2CCURPOS 		2
#define I2CDISPLAYSTATE	3
#define I2CDISPLAYCUR	4
#define I2CCURBLINK		5
#define I2CBACKLIGHT	6
#define I2CPRINTCUSTOM	7
#define I2CDEFINECUSTOM	8
#define I2CCURDIR		9
#define I2CINIT			10
#define I2CCLEARBUTTON	11
#define I2CPLAYNOTE		12
#define I2CADDRESS		13
#define I2CCONTRAST		14
#define I2CVERSION		15
#define I2CCLEARERROR	251


/* I2C Constructor to initialise the library where:

   I2C_Add is the I2C address of the SmartLCD.
		Valid values for I2C_Add are 0x08 to 0x77 (default = 0x27)
*/
SmartLCD::SmartLCD(uint8_t I2C_Add)
{
	//Save the I2C address
	_I2C_Add = I2C_Add;
}


/* Initialises the Arduino wire library - Nothing to set up for the LCD! */
void SmartLCD::init(void)
{
	//Initiliase the I2C interface
	Wire.begin();
}



/* Prints a single ASCII character to the screen where:
		Character is the ASCII encoded character to print
*/
void SmartLCD::PrintChar(char Character)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CPRINTCHAR);
	Wire.write(Character);
	Wire.endTransmission();
	while(Busy());
}



/* Prints a string of ASCII text to the screen where:
		String is an ASCII string with null terminator containing the text to print
*/
void SmartLCD::Print(const char *String)
{
	uint8_t i = 0;

	while(String[i] != '\0')
	{
		PrintChar(String[i]);
		i++;
	}
}



/* Prints a signed integer number to the screen where:
		Value is the signed integer to print
*/
void SmartLCD::Print(int Value)
{
	char buffer[12];

	itoa(Value,buffer,10);
	Print(buffer);
}



/* Prints a floating point number to the screen where:
		val is the floating point number to print
		dp is the number of decimal places to print to
*/
void SmartLCD::Print(float val, uint8_t dp = 0)
{
	char buffer[20];
	if(dp > 10)
		dp = 10;

	dtostrf(val, 0, dp, buffer);
	
	Print(buffer);
}




/* Clears the screen of any printed text and positions the cursor to row 0,
   column 0 (top left hand corner)
*/
void SmartLCD::Clear(void)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CCLEAR);
	Wire.endTransmission();
	while(Busy());
}



/* Positions the cursor on the screen where:
		Row is the text row number - valid values are 0 to 4 (only 0 to 1 visible on 1602 version)

		Col is the text column number - valid values are 0 to 79 (only 0 to 15 visible on 1602 version)
*/
void SmartLCD::CurPos(uint8_t Row, uint8_t Col)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CCURPOS);
	Wire.write(Row);
	Wire.write(Col);
	Wire.endTransmission();
	while(Busy());
}



/* Turns the LCD on or off where:
		State is required state to set the screen to. Valid values are
		OFF (screen is turned off)
		ON 	(screen is turned on)

	Note that any text on the screen and the backlight state are not affected.
*/
void SmartLCD::DispState(uint8_t State)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CDISPLAYSTATE);
	Wire.write(State);
	Wire.endTransmission();
	while(Busy());
}



/* Turns the cursor on or off where:
		State is required state to set the cursor to. Valid values are
		OFF (cursor is turned off)
		ON 	(cursor is turned on)
*/
void SmartLCD::DispCursor(uint8_t State)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CDISPLAYCUR);
	Wire.write(State);
	Wire.endTransmission();
	while(Busy());
}



/* Turns cursor blinking on or off where:
		State is required state to set the cursor blink to. Valid values are
		OFF (cursor blinking is turned off)
		ON 	(cursor blinking is turned on)
*/
void SmartLCD::CursorBlink(uint8_t State)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CCURBLINK);
	Wire.write(State);
	Wire.endTransmission();
	while(Busy());
}



/* Sets the brightness level for the back light where:
		Level is the required brightness in 10% increments. Valid values are
		0 (off) to 10 (100%)
*/
void SmartLCD::Backlight(uint8_t Level)
{
	if(Level > 10)
		Level = 10;
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CBACKLIGHT);
	Wire.write(Level);
	Wire.endTransmission();
}



/* Prints one of the 8 custom characters to the screen where:
		CharIndex specifies which custom character (0 to 7) to print.
*/

void SmartLCD::PrintCustChar(uint8_t CharIndex)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CPRINTCUSTOM);
	Wire.write(CharIndex);
	Wire.endTransmission();
	while(Busy());
}



/* Defines one of the 8 custom characters by writing a 5x8 pixel bitmap to it where:
		CharIndex specifies which custom character (0 to 7) to write the bitmap to.

		Data is an 8 byte array containing the bitmap data.

	See the Smart LCD manual for more information on bitmap format.

	Note after issuing this function you must reposition the cursor before printing any text
	using the SmartLCD.CurPos(Row, Col) function.
*/
void SmartLCD::DefCustChar(uint8_t CharIndex, const uint8_t *Data)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CDEFINECUSTOM);
	Wire.write(CharIndex);
	Wire.write(Data[0]);
	Wire.write(Data[1]);
	Wire.write(Data[2]);
	Wire.write(Data[3]);
	Wire.write(Data[4]);
	Wire.write(Data[5]);
	Wire.write(Data[6]);
	Wire.write(Data[7]);
	Wire.endTransmission();
	while(Busy());
}



/* Sets which direction the cursor will move when printing text where:
		Dir is the direction the cursor will move. Valid values are
		LTOR - cursor will move from left to right
		RTOL - cursor will move from right to left
*/
void SmartLCD::CursorDir(uint8_t Dir)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CCURDIR);
	Wire.write(Dir);
	Wire.endTransmission();
	while(Busy());
}



/* Initialises the LCD setting it to its default power on state. If the
   backlight was off it will also be set to the default on state. */
void SmartLCD::I2CInit(void)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CINIT);
	Wire.endTransmission();
	while(Busy());
}



/* Clears the last button pressed state by reseting it to 0 */
void SmartLCD::ClearButton(void)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CCLEARBUTTON);
	Wire.endTransmission();
	while(Busy());
}



/* Plays one of 12 musical notes for a specified duration where:
		Note is which of the 12 notes to play (0 to 11). Predefined values for note:
		NOTE_C			0
		NOTE_CS			1
		NOTE_D			2
		NOTE_DS			3
		NOTE_E			4
		NOTE_F			5
		NOTE_FS			6
		NOTE_G			7
		NOTE_GS			8
		NOTE_A			9
		NOTE_AS			10
		NOTE_B			11

		Time is the duration of the note in 10ms increments (1 = 10ms to 255 = 2.55s)

   Note: Requires the optional keypad and speaker accessory to be connected to
   the Smart LCD.

   This command is none blocking - i.e. it will not wait for the note to finish playing.
*/
void SmartLCD::PlayNote(uint8_t Note, uint8_t Time)
{
	if(Note > 11)
		Note = 11;
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CPLAYNOTE);
	Wire.write(Note);
	Wire.write(Time);
	Wire.endTransmission();
	while(Busy());
}



/* Changes the I2C slave address for the Smart LCD where:
		Address is the new I2C address. Valid values are
		0x08 to 0x77 (default =0x27)

   Note: Once this command is issued the display will immediately respond to
   commands sent to the new slave address and will no longer respond to the
   original address. This command will also update the current I2C address
   stored within the library so you can continue to issue commands without
   needing to re-initialise the library.
*/
void SmartLCD::Address(uint8_t Address)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CADDRESS);
	Wire.write(Address);
	Wire.endTransmission();

	_I2C_Add = Address;
	while(Busy());
}



/* Sets the contrast level of the screen where:
		Level is the required contrast level. Valid values are
		0 (maximum contrast) to 255 (minimum contrast).
*/
void SmartLCD::Contrast(uint8_t Level)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CCONTRAST);
	Wire.write(Level);
	Wire.endTransmission();
	while(Busy());
}



/* Shows the version of firmware flashed into the Smart LCD by displaying it to
   the LCD.
*/
void SmartLCD::Version(void)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CVERSION);
	Wire.endTransmission();
	while(Busy());
}



/* Clears the error flag in the status register */
void SmartLCD::ClearError(void)
{
	Wire.beginTransmission(_I2C_Add);
	Wire.write(I2CCLEARERROR);
	Wire.endTransmission();
	while(Busy());
}



/* Draws a horizontal wait bar to the screen where:
		Row is the text row number to position the wait bar.

		Col is the text col number to position the left side of the wait bar.

		Length is the length in characters of the wait bar

		Percent specifies what part of the wait bar to fill in percent (0 to 100)
*/
void SmartLCD::WaitBar(uint8_t Row, uint8_t Col, uint8_t Length, uint8_t Percent)
{
	uint8_t WaitBarEnd[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	uint16_t Scale = ((Length * 5) * Percent) / 100;

	//First draw any full character blocks
	CurPos(Row, Col);
	do
	{
		if(Scale >= 5)
		{
			PrintChar(0xFF);
			Scale -= 5;
			Col++;
		}
	}while(Scale >= 5);

	/* For the last character block it may only be partially filled so use a
	   custom character and draw the last filled columns within the character */
	if(Scale)
	{
		do
		{
			Scale--;

			for(uint8_t CharRow = 0; CharRow < 8; CharRow++)
				WaitBarEnd[CharRow] |=  0x10 >> Scale;

		}while(Scale);

		DefCustChar(7, WaitBarEnd);
		CurPos(Row, Col);
		PrintCustChar(7);
	}
}



/* Returns the busy status flag where
   false = SmartLCD is not busy and can accept new commands
   true = SmartLCD is busy and cannot accept new commands

   Note that all the functions within this library use the busy command and
   will not finish executing until the SmartLCD has finished processing the
   current command. Therefore you do not need to use this function to check
   if it is ok to send another command when using the functions within this
   library.
*/
boolean SmartLCD::Busy(void)
{
	return Status() & STATUS_BUSY;
}



/* Returns the command error flag where
   false = Last command executed without error
   true = There was an error with executing or receiving the last command.

   Note that if the error flag is set it will not automatically clear. Therefore
   you must clear the flag using the SmartLCD.ClearError() function.
*/
boolean SmartLCD::Error(void)
{
	return Status() & STATUS_ERROR;
}



/* Returns the keypad button pressed status where
   false = No buttons are currently pressed on the external keypad.
   true = A button on the external keypad is currently being pressed.

   Note: Requires the optional keypad and speaker accessory to be connected to
   the Smart LCD.
*/
boolean SmartLCD::ButtonState(void)
{
	return Status() & STATUS_BPS;
}



/* Returns the last button number to be pressed on the external keypad where
		KEYPAD_NONE 	= No buttons have been pressed
		KEYPAD_BACK 	= The back button has been pressed
		KEYPAD_SELECT 	= The select button has been pressed
		KEYPAD_DOWN 	= The down button has been pressed
		KEYPAD_RIGHT	= The right button has been pressed
		KEYPAD_UP 		= The up button has been pressed
		KEYPAD_LEFT 	= The left button has been pressed


	After reading the button state the current status can been cleared by
	issuing the SmartLCD.ClearButton() function.

	Note: Requires the optional keypad and speaker accessory to be connected to
	the Smart LCD
*/
uint8_t	SmartLCD::Button(void)
{
	return Status() & STATUS_BUTTON;
}



/* Returns an 8 bit byte representing the state of the 8 bit ADC connected
   to the 'S' pin of the keypad header where:
   0 = 0V (GND) and 255 = 5V (VCC)

   Note this pin is used by the SmartLCD keypad for button sensing but if the
   SmartLCD keypad is not required this pin can be used as an 8 bit ADC input
   (5V max).
*/
uint8_t SmartLCD::ReadADC(void)
{
	uint8_t Data = 0;

	Wire.requestFrom(_I2C_Add, (uint8_t)2);
	while (Wire.available())
	{
		Data = Wire.read();
	}
	return Data;
}


/* Returns an 8 bit byte containing the current state from the I2C status register.
   See SmartLCD manual for an explanation of the I2C status register
*/
uint8_t SmartLCD::Status(void)
{
	uint8_t Data = 0;

	Wire.requestFrom(_I2C_Add, (uint8_t)1);
	while (Wire.available())
	{
		Data = Wire.read();
	}
	return Data;
}
