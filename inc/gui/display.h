/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _DISPLAY_
#define _DISPLAY_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <types/matrix.h>
#include <gui/displayobjects/display_object.h>
#include <gui/drivers/display_driver.h>

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

typedef struct Display Display;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

#define DISPLAY_VISIBLE_WIDTH 	98
#define DISPLAY_VISIBLE_HEIGHT 	64

#define DISPLAY_WIDTH 102
#define DISPLAY_HEIGHT 65

#define PACK_SIZE 8

#define BUFFER_SIZE_W DISPLAY_WIDTH 
#define BUFFER_SIZE_H ( DISPLAY_HEIGHT / PACK_SIZE + 1 )

#define DISPLAY_BUFFER_SIZE BUFFER_SIZE_W * BUFFER_SIZE_H

struct Display {
	Matrix displayBuffer;
	u_t width;
	u_t height;
	bool_t bufferingEnabled;
	DisplayDriver* displayDriver;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

Display* Display_get_instance();
bool_t Display_redraw( const Display* self, coord_t x1, coord_t x2 );
void Display_clear( const Display* self );
bool_t Display_render( const Display* self, DisplayObject* obj );
u8_t* Display_set_pixel( const Display* self, Pixel* pixel );
Pixel Display_get_pixel( const Display* self, coord_t x, coord_t y );
void Display_standby( const Display* self );
void Display_wakeup( const Display* self );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
