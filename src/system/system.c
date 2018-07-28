/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <system/system.h>
#include <gui/display.h>
#include <gui/displayobjects/text.h>
#include <menu/menu.h>
#include <menu/menu_states.h>
#include <menu/menu_selector.h>


static System systemInstance = { FALSE, 0 };
static System* pSystem = &systemInstance;

/*----------------------------------------------------------------------------*/

System* System_get_instance()
{
	return pSystem;	
}

/*----------------------------------------------------------------------------*/

bool_t System_standby()
{
	bool_t retVal = !pSystem->standby;	
	if( !pSystem->standby )
	{
		Display_standby( Display_get_instance() );
	}
	pSystem->standby = TRUE;
	pSystem->standbyCounter = 0;	
	_BIS_SR(LPM3_bits + GIE);                       // Enter LPM0		    	
	
	return retVal;
}

/*----------------------------------------------------------------------------*/

extern Menu menu;

bool_t System_wakeup()
{
	bool_t retVal = pSystem->standby;

	pSystem->standbyCounter = 0;
	if( pSystem->standby )
	{
		Display_wakeup( Display_get_instance() );
		Menu_reset( &menu );
		pSystem->standby = FALSE;		
	}

	return retVal;
}

void System_restart()
{
	WDTCTL = 0;
}

/*----------------------------------------------------------------------------*/

MenuSelector systemMenuSelector;
MenuSelector* pSystemMenuSelector;

state_t System_shutdown_menu( Menu* menu, key_t input )
{
	state_t retVal = ST_SHUTDOWN_MENU;
	if( input == KEY_DUMMY )
	{
		return ST_MENU;
	}	
	Menu_clear_all( menu );
	//Menu_clear_text( menu );
	Pixel position = { menu->iconX + 5, menu->iconY + 5 };
	
	String str = (String){STRING("Choose action:")};
	Text txt;
	Text_ctor( &txt, menu->iconX + 1, menu->iconY - 5 , &str, 1, 
					 FALSE, ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );		
	
	if( pSystemMenuSelector == NULL )
	{
		MenuSelector_ctor( &systemMenuSelector, position, ms_reference_sans_serif, 12 );
		pSystemMenuSelector = &systemMenuSelector;
		
		MenuSelector_add_item( pSystemMenuSelector, (String){STRING("Standby")} );
		MenuSelector_add_item( pSystemMenuSelector, (String){STRING("Restart")} );		
	}
	MenuSelectorCommands command = MenuSelector_select( pSystemMenuSelector, menu, input );
	
	switch( command )
	{
		case MENU_SELECT_OK:
			if( pSystemMenuSelector->selectedItem == 0 )
			{
				System_standby();
			}
			else if( pSystemMenuSelector->selectedItem == 1 )
			{
				System_restart();
			}
			pSystemMenuSelector = NULL;
			break;
		
		case MENU_SELECT_CANCEL:
			pSystemMenuSelector = NULL;
			retVal = ST_MENU;
			break;
	}

	return retVal;
}

/*----------------------------------------------------------------------------*/