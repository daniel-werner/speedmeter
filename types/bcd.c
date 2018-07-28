/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <types/bcd.h>
#include <math.h>
#include <string.h>

/*----------------------------------------------------------------------------*/

#define MAX_BCD_LENGTH 6
#define ZERO_CHAR_OFFSET 0x30

#define num2char( num )(u8_t)(num + ZERO_CHAR_OFFSET)
#define char2num( num )(u8_t)(num - ZERO_CHAR_OFFSET)

static const u32_t powOfTen[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 };
static char chars[MAX_BCD_LENGTH];

/*----------------------------------------------------------------------------*/

String int2bcd( i_t number, u8_t length, bool_t zeroFill, u8_t dividePlaces, u8_t decimalPlaces )
{
	memset( chars, 0, MAX_BCD_LENGTH );
	String bcd;
	i_t tmpNumber = number;
	u8_t decimalPointPlace = 0;	
	u8_t count = length;
	u8_t bcdLength = length; 
	
	decimalPointPlace = bcdLength;
	
	if( decimalPlaces > 0 )
	{
		bcdLength++;
		decimalPointPlace = bcdLength - decimalPlaces - 1;
	}
	u8_t currentPlace = 0;
	
	if( decimalPlaces > 0 )
	{
		chars[decimalPointPlace] = '.';
	}
	while( count-- )
	{
		u32_t place = powOfTen[count + dividePlaces];
		currentPlace = length - count - 1;
		if( decimalPointPlace > 0 && currentPlace == decimalPointPlace )
		{
			currentPlace++;
		}
		if( place > number && !zeroFill && currentPlace != (bcdLength - 1) && currentPlace < (decimalPointPlace - 1) )
		{
			chars[currentPlace] = NULL;
		}
		else
		{		
			u8_t countPlace = 0;
			while (tmpNumber >= place )
			{
				countPlace++;
				tmpNumber -= place;
			}
			chars[currentPlace] = num2char( countPlace );	
		}
	}		
		
	String_ctor( &bcd, chars, bcdLength );
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

i_t changeBcdNumber( i_t number, u8_t length, u8_t position, i_t change, i_t maxNumber )
{
	i_t place = powOfTen[length - position - 1];
	if( ( change > 0 ) && ( number + place * change < powOfTen[length] ) && ( number + place * change <= maxNumber ))
	{
		number += place * change;
	}
	else if( ( change < 0 ) && ( number + place * change >= 0 ) )
	{
		number += place * change;		
	}
		
	return number;
}
