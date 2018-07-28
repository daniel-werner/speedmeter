/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/display.h>
#include <gui/drivers/PCD_8544_driver.h>
#include <math.h>
#include <string.h>
#include <system/system.h>

static Display displayInstance;
Display* display = NULL;
System* pSystem;

/*----------------------------------------------------------------------------*/

static u8_t displayBuffer[BUFFER_SIZE_W][BUFFER_SIZE_H];

/*----------------------------------------------------------------------------*/

static void Display_ctor( Display* self, u_t width, u_t height, DisplayDriver* displayDriver )
{
	pSystem = System_get_instance();
	Matrix_ctor( &self->displayBuffer, &displayBuffer, BUFFER_SIZE_W, BUFFER_SIZE_H );
	self->width = width;
	self->height = height;
	self->displayDriver = displayDriver;
}

/*----------------------------------------------------------------------------*/

Display* Display_get_instance()
{
	if( display == NULL )
	{
		Display_ctor( &displayInstance, DISPLAY_WIDTH, DISPLAY_HEIGHT, DisplayDriver_get_instance() );
		display = &displayInstance;
	}
	
	
	return display;
	
}

/*----------------------------------------------------------------------------*/

bool_t Display_render( const Display* self, DisplayObject* obj )
{
	if( self->bufferingEnabled )
	{
		u_t numElements = get_num_elements_Vector( &obj->pixels, Pixel );
		Pixel* pixels = (Pixel*)get_data_Buffer( (Buffer*)&obj->pixels );	
		
		coord_t x1 = pixels->x;
		coord_t x2 = pixels->x;
		for( int i = 0; i < numElements; i++ )
		{
			Pixel* pixel = (Pixel*)&pixels[i];
			
			if( pixel->x > x2 )
				x2 = pixel->x;
					
			if( pixel->x < x1 )
			{
				x1 = pixel->x;
			}
			u8_t* data = Display_set_pixel( self, pixel );
		}

		u_t size = (u_t)(x2 - x1 + 1 ) * BUFFER_SIZE_H;
		if( !pSystem->standby )
			DisplayDriver_put_pixels( self->displayDriver, &self->displayBuffer, x1, x2, size );
	}
	else
	{
		for( int i = 0; i < get_num_elements_Vector( &obj->pixels, Pixel ); i++ )
		{
			Pixel* pixels = (Pixel*)get_data_Buffer( (Buffer*)&obj->pixels );
			Pixel* pixel = (Pixel*)&pixels[i];
			
			u8_t* data = Display_set_pixel( self, pixel );
			if( !pSystem->standby )
				DisplayDriver_put_pixel( self->displayDriver, &self->displayBuffer, pixel->x, pixel->y );
		}
	}

	return TRUE;
//	if( !self->bufferingEnabled )
//	{
//		for( int i = 0; i < get_num_elements_Vector( &obj->pixels, Pixel ); i++ )
//		{
//			Pixel* pixels = (Pixel*)get_data_Buffer( (Buffer*)&obj->pixels );
//			Pixel* pixel = (Pixel*)&pixels[i];
//			
//			u8_t* data = Display_set_pixel( self, pixel );
//			DisplayDriver_put_pixel( self->displayDriver, &self->displayBuffer, pixel->x, pixel->y );
//		}
//	}	
//	
//	return TRUE;
}

/*----------------------------------------------------------------------------*/

bool_t Display_redraw( const Display* self, coord_t x1, coord_t x2 )
{
	u_t size = (u_t)(x2 - x1 + 1 ) * BUFFER_SIZE_H;
	if( !pSystem->standby )
		DisplayDriver_put_pixels( self->displayDriver, &self->displayBuffer, x1, x2, size );
	return TRUE;
}


/*----------------------------------------------------------------------------*/

void Display_clear( const Display* self )
{
	memset( displayBuffer, 0, DISPLAY_BUFFER_SIZE );
	if( !pSystem->standby )
		Display_redraw( self, 0, 97 );
}

/*----------------------------------------------------------------------------*/

u8_t* Display_set_pixel( const Display* self, Pixel* pixel )
{
//	u_t bufferY = (u_t)(pixel->y / PACK_SIZE);
//	u_t offsetY = (u_t)(pixel->y % PACK_SIZE);
	
	u_t bufferY = (u_t)(pixel->y >> 3);	
	u_t offsetY = (u_t)(pixel->y - (bufferY << 3) );
	
	u8_t* ptrBuf = Matrix_use_data( &self->displayBuffer, u8_t, pixel->x, bufferY );
	
	*ptrBuf &= ~( 0x01 << ( 7- offsetY ) );
	*ptrBuf |= ( pixel->color << ( 7 - offsetY ) );
	return ptrBuf;
}

/*----------------------------------------------------------------------------*/

Pixel Display_get_pixel( const Display* self, coord_t x, coord_t y )
{
	Pixel pixel;
	
	pixel.x = x;
	pixel.y = y;
	
	u_t bufferY = (u_t)(pixel.y / PACK_SIZE);
	u_t offsetY = (u_t)(pixel.y % PACK_SIZE);
	
	u8_t* ptrBuf = Matrix_use_data( &self->displayBuffer, u8_t, pixel.x, bufferY );
	
	u8_t mask = ( 0x01 << ( 7 - offsetY ) );

	if( (*ptrBuf & mask)  == mask )
	{
		pixel.color = 0x01;
	}
	else
	{
		pixel.color = 0x00;
	}	
	
	return pixel;
}

/*----------------------------------------------------------------------------*/

void Display_standby( const Display* self )
{
	Display_driver_standby( self->displayDriver );
}

/*----------------------------------------------------------------------------*/

void Display_wakeup( const Display* self )
{
	Display_driver_wakeup( self->displayDriver );
}