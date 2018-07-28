/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/displayobjects/line.h>
#include <gui/display.h>
#include <math.h>
//#include <stdlib.h>

#define PARENT DisplayObject
#define PARENT_CALL(arg) DisplayObject_ ## arg

/*----------------------------------------------------------------------------*/

void Line_ctor( Line* self, coord_t startX, coord_t startY, coord_t endX, coord_t endY, i8_t color )
{
	PARENT_CALL(ctor)( (PARENT*)self );

	self->color = color;
	Point_ctor( &self->startPoint, startX, startY, color );
	Point_ctor( &self->endPoint, endX, endY, color );
}

/*----------------------------------------------------------------------------*/

int Line_draw( const Line* self )
{
	bool_t bufferingState = Display_get_instance()->bufferingEnabled;
	Display_get_instance()->bufferingEnabled = TRUE;		
	
	i_t dx = self->endPoint.x - self->startPoint.x;
	i_t dy = self->endPoint.y - self->startPoint.y;

	coord_t dxAbs = (coord_t)fabs( dx );
	coord_t dyAbs = (coord_t)fabs( dy );	
		
	i_t signX = dx > 0 ? 1 : -1;
	i_t	signY = dy > 0 ? 1 : -1;
	
	coord_t x = dyAbs >> 1;
	coord_t y = dxAbs >> 1;

	coord_t px = self->startPoint.x;
	coord_t py = self->startPoint.y;
	
	Pixel pix;
	pix.color = self->color;
	
	dtor_Vector( (Vector*)&self->base.pixels );	

	if( dxAbs >= dyAbs )
	{
		ctor_Vector( (Vector*)&self->base.pixels, dxAbs * sizeof(Pixel) );
		for( i_t i = 0; i < dxAbs; i++ )
		{
			y += dyAbs;
			if( y >= dxAbs )
			{
				y -= dxAbs;
				py += signY;
			}
			px += signX;
			
			pix.x = px;
			pix.y = py;
			PARENT_CALL(add_pixel)( (PARENT*)self, &pix );
		}		
	}
	else
	{
		ctor_Vector( (Vector*)&self->base.pixels, dyAbs * sizeof(Pixel) );		
		for( i_t i = 0; i < dyAbs; i++ )
		{
			x += dxAbs;
			if( x >= dyAbs )
			{
				x -= dyAbs;
				px += signX;
			}
			py += signY;
			
			pix.x = px;
			pix.y = py;			
			PARENT_CALL(add_pixel)( (PARENT*)self, &pix );
		}				
	}	

	i_t retVal = PARENT_CALL(render)( (PARENT*)self );
	Display_get_instance()->bufferingEnabled = bufferingState;
	
	return retVal;
}

// Slow method
//int Line_draw( const Line* self )
//{
//	i_t dx = self->endPoint.x - self->startPoint.x;
//	i_t dy = self->endPoint.y - self->startPoint.y;
//
//	coord_t dxAbs = (coord_t)fabs( dx );
//	coord_t dyAbs = (coord_t)fabs( dy );	
//	
//	
//	f32_t m;
//	Pixel pix;
//	
//	pix.color = self->color;
//
//	dtor_Vector( (Vector*)&self->base.pixels );
//	
//	if( dxAbs > dyAbs )
//	{
//		m = (f32_t)( dy ) / ( dx );
//		i_t sign = self->startPoint.x < self->endPoint.x ? 1 : -1;
//		ctor_Vector( (Vector*)&self->base.pixels, dxAbs * sizeof(Pixel) );
//		for( i_t i = 0; i != dx; i += sign )
//		{
//			pix.x = i + self->startPoint.x;
//			pix.y = (coord_t)ceil( m * i + self->startPoint.y );
//			append_Vector ( (Vector*)&self->base.pixels, sizeof(Pixel), &pix );			
//		}		
//	}
//	else
//	{
//		m = (f32_t)( dx ) / ( dy );
//		i_t sign = self->startPoint.y < self->endPoint.y ? 1 : -1;
//		ctor_Vector( (Vector*)&self->base.pixels, dyAbs * sizeof(Pixel) );		
//		for( i_t i = 0; i != dy; i += sign )
//		{
//			pix.y = i + self->startPoint.y;
//			pix.x = (coord_t)ceil( m * i + self->startPoint.x );
//			append_Vector ( (Vector*)&self->base.pixels, sizeof(Pixel), &pix );			
//		}				
//	}	
//	
//	return PARENT_CALL(render)( (PARENT*)self );
//}