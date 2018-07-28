/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _CHARACTER_
#define _CHARACTER_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <gui/displayobjects/bitmap.h>
#include <gui/font_manager.h>

/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma unmanaged
#endif

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

typedef struct Character Character;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

struct Character {
	Bitmap base;
	enum AvailableFonts fontName;
	size_t fontSize;
	char character;
	bool_t ignoreVerticalPadding;
	coord_t offsetX;
	coord_t offsetY;
	coord_t yPadding;
	coord_t width;
	coord_t height;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

void Character_ctor( Character* self, coord_t x, coord_t y, char character,
					 bool_t inverse, enum AvailableFonts fontName, size_t fontSize,
					 bool_t ignoreVerticalPadding );
int Character_draw( const Character* self );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
