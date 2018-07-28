/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _BITMAP_
#define _BITMAP_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <gui/displayobjects/display_object.h>
#include <gui/displayobjects/point.h>
#include <types/matrix.h>

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

typedef struct Bitmap Bitmap;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

struct Bitmap {
	DisplayObject base;
	Point position; 
	coord_t width;
	coord_t height;
	bool_t inverse;
	Matrix data;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

void Bitmap_ctor( Bitmap* self, coord_t x, coord_t y, coord_t width, coord_t height, const void* data, bool_t inverse );
int Bitmap_draw( const Bitmap* self );
int Bitmap_draw_partial( const Bitmap* self, coord_t x1, coord_t y1, coord_t x2, coord_t y2 );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif