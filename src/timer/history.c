/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <system/settings.h>
#include <menu/menu_selector.h>
#include <menu/menu_states.h>
#include <menu/menu_edit.h>
#include <gui/displayobjects/text.h>
#include <gui/displayobjects/mask.h>
#include <gui/display.h>

#include <types/bcd.h>

MenuSelector historyMenuSelector;
MenuSelector* pHistoryMenuSelector = NULL;

/*----------------------------------------------------------------------------*/

History_clear_details( Menu* menu )
{
	Mask menuMask;
	Mask_ctor( &menuMask, 1, menu->iconY + 2, 
			  		  DISPLAY_VISIBLE_WIDTH - 1, menu->iconHeight - 2,
					  0, FALSE );
	
	Mask_draw( &menuMask );			
}

/*----------------------------------------------------------------------------*/

void History_draw_details( Menu* menu, Trip* currentTrip, DailyTrip* dailyTrip, AllTrip* allTrip )
{
	//History_clear_details( menu );
	//Menu_clear_all( menu );
	coord_t x = menu->iconX - 1;
	coord_t y = menu->iconY + 2;

	String distanceStr;
	String timeStr;
	String avgerageStr;
	u16_t avgSpeed;
	distance_t distance;
	
	if( currentTrip != NULL )
	{
		distance = currentTrip->distance;
		avgSpeed = SpeedMeter_calculate_average_speed( SpeedMeter_get_instance(), currentTrip->distance, Time_get_seconds( &currentTrip->elapsedTime ) );	
	}
	else if( dailyTrip != NULL )
	{
		distance = dailyTrip->distance * 100;
		avgSpeed = SpeedMeter_calculate_average_speed( SpeedMeter_get_instance(), distance, Time_get_seconds( &dailyTrip->elapsedTime ) );	
	}
	else if( allTrip != NULL )
	{
		distance = allTrip->distance;
		avgSpeed = SpeedMeter_calculate_average_speed( SpeedMeter_get_instance(), allTrip->distance,  Time_get_seconds_all( &allTrip->elapsedTime ) );	
	}
		
	
	String str = (String){STRING("Distance:")};
	Text txt;
	Text_ctor( &txt, x, y , &str, 1, FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );
	
	if( allTrip != NULL )
	{
		distanceStr = int2bcd( distance, 5, FALSE, 2, 1 );
	}
	else
	{
		distanceStr = int2bcd( distance, 4, FALSE, 2, 1 );	
	}
	Text_ctor( &txt, x + txt.width + 1, y , &distanceStr, 1, FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );
	
	str = (String){STRING("km")};
	Text_ctor( &txt, x + txt.x + txt.width, y , &str, 1, FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );		
	
	y += txt.height - 1;
	str = (String){STRING("Time:")};
	Text_ctor( &txt, x, y , &str, 1, FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );
	
	if( currentTrip != NULL )
	{
		timeStr = Time_to_string( &currentTrip->elapsedTime, TRUE );			
	}
	else if( dailyTrip != NULL )
	{
		timeStr = Time_to_string( &dailyTrip->elapsedTime, TRUE );
	}
	else if( allTrip != NULL )
	{
		timeStr = Time_to_string_all( &allTrip->elapsedTime, TRUE );
	}

	Text_ctor( &txt, x + txt.width + 1, y , &timeStr, 1, FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );

	y += txt.height - 1;
	str = (String){STRING("Avg spd:")};
	Text_ctor( &txt, x, y , &str, 1, FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );
	
	avgerageStr = int2bcd( avgSpeed, 3, FALSE, 0, 1 );
	Text_ctor( &txt, x + txt.width + 1 , y , &avgerageStr, 1, FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );
	
	str = (String){STRING("km/h")};
	Text_ctor( &txt, x + txt.x + txt.width, y , &str, 1, FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );	
	
}

/*----------------------------------------------------------------------------*/


Date tempDateh;
MenuEdit menuEditYear1;
MenuEdit menuEditMonth1;
MenuEdit menuEditDay1;
u8_t pos1 = 0;
String strh;
Text txth;

/*----------------------------------------------------------------------------*/

state_t History_select_date( Rtc* pRtc, Pixel startPoint, Menu* menu, key_t input )
{
	//Pixel startPoint = { 34, 32, 1 };

	if( input == KEY_NULL )
	{
		//pos = 0;
		Menu_clear_all( menu );		
		tempDateh = pRtc->date;
		strh = Date_to_string( &tempDateh );
		Text_ctor( &txth, startPoint.x, startPoint.y, &strh, 1, FALSE, ms_reference_sans_serif, 12, FALSE );
		Text_draw( &txth );			
	}
	else
	{
		History_clear_details( menu );
	}

	MenuEditCommands command;
	if( pos1 < 4 )
	{
		i_t number = (i_t)tempDateh.year;	
		command = MenuEdit_number( &menuEditYear1, menu, &startPoint, &number, 4, 2100, input, ms_reference_sans_serif, 12);
		input = KEY_NULL;
		tempDateh.year = number;
		Date_validate_and_correct( &tempDateh );
		if( command == MENU_EDIT_OK )
		{
			pos1 += 4;
		}
		else if( command == MENU_EDIT_CANCEL )
		{
			pos1 = 0;
		}
	}
	
	if( pos1 >= 4 && pos1 < 6 )
	{
		Character* ch  = Text_get_character( &txth, 5 );
		Pixel startPointl = (Pixel){ ch->base.position.x - 1, ch->base.position.y - 3, 1 };
		i_t number = (i_t)tempDateh.month;	
		command = MenuEdit_number( &menuEditMonth1, menu, &startPointl, &number, 2, 12, input, ms_reference_sans_serif, 12);
		input = KEY_NULL;		
		tempDateh.month = number;
		Date_validate_and_correct( &tempDateh );		
		if( command == MENU_EDIT_OK )
		{
			pos1 += 2;
		}
		else if( command == MENU_EDIT_CANCEL )
		{
			pos1 = 0;
			//startPoint = (Pixel){ 34, 32, 1 };
			i_t number = (i_t)tempDateh.year;	
			command = MenuEdit_number( &menuEditYear1, menu, &startPoint, &number, 4, 2100, KEY_NULL, ms_reference_sans_serif, 12);
		}
	}
	
	if( pos1 >= 6 )
	{
		Character* ch  = Text_get_character( &txth, 8 );
		startPoint = (Pixel){ ch->base.position.x - 1, ch->base.position.y - 3, 1 };
		i_t number = (i_t)tempDateh.day;
		u8_t dayNumber = Date_get_months_day_number( tempDateh.year, tempDateh.month );
		command = MenuEdit_number( &menuEditDay1, menu, &startPoint, &number, 2, dayNumber, input, ms_reference_sans_serif, 12);
		tempDateh.day = number;			
		if( command == MENU_EDIT_OK )
		{
			pos1 += 2;
		}
		else if( command == MENU_EDIT_CANCEL )
		{
			pos1 = 5;
			Character* ch  = Text_get_character( &txth, 5 );
			startPoint = (Pixel){ ch->base.position.x - 1, ch->base.position.y - 3, 1 };
			i_t number = (i_t)tempDateh.month;	
			command = MenuEdit_number( &menuEditMonth1, menu, &startPoint, &number, 2, 12, KEY_NULL, ms_reference_sans_serif, 12);
		}
	}	
	state_t retVal = ST_MENU_SET_DATE_FUNC;
	switch( command )
	{
		case MENU_EDIT_CANCEL:
			if( pos1 <= 0 )
			{
				retVal = ST_MENU_SET_DATE;
			}
			break;
		case MENU_EDIT_OK:
			if( pos1 >= 7 )
			{
				pos1 = 0;
				menuEditYear1.editPosition = 0;
				menuEditMonth1.editPosition = 0;				
				menuEditDay1.editPosition = 0;								
				retVal = ST_MENU_SET_DATE;
				pRtc->date = tempDateh;
				Date_to_number( &pRtc->date );
			}
			break;
	}	

	if( retVal != ST_MENU_SET_DATE )
	{
		tempDateh.elapsedDays = Date_to_number( &tempDateh );		
		const DailyTrip* pDailyTrip = Settigns_get_daily_trip( tempDateh.elapsedDays );
		History_draw_details( menu, NULL, (DailyTrip*)pDailyTrip, NULL );
	}
	
	if( pos1 <= 1 && menuEditYear1.editPosition == 0 )
	{
		Menu_draw_bottom_line( menu, BOTTOM_RIGHT_ARROW );			
	}
	else if( pos1 >= 6 && menuEditDay1.editPosition == 1 )
	{
		Menu_draw_bottom_line( menu, BOTTOM_LEFT_ARROW );			
	}
	else
	{
		Menu_draw_bottom_line( menu, BOTTOM_ARROWS );
	}
	
	return retVal;
}


/*---------------------------------------------------------------------------*/

bool_t details = FALSE;
extern Rtc rtc;
MenuSelectorCommands command;

/*---------------------------------------------------------------------------*/

state_t History_view( Menu* menu, key_t input )
{
	state_t retVal = ST_MENU_HISTORY_FUNC;
	Pixel position = { menu->iconX + menu->iconWidth + 5, menu->iconY - 4 };
	
//	String str = (String){STRING("Choose trip:")};
//	Text txt;
//	Text_ctor( &txt, menu->iconX + menu->iconWidth + 1, menu->iconY - 5 , &str, 1, 
//			         FALSE, ms_reference_sans_serif, 12, FALSE );
//	Text_draw( &txt );		
	
	if( !details )
	{
		//input = KEY_NULL;
		Menu_clear_text( menu );		
		Menu_draw_icon( menu );
	}
	
	if( !details )
	{
		if( pHistoryMenuSelector == NULL )
		{
			MenuSelector_ctor( &historyMenuSelector, position, ms_reference_sans_serif, 12 );
			pHistoryMenuSelector = &historyMenuSelector;
			
			MenuSelector_add_item( pHistoryMenuSelector, (String){STRING("Current")} );
			MenuSelector_add_item( pHistoryMenuSelector, (String){STRING("Daily")} );		
			MenuSelector_add_item( pHistoryMenuSelector, (String){STRING("All")} );				
		}

		command = MenuSelector_select( pHistoryMenuSelector, menu, input );
	}
		switch( command )
		{
			case MENU_SELECT_OK:
				if( pHistoryMenuSelector->selectedItem == 0 )
				{
					details ^= TRUE;					
					if( details )
					{
						Menu_clear_all( menu );
						History_draw_details( menu, &Settings_get_instance()->currentTrip, NULL, NULL );
					}
					//input = KEY_NULL;
				}
				else if( pHistoryMenuSelector->selectedItem == 1 )
				{
					Pixel startPoint = { 0, 6, 1 };
					Rtc tempRtc = rtc;
					if( !details )
						input = KEY_NULL;
					details = TRUE;

					if( History_select_date( &tempRtc, startPoint, menu, input ) == ST_MENU_SET_DATE )
						details = FALSE;
					input = KEY_NULL;					
					//details = TRUE;
					//input = KEY_NULL;					
				}
				else if( pHistoryMenuSelector->selectedItem == 2 )
				{
					details ^= TRUE;					
					if( details )
					{					
						Menu_clear_all( menu );
						History_draw_details( menu, NULL, NULL, &Settings_get_instance()->allTrip );
					}
					//input = KEY_NULL;						
				}
				
				if( !details )
				{
					Menu_clear_all( menu );					
					retVal = ST_MENU_HISTORY;
					pHistoryMenuSelector = NULL;
				}
				break;
			
			case MENU_SELECT_CANCEL:
				retVal = ST_MENU_HISTORY;	
				pHistoryMenuSelector = NULL;			
				break;
		}
//	}
		
	return retVal;
}

/*----------------------------------------------------------------------------*/