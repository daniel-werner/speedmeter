/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/displayobjects/bitmap.h>
#include <gui/pixel.h>
#include <gui/display.h>

#define PARENT DisplayObject
#define PARENT_CALL(arg) DisplayObject_ ## arg

#define PACK_SIZE 8

/*----------------------------------------------------------------------------*/

void Bitmap_ctor( Bitmap* self, coord_t x, coord_t y, coord_t width, coord_t height, const void* data, bool_t inverse )
{
	PARENT_CALL(ctor)( (PARENT*)self );

	((PARENT*)self)->doubleBuffering = FALSE;
	Point_ctor( &self->position, x, y, 0 );
	self->width = width;
	self->height = height;
	self->inverse = inverse;
	
	coord_t bufferHeight = height % PACK_SIZE == 0 ? height / PACK_SIZE : height / PACK_SIZE + 1; 
	Matrix_ctor( &self->data, (void*)data, bufferHeight, width );
}

/*----------------------------------------------------------------------------*/

int Bitmap_draw( const Bitmap* self )
{
//	Pixel pixel;
//	bool_t bufferingState = Display_get_instance()->bufferingEnabled;
//	
//	Display_get_instance()->bufferingEnabled = TRUE;
//	
//	for( coord_t y = 0; y < self->height; y++ )
//	{
//		for( coord_t x = 0; x < self->width; x++ )
//		{
//			u_t bufferY = (u_t)(y / PACK_SIZE);
//			u_t offsetY = (u_t)(y % PACK_SIZE);
//	
//			u8_t* ptrBuf = Matrix_use_data( &self->data, u8_t, bufferY, x );
//	
//			u8_t mask = ( 0x01 << ( 7 - offsetY ) );
//			if( (*ptrBuf & mask)  == mask )
//			{
//				pixel.color = 0x01;
//			}
//			else
//			{
//				pixel.color = 0x00;
//			}
//			
//			pixel.x = self->position.x + x;
//			pixel.y = self->position.y + y;
//			PARENT_CALL(add_pixel)( (PARENT*)self, &pixel );
//		}
//	}
//
//	PARENT_CALL(redraw)( (PARENT*)self, self->position.x, self->position.x + self->width - 1  );
//	
//	Display_get_instance()->bufferingEnabled = bufferingState;
//	return 1;
	
	return Bitmap_draw_partial( self, 0, 0, self->width, self->height );
}

/*----------------------------------------------------------------------------*/

int Bitmap_draw_partial( const Bitmap* self, coord_t x1, coord_t y1, coord_t x2, coord_t y2 )
{
	Pixel pixel;
	bool_t bufferingState = Display_get_instance()->bufferingEnabled;
	
	Display_get_instance()->bufferingEnabled = TRUE;
	
	for( coord_t y = y1; y < y2; y++ )
	{
		//u_t bufferY = (u_t)(y / PACK_SIZE);
		//u_t offsetY = (u_t)(y % PACK_SIZE);		
		
		u_t bufferY = (u_t)(y >> 3);	
		u_t offsetY = (u_t)(y - (bufferY << 3) );		
		
		for( coord_t x = x1; x < x2; x++ )
		{
			u8_t* ptrBuf = Matrix_use_data( &self->data, u8_t, bufferY, x );
	
			u8_t mask = ( 0x01 << ( 7 - offsetY ) );
			if( (*ptrBuf & mask)  == mask )
			{
				pixel.color = 0x01;
			}
			else
			{
				pixel.color = 0x00;
			}
			
			if ( self->inverse)
			{
				pixel.color = INVERSE_COLOR(pixel.color);
			}
			
			pixel.x = self->position.x + x - x1;
			pixel.y = self->position.y + y - y1;
			PARENT_CALL(add_pixel)( (PARENT*)self, &pixel );
		}
	}

	PARENT_CALL(redraw)( (PARENT*)self, self->position.x, self->position.x + ( x2 - x1 ) - 1 );
	
	Display_get_instance()->bufferingEnabled = bufferingState;
	return 1;
}