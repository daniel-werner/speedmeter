/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _MENU_
#define _MENU_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <types/string.h>
#include <gui/pixel.h>
#include <menu/keyboard.h>

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

typedef struct Menu Menu;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

typedef u8_t state_t;

typedef state_t (*state_func_t)( Menu* menu, key_t input);

typedef enum{
	BOTTOM_ENTER_ESCAPE = 1,
	BOTTOM_ARROWS = 2,
	BOTTOM_RIGHT_ARROW = 3,
	BOTTOM_LEFT_ARROW = 4
} BottomLineType;

typedef struct
{
    state_t state;
    key_t input;
    state_t nextstate;
} MenuNextState;


//typedef struct
//{
//    state_t state;
//    const char* pText;
//    state_func_t pFunc;
//} MenuState;

typedef struct
{
    state_t state;
    const String* pText;
	const u8_t* bitmap;
    state_func_t pFunc;
} MenuState;

struct Menu {
	Keyboard keyboard;
	MenuState* states;
	MenuNextState* stateRelations;
	MenuState* currentState;
	coord_t iconX;
	coord_t iconY;
	coord_t iconWidth;
	coord_t iconHeight;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

void Menu_ctor( Menu* self );
state_t Menu_process( Menu* self, bool_t selfCall );
void Menu_draw_icon( Menu* self );
void Menu_clear_all( Menu* self );
void Menu_clear_text( Menu* self );
void Menu_draw_bottom_line( Menu* self, BottomLineType type );
void Menu_reset( Menu* self );
/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
