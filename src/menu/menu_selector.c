/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <menu/menu_selector.h>
#include <types/bcd.h>
#include <gui/displayobjects/text.h>
#include <gui/displayobjects/line.h>
#include <gui/displayobjects/mask.h>
#include <types/string.h>


/*----------------------------------------------------------------------------*/

void MenuSelector_ctor( MenuSelector* self, Pixel position, enum AvailableFonts fontName, size_t fontSize )
{
	self->selectedItem = 0;
	self->itemNumber = 0;
	self->position = position;
	self->fontName = fontName;
	self->fontSize = fontSize;
}

/*----------------------------------------------------------------------------*/

bool_t MenuSelector_add_item( MenuSelector* self, String item )
{
	bool_t retVal = FALSE;
	
	if( self->itemNumber < MENU_SELECTOR_MAX_ITEMS )
	{
		self->selectItems[self->itemNumber] = item;
		self->itemNumber++;
		retVal = TRUE;
	}
	
	return retVal;
}

/*----------------------------------------------------------------------------*/

MenuSelectorCommands MenuSelector_select( MenuSelector* self, Menu* menu, key_t input )
{
	MenuSelectorCommands retVal = MENU_SELECT_NULL;
	switch( input )
	{
		case KEY_UP:
			self->selectedItem--;
			if( self->selectedItem < 0 )
			{
				self->selectedItem = self->itemNumber - 1;
			}
			break;
		case KEY_DOWN:
			self->selectedItem++;
			if( self->selectedItem >= self->itemNumber )
			{
				self->selectedItem = 0;
			}		
			break;
		case KEY_ENTER:
			retVal = MENU_SELECT_OK;
			break;
		case KEY_ESCAPE:
			retVal = MENU_SELECT_CANCEL;
			break;			
	}
	
	if( input != KEY_ENTER && input != KEY_ESCAPE )
	{
		Text itemText;
		Mask selectedMask;
		coord_t itemX = self->position.x + 1;
		coord_t itemY = self->position.y;
		coord_t maskWidth = 0;
		for( i_t i = 0; i < self->itemNumber; i++ )
		{
			Text_ctor( &itemText, itemX, itemY, &self->selectItems[i], 
					   1, FALSE, self->fontName, self->fontSize,
					   FALSE);
			Text_draw( &itemText );
			maskWidth = maskWidth < itemText.width + 2 ? itemText.width + 2 : maskWidth;
			
			if( i == self->selectedItem )
			{
				Mask_ctor( &selectedMask, self->position.x, itemY + 1, maskWidth, itemText.height + 1, 0, TRUE );			
				Mask_draw( &selectedMask );			
			}
			
			Character* ch = Text_get_character( &itemText, 0 );
			itemY += itemText.height + 1;
		}	
	}	
	return retVal;
}