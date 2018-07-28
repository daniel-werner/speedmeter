/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/displayobjects/text.h>
#include <gui/font.h>
#include <gui/displayobjects/character.h>
#include <gui/displayobjects/line.h>

#include <types/buffer.h>

#define PARENT DisplayObject
#define PARENT_CALL(arg) DisplayObject_ ## arg

/*----------------------------------------------------------------------------*/

void Text_ctor( Text* self, coord_t x, coord_t y, String* string, coord_t spacing,
			   		bool_t inverse, enum AvailableFonts fontName, size_t fontSize,
					bool_t ignoreVerticalPadding )
{
	self->fontName = fontName;
	self->fontSize = fontSize;
	self->string = string;
	self->spacing = spacing;
	self->x = x;
	self->y = y;
	self->inverse = inverse;
	self->ignoreVerticalPadding = ignoreVerticalPadding;
	self->width = 0;
	self->height = 0;	

	PARENT_CALL(ctor)( (PARENT*)self );
}

/*----------------------------------------------------------------------------*/

int Text_draw( Text* self )
{
//	Line line;
	Character character;
	coord_t prevWidth = 0;
	coord_t prevX = self->x;
	
	for( i_t i = 0; i < self->string->length; i++ )
	{
		Character_ctor( &character, prevX + prevWidth + self->spacing, self->y,
					   self->string->chars[i], self->inverse, 
					   self->fontName, self->fontSize, self->ignoreVerticalPadding );
		
		self->width += character.width + self->spacing;
		if( self->height < character.height + character.yPadding )
		{
			self->height = character.height + character.yPadding;
		}
		prevWidth = character.width;
		prevX = character.base.position.x;
		Character_draw( &character );

//		Line_ctor( &line, character.base.position.x + character.width, self->y, 
//				  		  character.base.position.x + character.width, self->y + character.height + 1,
//						  0x00 );
//		Line_draw( &line );
	}	
	
	return 1; 
}

/*----------------------------------------------------------------------------*/

Character character;

Character* Text_get_character( const Text* self, u_t index )
{
	Character* retVal = NULL;
	coord_t prevWidth = 0;
	coord_t prevX = self->x;
	
	if( index <= self->string->length )
	{
		for( i_t i = 0; i < self->string->length; i++ )
		{
			Character_ctor( &character, prevX + prevWidth + self->spacing, self->y,
						   self->string->chars[i], self->inverse, 
						   self->fontName, self->fontSize, self->ignoreVerticalPadding );
			
			prevWidth = character.width;
			prevX = character.base.position.x;
			if( i == index )
			{
				retVal = &character;
				break;
			}
		}
	}
	return retVal;
}