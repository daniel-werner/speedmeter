/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/font.h>
#include <gui/font_manager.h>
#include <gui/available_fonts.h>
#include <assert.h>

/*----------------------------------------------------------------------------*/

Font* FontManager_getFont( AvailableFonts fontName, u8_t fontSize )
{
	u_t numFonts = sizeof( availFonts ) / sizeof( Font );
	bool_t found = FALSE;
	Font* currentFont;
	
	for( i_t i = 0; i < numFonts; i++ )
	{
		currentFont = (Font*)&availFonts[i];
		if( currentFont->fontName == fontName && currentFont->fontSize == fontSize )
		{
			found = TRUE;
			break;
		}
	}
	
	assert( found );
	
	return currentFont;
}

/*----------------------------------------------------------------------------*/