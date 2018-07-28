/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <timer/rtc.h>
#include <timer/time.h>
#include <timer/date.h>
#include <types/string.h>
#include <types/bcd.h>
#include <string.h>
#include <setup/board.h>
#include <menu/menu_edit.h>
#include <menu/menu_states.h>
#include <gui/displayobjects/text.h>

/*----------------------------------------------------------------------------*/
Rtc* ptrRtc = NULL;
/*----------------------------------------------------------------------------*/

static void Rtc_timer_init( Rtc* self )
{
  TACCR0 = 32768;
  TACTL = TASSEL0 +  MC_1;		    // TimerA folyamatos mod, ACLK = lfxtal = 32768
  TACCTL0 |= CCIE;		            // CCTL0 ugyanaz, mint TACCTL0
}

/*----------------------------------------------------------------------------*/

void Rtc_ctor( Rtc* self )
{
	ptrRtc = self;
	Rtc_timer_init( self );
}

/*----------------------------------------------------------------------------*/

//static char clockChars[8] = { ' ',' ',':',' ',' ',':',' ',' ' };

String Rtc_to_string( Rtc* self, bool_t seconds )
{
	return Time_to_string( &self->time, seconds);
//	String clockStr;
//	String strTmp;
//	
//	if( seconds )
//	{
//		String_ctor( &clockStr, clockChars, 8 );
//	}
//	else
//	{
//		String_ctor( &clockStr, clockChars, 5 );
//	}
//	
//	strTmp = int2bcd( self->time.hours, 2, FALSE, 0, 0);
//	memcpy( clockChars, strTmp.chars, 2 * sizeof( char ) );
//	strTmp = int2bcd( self->time.minutes, 2, TRUE, 0, 0);
//	memcpy( &clockChars[3], strTmp.chars, 2 * sizeof( char ) );
//	
//	if( seconds )
//	{
//		strTmp = int2bcd( self->time.seconds, 2, TRUE, 0, 0);
//		memcpy( &clockChars[6], strTmp.chars, 2 * sizeof( char ) );	
//	}
//	
//	return clockStr;
		
}

/*----------------------------------------------------------------------------*/

Time tempTime;
MenuEdit menuEditHour;
MenuEdit menuEditMinute;
u8_t pos = 0;
String str;
Text txt;

static bool_t updateClock = FALSE;

state_t Rtc_set_time( Menu* menu, key_t input )
{
	Pixel startPoint = { 39, 32, 1 };

	if( input == KEY_NULL )
	{
		pos = 0;
		tempTime = ptrRtc->time;
		Menu_clear_text( menu );

		str = (String){STRING("Time:")};
		Text_ctor( &txt, menu->iconX + menu->iconWidth + 5, menu->iconY + 5, &str, 1, FALSE, ms_sans_serif, 11, FALSE );
		Text_draw( &txt );
		
		str = Rtc_to_string( ptrRtc, FALSE );
		Text_ctor( &txt, menu->iconX + menu->iconWidth + 5, 32, &str, 1, FALSE, ms_sans_serif, 11, FALSE );
		Text_draw( &txt );		
	}
	MenuEditCommands command;
	if( pos < 2 )
	{
		i_t number = (i_t)tempTime.hours;	
		command = MenuEdit_number( &menuEditHour, menu, &startPoint, &number, 2, 23,input, ms_sans_serif, 11);
		input = KEY_NULL;
		tempTime.hours = number;			
		if( command == MENU_EDIT_OK )
		{
			pos += 2;
		}
		else if( command == MENU_EDIT_CANCEL )
		{
			pos = 0;
		}
	}
	
	if( pos >= 2 )
	{
		//Character* ch  = Text_get_character( &txt, 3 );
		startPoint = (Pixel){ 57, 32, 1 };
		i_t number = (i_t)tempTime.minutes;	
		command = MenuEdit_number( &menuEditMinute, menu, &startPoint, &number, 2, 59, input, ms_sans_serif, 11);
		tempTime.minutes = number;			
		if( command == MENU_EDIT_OK )
		{
			pos += 2;
		}
		else if( command == MENU_EDIT_CANCEL )
		{
			pos = 1;
			startPoint = (Pixel){ 39, 32, 1 };
			i_t number = (i_t)tempTime.hours;	
			command = MenuEdit_number( &menuEditHour, menu, &startPoint, &number, 2, 23, KEY_NULL, ms_sans_serif, 11);
		}
	}
	
	state_t retVal = ST_MENU_SET_TIME_FUNC;
	switch( command )
	{
		case MENU_EDIT_CANCEL:
			if( pos <= 0 )
			{
				retVal = ST_MENU_SET_TIME;
			}
			break;
		case MENU_EDIT_OK:
			if( pos >= 3 )
			{
				pos = 0;
				menuEditHour.editPosition = 0;
				menuEditMinute.editPosition = 0;				
				retVal = ST_MENU_SET_TIME;
				tempTime.seconds = 0x00;
				TAR = 0x0000;
				ptrRtc->time = tempTime;
			}
			break;
	}
	
	if( pos <= 1 && menuEditHour.editPosition == 0 )
	{
		if( retVal != ST_MENU_SET_TIME )
		{
			Menu_draw_bottom_line( menu, BOTTOM_RIGHT_ARROW );
		}
		else
		{
			Menu_draw_bottom_line( menu, BOTTOM_ENTER_ESCAPE );
		}
	}
	else if( pos >= 2 && menuEditMinute.editPosition == 1 )
	{
		Menu_draw_bottom_line( menu, BOTTOM_LEFT_ARROW );			
	}
	else
	{
		Menu_draw_bottom_line( menu, BOTTOM_ARROWS );
	}	
	
	return retVal;
}

/*----------------------------------------------------------------------------*/

Date tempDate;
MenuEdit menuEditYear;
MenuEdit menuEditMonth;
MenuEdit menuEditDay;
u8_t posDate = 0;
//String strDate;
//Text txt;

static bool_t updateDate = FALSE;

/*----------------------------------------------------------------------------*/

state_t Rtc_set_date_custom( Rtc* self, Pixel startPoint, Menu* menu, key_t input )
{
	//Pixel startPoint = { 34, 32, 1 };

	if( input == KEY_NULL )
	{
		//pos = 0;
		tempDate = self->date;
		Menu_clear_text( menu );

		str = (String){STRING("Date:")};
		Text_ctor( &txt, menu->iconX + menu->iconWidth, menu->iconY + 5, &str, 1, FALSE, ms_sans_serif, 11, FALSE );
		Text_draw( &txt );
		
		str = Date_to_string( &self->date );
		Text_ctor( &txt, menu->iconX + menu->iconWidth, 32, &str, 1, FALSE, ms_sans_serif, 11, FALSE );
		Text_draw( &txt );		
	}
	MenuEditCommands command;
	if( pos < 4 )
	{
		i_t number = (i_t)tempDate.year;	
		command = MenuEdit_number( &menuEditYear, menu, &startPoint, &number, 4, 2100, input, ms_sans_serif, 11);
		input = KEY_NULL;
		tempDate.year = number;
		Date_validate_and_correct( &tempDate );
		if( command == MENU_EDIT_OK )
		{
			pos += 4;
		}
		else if( command == MENU_EDIT_CANCEL )
		{
			pos = 0;
		}
	}
	
	if( pos >= 4 && pos < 6 )
	{
		Character* ch  = Text_get_character( &txt, 5 );
		startPoint = (Pixel){ ch->base.position.x - 1, ch->base.position.y - 2, 1 };
		i_t number = (i_t)tempDate.month;	
		command = MenuEdit_number( &menuEditMonth, menu, &startPoint, &number, 2, 12, input, ms_sans_serif, 11);
		input = KEY_NULL;		
		tempDate.month = number;
		Date_validate_and_correct( &tempDate );		
		if( command == MENU_EDIT_OK )
		{
			pos += 2;
		}
		else if( command == MENU_EDIT_CANCEL )
		{
			pos = 0;
			startPoint = (Pixel){ 34, 32, 1 };
			i_t number = (i_t)tempDate.year;	
			command = MenuEdit_number( &menuEditYear, menu, &startPoint, &number, 4, 2100, KEY_NULL, ms_sans_serif, 11);
		}
	}
	
	if( pos >= 6 )
	{
		Character* ch  = Text_get_character( &txt, 8 );
		startPoint = (Pixel){ ch->base.position.x - 1, ch->base.position.y - 2, 1 };
		i_t number = (i_t)tempDate.day;
		u8_t dayNumber = Date_get_months_day_number( tempDate.year, tempDate.month );
		command = MenuEdit_number( &menuEditDay, menu, &startPoint, &number, 2, dayNumber, input, ms_sans_serif, 11);
		tempDate.day = number;			
		if( command == MENU_EDIT_OK )
		{
			pos += 2;
		}
		else if( command == MENU_EDIT_CANCEL )
		{
			pos = 5;
			Character* ch  = Text_get_character( &txt, 5 );
			startPoint = (Pixel){ ch->base.position.x - 1, ch->base.position.y - 2, 1 };
			i_t number = (i_t)tempDate.month;	
			command = MenuEdit_number( &menuEditMonth, menu, &startPoint, &number, 2, 12, KEY_NULL, ms_sans_serif, 11);
		}
	}	
	state_t retVal = ST_MENU_SET_DATE_FUNC;
	switch( command )
	{
		case MENU_EDIT_CANCEL:
			if( pos <= 0 )
			{
				retVal = ST_MENU_SET_DATE;
			}
			break;
		case MENU_EDIT_OK:
			if( pos >= 7 )
			{
				pos = 0;
				menuEditYear.editPosition = 0;
				menuEditMonth.editPosition = 0;				
				menuEditDay.editPosition = 0;								
				retVal = ST_MENU_SET_DATE;
				self->date = tempDate;
				self->date.elapsedDays = Date_to_number( &self->date );
			}
			break;
	}

	if( pos <= 1 && menuEditYear.editPosition == 0 )
	{
		if( retVal != ST_MENU_SET_DATE )
		{
			Menu_draw_bottom_line( menu, BOTTOM_RIGHT_ARROW );			
		}
		else
		{
			Menu_draw_bottom_line( menu, BOTTOM_ENTER_ESCAPE );	
		}
	}
	else if( pos >= 6 && menuEditDay.editPosition == 1 )
	{
		Menu_draw_bottom_line( menu, BOTTOM_LEFT_ARROW );			
	}
	else
	{
		Menu_draw_bottom_line( menu, BOTTOM_ARROWS );
	}
	
	
	return retVal;
}

/*----------------------------------------------------------------------------*/

state_t Rtc_set_date( Menu* menu, key_t input )
{
	Pixel startPoint = { 34, 32, 1 };

	return Rtc_set_date_custom( ptrRtc, startPoint, menu, input );
//	if( input == KEY_NULL )
//	{
//		//pos = 0;
//		tempDate = ptrRtc->date;
//		Menu_clear_text( menu );
//
//		str = (String){STRING("Date:")};
//		Text_ctor( &txt, menu->iconX + menu->iconWidth, menu->iconY + 5, &str, 1, FALSE, ms_sans_serif, 11, FALSE );
//		Text_draw( &txt );
//		
//		str = Date_to_string( &ptrRtc->date );
//		Text_ctor( &txt, menu->iconX + menu->iconWidth, 32, &str, 1, FALSE, ms_sans_serif, 11, FALSE );
//		Text_draw( &txt );		
//	}
//	MenuEditCommands command;
//	if( pos < 4 )
//	{
//		i_t number = (i_t)tempDate.year;	
//		command = MenuEdit_number( &menuEditYear, menu, &startPoint, &number, 4, 2100, input);
//		input = KEY_NULL;
//		tempDate.year = number;
//		Date_validate_and_correct( &tempDate );
//		if( command == MENU_EDIT_OK )
//		{
//			pos += 4;
//		}
//		else if( command == MENU_EDIT_CANCEL )
//		{
//			pos = 0;
//		}
//	}
//	
//	if( pos >= 4 && pos < 6 )
//	{
//		Character* ch  = Text_get_character( &txt, 5 );
//		startPoint = (Pixel){ ch->base.position.x - 1, ch->base.position.y - 2, 1 };
//		i_t number = (i_t)tempDate.month;	
//		command = MenuEdit_number( &menuEditMonth, menu, &startPoint, &number, 2, 12, input);
//		input = KEY_NULL;		
//		tempDate.month = number;
//		Date_validate_and_correct( &tempDate );		
//		if( command == MENU_EDIT_OK )
//		{
//			pos += 2;
//		}
//		else if( command == MENU_EDIT_CANCEL )
//		{
//			pos = 0;
//			startPoint = (Pixel){ 34, 32, 1 };
//			i_t number = (i_t)tempDate.year;	
//			command = MenuEdit_number( &menuEditYear, menu, &startPoint, &number, 4, 2100, KEY_NULL);
//		}
//	}
//	
//	if( pos >= 6 )
//	{
//		Character* ch  = Text_get_character( &txt, 8 );
//		startPoint = (Pixel){ ch->base.position.x - 1, ch->base.position.y - 2, 1 };
//		i_t number = (i_t)tempDate.day;
//		u8_t dayNumber = Date_get_months_day_number( tempDate.year, tempDate.month );
//		command = MenuEdit_number( &menuEditDay, menu, &startPoint, &number, 2, dayNumber, input);
//		tempDate.day = number;			
//		if( command == MENU_EDIT_OK )
//		{
//			pos += 2;
//		}
//		else if( command == MENU_EDIT_CANCEL )
//		{
//			pos = 5;
//			Character* ch  = Text_get_character( &txt, 5 );
//			startPoint = (Pixel){ ch->base.position.x - 1, ch->base.position.y - 2, 1 };
//			i_t number = (i_t)tempDate.month;	
//			command = MenuEdit_number( &menuEditMonth, menu, &startPoint, &number, 2, 12, KEY_NULL);
//		}
//	}	
//	state_t retVal = ST_MENU_SET_DATE_FUNC;
//	switch( command )
//	{
//		case MENU_EDIT_CANCEL:
//			if( pos <= 0 )
//			{
//				retVal = ST_MENU_SET_DATE;
//			}
//			break;
//		case MENU_EDIT_OK:
//			if( pos >= 7 )
//			{
//				pos = 0;
//				menuEditYear.editPosition = 0;
//				menuEditMonth.editPosition = 0;				
//				menuEditDay.editPosition = 0;								
//				retVal = ST_MENU_SET_DATE;
//				ptrRtc->date = tempDate;
//				Date_to_number( &ptrRtc->date );
//			}
//			break;
//	}
//	
//	return retVal;
}

/*----------------------------------------------------------------------------*/

void Rtc_draw( Rtc* self, bool_t force )
{
	if( updateClock || force )
	{
		str = Rtc_to_string( self, FALSE );
		Text_ctor( &txt, 0, 0, &str, 1, FALSE, ms_reference_sans_serif, 12, TRUE);
		Text_draw( &txt );
		updateClock = FALSE;
	}
}
		

/*----------------------------------------------------------------------------*/		

static bool_t Rtc_tick( Rtc* self )
{
	time_t prevTime = self->time.hours;

	updateClock = Time_tick( &self->time );
	
	if( prevTime == 23 && self->time.hours == 0 )
	{
		Settings_save_flash_daily( Settings_get_instance() );
		Date_tick( &self->date );
	}
	
	SpeedMeter_time_tick( SpeedMeter_get_instance() );
	return updateClock;
//	bool_t retVal = FALSE;
//	self->time.seconds++;
//	if( self->time.seconds > 59 )
//	{
//		self->time.seconds = 0;
//		self->time.minutes++;
//		retVal = TRUE;
//		updateClock = TRUE;
//		if( self->time.minutes > 59 )
//		{
//			self->time.minutes = 0;
//			self->time.hours++;
//			if( self->time.hours > 23 )
//			{
//				self->time.hours = 0;
//			}
//		}
//	}
//	
//	return retVal;
}



#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A_int (void)
{
	if( Rtc_tick( ptrRtc ) )
	{
		_BIC_SR_IRQ(CPUOFF); // Wake up processor, update screen		
	};
}