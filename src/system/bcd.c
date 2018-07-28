/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <system/bcd.h>
#include <math.h>

/*----------------------------------------------------------------------------*/

#define MAX_BCD_LENGTH 4
#define ZERO_CHAR_OFFSET 0x30

#define num2char( num )(u8_t)(num + ZERO_CHAR_OFFSET)

#define char2num( num )(u8_t)(num - ZERO_CHAR_OFFSET)

static const i_t powOfTen[] = { 1, 10, 100, 1000, 10000 };
static char chars[MAX_BCD_LENGTH];

/*----------------------------------------------------------------------------*/

String int2bcd( i_t number, u8_t length )
{
	String bcd;
	
	u8_t count = length;	
	
	while( count-- )
	{
		i_t place = powOfTen[count];
		u8_t countPlace = 0;
		while (number >= place )
		{
			countPlace++;
			number -= place;
		}
		chars[length - count - 1] = num2char( countPlace );	
	}		
		
	String_ctor( &bcd, chars, length );
	return bcd;
}

/*----------------------------------------------------------------------------*/

i_t bcdString2int( String* bcd )
{

	i_t number = 0;
	u8_t count = bcd->length;	
	
	while( count-- )
	{
		i_t place = powOfTen[count];
		number += place * char2num(bcd->chars[bcd->length - count - 1]);
	}

	return number;
}

/*----------------------------------------------------------------------------*/

i_t changeBcdNumber( i_t number, u8_t length, u8_t position, i_t change )
{
	i_t place = powOfTen[length - position - 1];
	number += place * change;

	return number;
}
