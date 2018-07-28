/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <menu/about.h>
#include <menu/menu_states.h>

#include <gui/displayobjects/bitmap.h>
#include <gui/displayobjects/text.h>
#include <gui/display.h>

#include <gui/images/splash.h>

/*----------------------------------------------------------------------------*/

u8_t* About_get_image()
{
	return (u8_t*)splash;
}

/*----------------------------------------------------------------------------*/

state_t About_draw( Menu* menu, key_t input )
{
	u8_t* about_image = About_get_image();
	
	Bitmap bitmap;
	Bitmap_ctor( &bitmap, 0, 0, DISPLAY_VISIBLE_WIDTH, DISPLAY_VISIBLE_HEIGHT, about_image, FALSE );
	Bitmap_draw( &bitmap );	
	
	Text txt;
	String str = (String){STRING( "WD" )};
	Text_ctor( &txt, 0, 54, &str, 1, FALSE, 
			  		 ms_reference_sans_serif, 12, FALSE );
	Text_draw( &txt );	
	
	state_t retVal = ST_MENU_ABOUT_FUNC;
	
	if( (input != KEY_ENTER) && (input != KEY_NULL) )
	{
		retVal = ST_MENU;
	}	
	return retVal;
}


/*----------------------------------------------------------------------------*/