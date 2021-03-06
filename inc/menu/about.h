/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _ABOUT_
#define _ABOUT_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>

#include <menu/menu_states.h>
#include <menu/menu.h>
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


/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

state_t About_draw( Menu* menu, key_t input );
u8_t* About_get_image();
	
/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
