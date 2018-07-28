/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/displayobjects/point.h>

#define PARENT DisplayObject
#define PARENT_CALL(arg) DisplayObject_ ## arg

/*----------------------------------------------------------------------------*/

void Point_ctor( Point* self, coord_t x, coord_t y, i8_t color )
{
	PARENT_CALL(ctor)( (PARENT*)self );

	Pixel pix;
	//append_Vector ( (Vector*)&self->base.pixels, sizeof(Pixel), &pix );

	self->color = color;
	self->x = x;
	self->y = y;
}

/*----------------------------------------------------------------------------*/

int Point_draw( const Point* self )
{
	Pixel pix;
	
	pix.x = self->x;
	pix.y = self->y;
	pix.color = self->color;

	dtor_Vector( (Vector*)&self->base.pixels );
	ctor_Vector( (Vector*)&self->base.pixels, sizeof(Pixel) );	
	append_Vector ( (Vector*)&self->base.pixels, sizeof(Pixel), &pix );
	Pixel* buf = (Pixel*)use_data_Buffer( (Buffer*)&self->base.pixels );
	buf[0] = pix;
	
	return PARENT_CALL(render)( (PARENT*)self );
}