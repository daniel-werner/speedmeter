/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <timer/date.h>
#include <types/string.h>
#include <types/bcd.h>
#include <string.h>

/*----------------------------------------------------------------------------*/

#define START_YEAR 2008
#define LEAP_YEAR 2012

#define DAYS_OF_YEAR 365
#define DAYS_OF_LEAP_YEAR 366


static const u8_t monthLength[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void Date_ctor( Date* self )
{
}

/*----------------------------------------------------------------------------*/

static char dateChars[10] = { ' ',' ',' ',' ','.',' ',' ','.',' ',' ' };

String Date_to_string( Date* self )
{
	String timeStr;
	String strTmp;
	
	String_ctor( &timeStr, dateChars, sizeof( dateChars ) );
	
	strTmp = int2bcd( self->year, 4, FALSE, 0, 0);
	memcpy( dateChars, strTmp.chars, 4 * sizeof( char ) );
	strTmp = int2bcd( self->month, 2, TRUE, 0, 0);
	memcpy( &dateChars[5], strTmp.chars, 2 * sizeof( char ) );
	strTmp = int2bcd( self->day, 2, TRUE, 0, 0);
	memcpy( &dateChars[8], strTmp.chars, 2 * sizeof( char ) );	
	
	return timeStr;
}

/*----------------------------------------------------------------------------*/

#define is_leap_year( year )( ( year - START_YEAR ) % 4 == 0 )

/*----------------------------------------------------------------------------*/

u8_t Date_get_months_day_number( year_t year, month_t month )
{
	u8_t dayNumber = monthLength[month];
	if( is_leap_year( year ) && month == 2 )
	{
		dayNumber++;
	}
	
	return dayNumber;
}

/*----------------------------------------------------------------------------*/

bool_t Date_validate_and_correct( Date* self )
{
	bool_t retVal = TRUE;
	day_t maxDayNumber = Date_get_months_day_number( self->year, self->month );
	
	if( self->day > maxDayNumber )
	{
		self->day = maxDayNumber;
		retVal = FALSE;
	}
	
	return retVal;
}

/*----------------------------------------------------------------------------*/

bool_t Date_from_number( Date* self )
{
	u16_t countElapsedDays = 0;
	year_t year = START_YEAR;
	month_t month = 0;
	u16_t daysOfyear = DAYS_OF_LEAP_YEAR;
	
	while( countElapsedDays < self->elapsedDays )
	{
		daysOfyear = ( is_leap_year(year) ) ? DAYS_OF_LEAP_YEAR : DAYS_OF_YEAR;		
		countElapsedDays += daysOfyear;
		year++;
	}
	year--;
	countElapsedDays -= daysOfyear;
	
	u16_t elapsedDaysInYear = year > START_YEAR ? self->elapsedDays - countElapsedDays : self->elapsedDays;
	u16_t countElapsedDaysInYear = 0;
	
	for( month_t i = 1; i <= 12; i++ )
	{
		u8_t tempMonthLength = monthLength[i];
		if( i == 2 && ( is_leap_year(year) ) )
		{
			tempMonthLength++;
		}		
		countElapsedDaysInYear += tempMonthLength;
		if( countElapsedDaysInYear >= elapsedDaysInYear )
		{
			month = i;
			countElapsedDaysInYear -= tempMonthLength;
			break;
		}
	}

	day_t day = elapsedDaysInYear - countElapsedDaysInYear;
	
	if( day == 0 )
		day++;
	
	self->year = year;
	self->month = month;
	self->day = day;
	
	return TRUE;
}

/*----------------------------------------------------------------------------*/

u16_t Date_to_number( Date* self )
{
	Date_validate_and_correct( self );
	u16_t countElapsedDays = 0;
	u16_t daysOfyear = DAYS_OF_LEAP_YEAR;
	
	for( year_t year = START_YEAR; year < self->year; year++ )
	{
		daysOfyear = ( is_leap_year(year) ) ? DAYS_OF_LEAP_YEAR : DAYS_OF_YEAR;		
		countElapsedDays += daysOfyear;
	}


	for( month_t i = 1; i < self->month; i++ )
	{
		u8_t tempMonthLength = monthLength[i];
		if( i == 2 && ( is_leap_year(self->year) ) )
		{
			tempMonthLength++;
		}		
		countElapsedDays += tempMonthLength;
	}

	countElapsedDays += self->day;
	
	return countElapsedDays;
}

/*----------------------------------------------------------------------------*/

bool_t Date_tick( Date* self )
{
	self->elapsedDays++;
	Date_from_number( self );
//	bool_t retVal = FALSE;
//	self->seconds++;
//	if( self->seconds > 59 )
//	{
//		self->seconds = 0;
//		self->minutes++;
//		retVal = TRUE;
//		if( self->minutes > 59 )
//		{
//			self->minutes = 0;
//			self->hours++;
//			if( self->hours > 23 )
//			{
//				self->hours = 0;
//			}
//		}
//	}
	
	return TRUE;
}
