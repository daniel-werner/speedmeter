/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/displayobjects/mask.h>
#include <gui/pixel.h>
#include <gui/display.h>

#define PARENT Bitmap
#define PARENT_CALL(arg) Bitmap_ ## arg

#define PACK_SIZE 8

/*----------------------------------------------------------------------------*/

void Mask_ctor( Mask* self, coord_t x, coord_t y, coord_t width, coord_t height, u8_t fillColor, bool_t inverse )
{
	PARENT_CALL(ctor)( (PARENT*)self, x, y, width, height, NULL, inverse );
	self->fillColor = fillColor;
}

/*----------------------------------------------------------------------------*/

int Mask_draw( const Mask* self )
{
	Pixel pixel;
	bool_t bufferingState = Display_get_instance()->bufferingEnabled;
	Display* display = Display_get_instance();
	display->bufferingEnabled = TRUE;
	
	for( coord_t y = 0; y < ((PARENT*)self)->height; y++ )
	{
		for( coord_t x = 0; x < ((PARENT*)self)->width; x++ )
		{
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

			pixel.x = ((PARENT*)self)->position.x + x;
			pixel.y = ((PARENT*)self)->position.y + y;
			
			if( ((PARENT*)self)->inverse )
			{
				pixel.color = INVERSE_COLOR( Display_get_pixel( display, pixel.x, pixel.y ).color );
			}
			else
			{
				pixel.color = self->fillColor;
			}
			

			DisplayObject_add_pixel( (DisplayObject*)self, &pixel );
		}
	}

	DisplayObject_redraw( (DisplayObject*)self, ((PARENT*)self)->position.x, 
						 						((PARENT*)self)->position.x + ((PARENT*)self)->width - 1  );
	
	Display_get_instance()->bufferingEnabled = bufferingState;
	return 1;
	
}
