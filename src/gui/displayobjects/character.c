/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/displayobjects/character.h>
#include <gui/font.h>
#include <gui/font_manager.h>

#define PARENT Bitmap
#define PARENT_CALL(arg) Bitmap_ ## arg

/*----------------------------------------------------------------------------*/

void Character_ctor( Character* self, coord_t x, coord_t y, char character,
					 bool_t inverse, enum AvailableFonts fontName, size_t fontSize,
					 bool_t ignoreVerticalPadding )
{
	self->fontName = fontName;
	self->fontSize = fontSize;
	self->character = character;

	Font* font = FontManager_getFont( self->fontName, self->fontSize );
	self->offsetX = font->xArray[character];
	self->offsetY = font->yArray[character];
	self->yPadding = font->yPaddingArray[character];
	self->ignoreVerticalPadding = ignoreVerticalPadding;
	self->width = font->widthArray[character];
	self->height = font->heightArray[character];

	Matrix	m;
	
	Matrix_ctor( &m, (u8_t*)font->data, *font->imageWidth, *font->imageHeight / 8 );
	
	
	const unsigned char *pData = Matrix_get_data( &m, u8_t, 0, 0 );

	//NOTE: Hard coded -3 for correct top toolbar display in speedmeter project, 
	// REVISE NEEDED!!!!!!
	coord_t yPadding = self->ignoreVerticalPadding ? self->yPadding - 2 : self->yPadding;
	// correct setting below
	//coord_t yPadding = self->ignoreVerticalPadding ? 0 : self->yPadding;
	
	PARENT_CALL(ctor)( (PARENT*)self, x, y + yPadding , *font->imageWidth, *font->imageHeight, pData, inverse );
}

/*----------------------------------------------------------------------------*/

int Character_draw( const Character* self )
{
	return PARENT_CALL(draw_partial)( (PARENT*)self, self->offsetX, self->offsetY, 
									 				 self->offsetX + self->width, 
													 self->offsetY + self->height );
}