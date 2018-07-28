/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _TEXT_
#define _TEXT_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <gui/displayobjects/display_object.h>
#include <gui/font_manager.h>
#include <gui/displayobjects/character.h>
#include <types/string.h>

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

typedef struct Text Text;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

struct Text {
	DisplayObject base;
	enum AvailableFonts fontName;
	size_t fontSize;
	String* string;
	coord_t spacing;
	bool_t inverse;
	bool_t ignoreVerticalPadding;
	coord_t x;
	coord_t y;
	coord_t width;
	coord_t height;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

void Text_ctor( Text* self, coord_t x, coord_t y, String* string, coord_t spacing,
			   		bool_t inverse, enum AvailableFonts fontName, size_t fontSize,
					bool_t ignoreVerticalPadding );
int Text_draw( Text* self );
Character* Text_get_character( const Text* self, u_t index );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
