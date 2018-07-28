/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _MENU_SELECTOR_
#define _MENU_SELECTOR_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <types/string.h>
#include <menu/keyboard.h>
#include <menu/menu.h>
#include <gui/pixel.h>

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

typedef struct MenuSelector MenuSelector;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/
typedef enum
{
	MENU_SELECT_NULL = 0,	
	MENU_SELECT_CANCEL = 1,
	MENU_SELECT_OK = 2
} MenuSelectorCommands;

#define MENU_SELECTOR_MAX_ITEMS 5

struct MenuSelector {
	String selectItems[MENU_SELECTOR_MAX_ITEMS];
	size_t itemNumber;
	i_t selectedItem;
	Pixel position;
	AvailableFonts fontName;
	size_t fontSize;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

void MenuSelector_ctor( MenuSelector* self, Pixel position, enum AvailableFonts fontName, size_t fontSize );
bool_t MenuSelector_add_item( MenuSelector* self, String item );
MenuSelectorCommands MenuSelector_select( MenuSelector* self, Menu* menu, key_t input );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
