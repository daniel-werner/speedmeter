/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _SPEED_METER_
#define _SPEED_METER_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <timer/rtc.h>

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

typedef struct SpeedMeter SpeedMeter;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

typedef u_t speed_t;
typedef u32_t distance_t;

typedef struct AllTrip
{
	distance_t distance;
	AllTripTime elapsedTime;
}AllTrip;


typedef struct Trip
{
	distance_t distance;
	Time elapsedTime;
}Trip;

typedef u16_t daily_distance_t;

typedef struct DailyTrip
{
	daily_distance_t distance;
	Time elapsedTime;
}DailyTrip;

struct SpeedMeter{
	speed_t currentSpeed;
	Trip* currentTrip;
	DailyTrip* dailyTrip;
	AllTrip* allTrip;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

void SpeedMeter_ctor( SpeedMeter* self );
SpeedMeter* SpeedMeter_get_instance();
void SpeedMeter_draw( bool_t force, bool_t gauge );
void SpeedMeter_draw_gauge_numbers( SpeedMeter* self );
void SpeedMeter_time_tick( SpeedMeter* self );
state_t SpeedMeter_change_top_display( Menu* menu, key_t input );
u16_t SpeedMeter_calculate_average_speed( SpeedMeter* self, distance_t distance, u32_t seconds );
void SpeedMeter_calculate_gauge_coords( SpeedMeter* self, u_t maxSpeed );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
