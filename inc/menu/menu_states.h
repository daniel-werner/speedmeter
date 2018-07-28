/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _MENU_STATES_
#define _MENU_STATES_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <system/settings.h>

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

// State names

#define ST_MENU     	                1
#define ST_SHUTDOWN_MENU     	        2	
#define ST_MENU_SETTINGS                10
#define ST_MENU_SET_TIME                11
#define ST_MENU_SET_TIME_FUNC           111
#define ST_MENU_SET_DATE                12
#define ST_MENU_SET_DATE_FUNC           121	
#define ST_MENU_SET_DIAMETER            13
#define ST_MENU_SET_DIAMETER_FUNC       131
#define ST_MENU_SET_GAUGE_SCALE         14
#define ST_MENU_SET_GAUGE_SCALE_FUNC    141	
#define ST_MENU_SET_SPEED_DISPLAY_MODE  15
#define ST_MENU_SET_SPEED_DISPLAY_MODE_FUNC    151		
#define ST_MENU_ABOUT                   20
#define ST_MENU_ABOUT_FUNC              21
#define ST_MENU_RESET                   30
#define ST_MENU_RESET_FUNC              31
#define ST_MENU_HISTORY                 40
#define ST_MENU_HISTORY_FUNC            41	
	
/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

MenuNextState* get_menu_relations();
MenuState* get_menu_state();
	
/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
