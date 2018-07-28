/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/displayobjects/circle.h>
#include <gui/displayobjects/point.h>
#include <gui/display.h>

#define PARENT Point
#define PARENT_CALL(arg) Point_ ## arg

/*----------------------------------------------------------------------------*/

void Circle_ctor( Circle* self, coord_t x, coord_t y, u_t radius, u8_t color )
{
	PARENT_CALL(ctor)( (PARENT*)self, x, y, color );

	self->radius = radius;
}

/*----------------------------------------------------------------------------*/

int Circle_draw( const Circle* self )
{
	Pixel startPix;
	Pixel pix;

	startPix.color = ((PARENT*)self)->color;
	pix.color = ((PARENT*)self)->color;
	
	startPix.x = 0;
	startPix.y = (coord_t)self->radius;
	i_t p = 3 - 2 * self->radius;

	dtor_Vector( (Vector*)&((PARENT*)self)->base.pixels );
	ctor_Vector( (Vector*)&((PARENT*)self)->base.pixels, 6 * self->radius * sizeof(Pixel) );
	
	while ( startPix.x <= startPix.y)
	{
		pix.x = ((Point*)self)->x + startPix.x;
		pix.y = ((Point*)self)->y + startPix.y;
		DisplayObject_add_pixel( (DisplayObject*)self, &pix );
		
		pix.x = ((Point*)self)->x - startPix.x;
		pix.y = ((Point*)self)->y + startPix.y;
		DisplayObject_add_pixel( (DisplayObject*)self, &pix );	
		
		pix.x = ((Point*)self)->x + startPix.x;
		pix.y = ((Point*)self)->y - startPix.y;
		DisplayObject_add_pixel( (DisplayObject*)self, &pix );
		
		pix.x = ((Point*)self)->x - startPix.x;
		pix.y = ((Point*)self)->y - startPix.y;
		DisplayObject_add_pixel( (DisplayObject*)self, &pix );
		
		pix.x = ((Point*)self)->x + startPix.y;
		pix.y = ((Point*)self)->y + startPix.x;
		DisplayObject_add_pixel( (DisplayObject*)self, &pix );
		
		pix.x = ((Point*)self)->x - startPix.y;
		pix.y = ((Point*)self)->y + startPix.x;
		DisplayObject_add_pixel( (DisplayObject*)self, &pix );
		
		pix.x = ((Point*)self)->x + startPix.y;
		pix.y = ((Point*)self)->y - startPix.x;
		DisplayObject_add_pixel( (DisplayObject*)self, &pix );
		
		pix.x = ((Point*)self)->x - startPix.y;
		pix.y = ((Point*)self)->y - startPix.x;
		DisplayObject_add_pixel( (DisplayObject*)self, &pix );
		
		if (p < 0)
			p += 4 * startPix.x++ + 6;
		else
			p += 4 * (startPix.x++ - startPix.y--) + 10;
	}
	
	bool_t bufferingState = Display_get_instance()->bufferingEnabled;
	Display_get_instance()->bufferingEnabled = TRUE;	

	i_t retVal = DisplayObject_render( (DisplayObject*)self );
	Display_get_instance()->bufferingEnabled = bufferingState;
	
	return retVal;	
}	
