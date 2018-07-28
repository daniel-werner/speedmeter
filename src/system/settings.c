/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <system/settings.h>
#include <menu/menu_edit.h>
#include <menu/menu_states.h>
#include <menu/menu_selector.h>
#include <gui/displayobjects/text.h>
#include <types/string.h>
#include <math.h>
//#include <io/speed_meter.h>

#include <inc/flash/flash_manager.h>

static Settings settingsInstance;
static Settings* pSettings = NULL;

#pragma constseg=SETTINGS_ID   // use special area for the following variables
static const Settings flashSettings = {711, 2230, 40, SPEED_DISPLAY_MODE_GAUGE };
static const DailyTrip dailyTrips[3653];
#pragma constseg = default  // switch back to regular segment for following


/*----------------------------------------------------------------------------*/

static MenuEdit menuEdit;
extern Rtc rtc;

Settings* Settings_get_instance()
{
	if( pSettings == NULL )
	{
		settingsInstance = flashSettings;
		settingsInstance.dailyTrip = dailyTrips[rtc.date.elapsedDays];
		settingsInstance.dailyTrip.distance *= 100;
		pSettings = &settingsInstance;
	}
	return pSettings;
}

/*----------------------------------------------------------------------------*/

const DailyTrip* Settigns_get_daily_trip( i_t index )
{
	return &dailyTrips[index];
}

/*----------------------------------------------------------------------------*/

bool_t Settings_save_flash( Settings* self )
{
	flash_write( (char*)pSettings, (char*)&flashSettings, sizeof( Settings ) );
	//Settings_save_flash_daily( pSettings );
	return TRUE;
}

/*----------------------------------------------------------------------------*/

bool_t Settings_save_flash_daily( Settings* self )
{
	pSettings->dailyTrip.distance = pSettings->dailyTrip.distance / 100; 
	flash_write( (char*)&pSettings->dailyTrip, (char*)&dailyTrips[rtc.date.elapsedDays], sizeof( DailyTrip ) );
	pSettings->dailyTrip.distance = pSettings->dailyTrip.distance * 100; 
	return TRUE;
}

/*----------------------------------------------------------------------------*/

u_t tempWheelDiameter;

state_t Settings_change_wheer_diameter( Menu* menu, key_t input )
{
	i_t* number = (i_t*)&tempWheelDiameter;
	Pixel startPoint = { 39, 32, 1 };
	
	if( input == KEY_NULL )
	{
		tempWheelDiameter = Settings_get_instance()->wheelDiameter;
		Menu_clear_text( menu );
		Text txt;

		String str = {STRING("Diameter:")};
		Text_ctor( &txt, menu->iconX + menu->iconWidth + 5, menu->iconY + 5, &str, 1, FALSE, ms_sans_serif, 11, FALSE );
		Text_draw( &txt );
		
		str = (String){STRING(" mm")};
		Text_ctor( &txt, 70, 32, &str, 1, FALSE, ms_sans_serif, 11, FALSE );
		Text_draw( &txt );		
	}
	
	MenuEditCommands command = MenuEdit_number( &menuEdit, menu, &startPoint, number, 4, 9999, input, ms_sans_serif, 11 );
	
	state_t retVal = ST_MENU_SET_DIAMETER_FUNC;
	
	switch( command )
	{
		case MENU_EDIT_CANCEL:
			retVal = ST_MENU_SET_DIAMETER;
			break;
		case MENU_EDIT_OK:
			retVal = ST_MENU_SET_DIAMETER;
			Settings_get_instance()->wheelDiameter = tempWheelDiameter;
			Settings_get_instance()->wheelPerimeter = (u_t)((f32_t)__PI * tempWheelDiameter);
			tempWheelDiameter = 0;			
			break;
	}
	
	
	if( retVal != ST_MENU_SET_DIAMETER )
	{
		if( menuEdit.editPosition == 0 )
		{
			Menu_draw_bottom_line( menu, BOTTOM_RIGHT_ARROW );			
		}
		else if( menuEdit.editPosition == 3 )
		{
			Menu_draw_bottom_line( menu, BOTTOM_LEFT_ARROW );			
		}
		else
		{
			Menu_draw_bottom_line( menu, BOTTOM_ARROWS );
		}		
	}
	else
	{
		Menu_draw_bottom_line( menu, BOTTOM_ENTER_ESCAPE );
	}
	
	return retVal;
}

/*----------------------------------------------------------------------------*/

MenuSelector menuSelector;
MenuSelector* pMenuSelector = NULL;

state_t Settings_reset( Menu* menu, key_t input )
{
	state_t retVal = ST_MENU_RESET_FUNC;
	Menu_clear_text( menu );
	Pixel position = { menu->iconX + menu->iconWidth + 5, menu->iconY + 5 };
	
	String str = (String){STRING("Choose trip:")};
	Text txt;
	Text_ctor( &txt, menu->iconX + menu->iconWidth + 1, menu->iconY - 5 , &str, 1, 
			         FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );		
	
	if( pMenuSelector == NULL )
	{
		MenuSelector_ctor( &menuSelector, position, ms_reference_sans_serif, 12 );
		pMenuSelector = &menuSelector;
		
		MenuSelector_add_item( pMenuSelector, (String){STRING("Current")} );
		MenuSelector_add_item( pMenuSelector, (String){STRING("All")} );		
	}
	MenuSelectorCommands command = MenuSelector_select( pMenuSelector, menu, input );
	
	switch( command )
	{
		case MENU_SELECT_OK:
			if( pMenuSelector->selectedItem == 0 )
			{
				settingsInstance.currentTrip.distance = 0;
				settingsInstance.currentTrip.elapsedTime = (Time){0,0,0};
			}
			else if( pMenuSelector->selectedItem == 1 )
			{
				settingsInstance.allTrip.distance = 0;
				settingsInstance.allTrip.elapsedTime = (AllTripTime){0,0,0};
			}
			retVal = ST_MENU_RESET;
			pMenuSelector = NULL;
			break;
		
		case MENU_SELECT_CANCEL:
			retVal = ST_MENU_RESET;		
			pMenuSelector = NULL;			
			break;
	}
		
	return retVal;
}

/*----------------------------------------------------------------------------*/

state_t Settings_set_gauge_scale( Menu* menu, key_t input )
{
	state_t retVal = ST_MENU_SET_GAUGE_SCALE_FUNC;
	Menu_clear_text( menu );
	Pixel position = { menu->iconX + menu->iconWidth + 5, menu->iconY + 5 };
	
	String str = (String){STRING("Choose scale:")};
	Text txt;
	Text_ctor( &txt, menu->iconX + menu->iconWidth + 1, menu->iconY - 5 , &str, 1, 
			         FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );		
	
	if( pMenuSelector == NULL )
	{
		MenuSelector_ctor( &menuSelector, position, ms_reference_sans_serif, 12 );
		pMenuSelector = &menuSelector;
		
		MenuSelector_add_item( pMenuSelector, (String){STRING("40 km/h")} );
		MenuSelector_add_item( pMenuSelector, (String){STRING("80 km/h")} );		
		pMenuSelector->selectedItem = settingsInstance.maxSpeed == 40 ? 0 : 1;
	}
	MenuSelectorCommands command = MenuSelector_select( pMenuSelector, menu, input );
	
	switch( command )
	{
		case MENU_SELECT_OK:
			if( pMenuSelector->selectedItem == 0 )
			{
				settingsInstance.maxSpeed = 40;
			}
			else if( pMenuSelector->selectedItem == 1 )
			{
				settingsInstance.maxSpeed = 80;
			}
			SpeedMeter_calculate_gauge_coords( SpeedMeter_get_instance(), settingsInstance.maxSpeed );			
			retVal = ST_MENU_SET_GAUGE_SCALE;
			pMenuSelector = NULL;
			break;
		
		case MENU_SELECT_CANCEL:
			retVal = ST_MENU_SET_GAUGE_SCALE;		
			pMenuSelector = NULL;			
			break;
	}
		
	return retVal;
}

/*----------------------------------------------------------------------------*/

state_t Settings_set_speed_display_mode( Menu* menu, key_t input )
{
	state_t retVal = ST_MENU_SET_SPEED_DISPLAY_MODE_FUNC;
	Menu_clear_text( menu );
	Pixel position = { menu->iconX + menu->iconWidth + 5, menu->iconY + 5 };
	
	String str = (String){STRING("Choose scale:")};
	Text txt;
	Text_ctor( &txt, menu->iconX + menu->iconWidth + 1, menu->iconY - 5 , &str, 1, 
			         FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );		
	
	if( pMenuSelector == NULL )
	{
		MenuSelector_ctor( &menuSelector, position, ms_reference_sans_serif, 12 );
		pMenuSelector = &menuSelector;
		
		MenuSelector_add_item( pMenuSelector, (String){STRING("Gauge")} );
		MenuSelector_add_item( pMenuSelector, (String){STRING("Numeric")} );
		pMenuSelector->selectedItem = settingsInstance.speedDisplayMode == SPEED_DISPLAY_MODE_GAUGE ? 0 : 1;		
	}
	MenuSelectorCommands command = MenuSelector_select( pMenuSelector, menu, input );
	
	switch( command )
	{
		case MENU_SELECT_OK:
			if( pMenuSelector->selectedItem == 0 )
			{
				settingsInstance.speedDisplayMode = SPEED_DISPLAY_MODE_GAUGE;
			}
			else if( pMenuSelector->selectedItem == 1 )
			{
				settingsInstance.speedDisplayMode = SPEED_DISPLAY_MODE_NUMERIC;
			}
			retVal = ST_MENU_SET_SPEED_DISPLAY_MODE;
			pMenuSelector = NULL;
			break;
		
		case MENU_SELECT_CANCEL:
			retVal = ST_MENU_SET_SPEED_DISPLAY_MODE;		
			pMenuSelector = NULL;			
			break;
	}
		
	return retVal;
}