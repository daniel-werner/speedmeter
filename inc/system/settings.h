/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _SETTINGS_
#define _SETTINGS_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <menu/menu.h>
#include <io/speed_meter.h>

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

typedef struct Settings Settings;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

typedef enum{
	SPEED_DISPLAY_MODE_GAUGE = 0,
	SPEED_DISPLAY_MODE_NUMERIC = 1
} SpeedDisplayMode;


struct Settings {
	u_t wheelDiameter;
	u_t wheelPerimeter;
	speed_t maxSpeed;
	SpeedDisplayMode speedDisplayMode;
	Trip currentTrip;
	DailyTrip dailyTrip;
	AllTrip allTrip;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

Settings* Settings_get_instance();
bool_t Settings_save_flash( Settings* self );
bool_t Settings_save_flash_daily( Settings* self );
state_t Settings_change_wheer_diameter( Menu* menu, key_t input );
state_t Settings_reset( Menu* menu, key_t input );
const DailyTrip* Settigns_get_daily_trip( i_t index );
state_t Settings_set_speed_display_mode( Menu* menu, key_t input );
state_t Settings_set_gauge_scale( Menu* menu, key_t input );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
