/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <menu/menu_edit.h>
#include <types/bcd.h>
#include <gui/displayobjects/text.h>
#include <gui/displayobjects/line.h>
#include <types/string.h>
#include <gui/font_manager.h>

/*----------------------------------------------------------------------------*/


void MenuEdit_ctor( MenuEdit* self )
{
	self->editPosition = 0;
}

/*----------------------------------------------------------------------------*/

MenuEditCommands MenuEdit_number( MenuEdit* self, Menu* menu, Pixel* position,
								 i_t* number, u8_t places, i_t maxNumber, key_t input, 
								 AvailableFonts fontName, size_t fontSize )
{
	String str = int2bcd( *number, places, TRUE, 0, 0 );
	Text txt;
	Text_ctor( &txt, position->x, position->y, &str, 1, FALSE, fontName, fontSize, FALSE );
	Text_draw( &txt );
	
	MenuEditCommands retVal = MENU_EDIT_NULL;
	
	Character* pCharacter = Text_get_character( &txt, self->editPosition );
	
	Line line;

	switch( input )
	{
		case KEY_ESCAPE:
			pCharacter = Text_get_character( &txt, self->editPosition );
			Line_ctor( &line, pCharacter->base.position.x,
							  pCharacter->base.position.y + pCharacter->height + 1, 
							  pCharacter->base.position.x + pCharacter->width, 
							  pCharacter->base.position.y + pCharacter->height + 1, 0 );
			Line_draw( &line );		
			self->editPosition--;
			if( self->editPosition < 0 )
			{
				self->editPosition = 0;
				retVal =  MENU_EDIT_CANCEL;
			}
			break;
		
		case KEY_UP:
			*number = changeBcdNumber( *number, places, self->editPosition, 1, maxNumber );
			break;
			
		case KEY_DOWN:
			*number = changeBcdNumber( *number, places, self->editPosition, -1, maxNumber );
			break;
		
		case KEY_ENTER:
			pCharacter = Text_get_character( &txt, self->editPosition );
			Line_ctor( &line, pCharacter->base.position.x,
							  pCharacter->base.position.y + pCharacter->height + 1, 
							  pCharacter->base.position.x + pCharacter->width, 
							  pCharacter->base.position.y + pCharacter->height + 1, 0 );
			Line_draw( &line );				
			self->editPosition++;
			if( self->editPosition >= places )
			{
				self->editPosition = places - 1;
				retVal = MENU_EDIT_OK;
			}
			break;
	}
	
	if( retVal != MENU_EDIT_CANCEL && retVal != MENU_EDIT_OK )
	{
		pCharacter = Text_get_character( &txt, self->editPosition );	
		Line_ctor( &line, pCharacter->base.position.x,
						  pCharacter->base.position.y + pCharacter->height + 1, 
						  pCharacter->base.position.x + pCharacter->width, 
						  pCharacter->base.position.y + pCharacter->height + 1, 1 );
		Line_draw( &line );
	}
	
	str = int2bcd( *number, places, TRUE, 0, 0);
	Text_draw( &txt );	
	
	return retVal;
}

/*----------------------------------------------------------------------------*/