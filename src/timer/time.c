/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <timer/time.h>
#include <types/string.h>
#include <types/bcd.h>
#include <string.h>

/*----------------------------------------------------------------------------*/

void Time_ctor( Time* self )
{
}

/*----------------------------------------------------------------------------*/

static char timeChars[8] = { ' ',' ',':',' ',' ',':',' ',' ' };

String Time_to_string( Time* self, bool_t seconds )
{
	String timeStr;
	String strTmp;
	
	if( seconds )
	{
		String_ctor( &timeStr, timeChars, 8 );
	}
	else
	{
		String_ctor( &timeStr, timeChars, 5 );
	}
	
	strTmp = int2bcd( self->hours, 2, FALSE, 0, 0);
	memcpy( timeChars, strTmp.chars, 2 * sizeof( char ) );
	strTmp = int2bcd( self->minutes, 2, TRUE, 0, 0);
	memcpy( &timeChars[3], strTmp.chars, 2 * sizeof( char ) );
	
	if( seconds )
	{
		strTmp = int2bcd( self->seconds, 2, TRUE, 0, 0);
		memcpy( &timeChars[6], strTmp.chars, 2 * sizeof( char ) );	
	}
	
	return timeStr;
}

/*----------------------------------------------------------------------------*/

bool_t Time_tick( Time* self )
{
	bool_t retVal = FALSE;
	self->seconds++;
	if( self->seconds > 59 )
	{
		self->seconds = 0;
		self->minutes++;
		retVal = TRUE;
		if( self->minutes > 59 )
		{
			self->minutes = 0;
			self->hours++;
			if( self->hours > 23 )
			{
				self->hours = 0;
			}
		}
	}
	
	return retVal;
}

/*----------------------------------------------------------------------------*/

bool_t Time_tick_all( AllTripTime* self )
{
	bool_t retVal = FALSE;
	self->seconds++;
	if( self->seconds > 59 )
	{
		self->seconds = 0;
		self->minutes++;
		retVal = TRUE;
		if( self->minutes > 59 )
		{
			self->minutes = 0;
			self->hours++;
			if( self->hours > 23 )
			{
				self->hours = 0;
			}
		}
	}
	
	return retVal;
}

/*----------------------------------------------------------------------------*/

u32_t Time_get_seconds( Time* self )
{
	u32_t seconds = self->hours * 3600 + self->minutes * 60 + self->seconds;
	
	return seconds;
}

/*----------------------------------------------------------------------------*/

u32_t Time_get_seconds_all( AllTripTime* self )
{
	u32_t seconds = self->hours * 3600 + self->minutes * 60 + self->seconds;
	
	return seconds;
}

/*----------------------------------------------------------------------------*/

String Time_to_string_all( AllTripTime* self, bool_t seconds )
{
	String timeStr;
	String strTmp;
	
	if( seconds )
	{
		String_ctor( &timeStr, timeChars, 8 );
	}
	else
	{
		String_ctor( &timeStr, timeChars, 5 );
	}
	
	strTmp = int2bcd( self->hours, 2, FALSE, 0, 0);
	memcpy( timeChars, strTmp.chars, 2 * sizeof( char ) );
	strTmp = int2bcd( self->minutes, 2, TRUE, 0, 0);
	memcpy( &timeChars[3], strTmp.chars, 2 * sizeof( char ) );
	
	if( seconds )
	{
		strTmp = int2bcd( self->seconds, 2, TRUE, 0, 0);
		memcpy( &timeChars[6], strTmp.chars, 2 * sizeof( char ) );	
	}
	
	return timeStr;
}